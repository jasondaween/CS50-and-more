import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # TODO: Display the entries in the database on index.html
    stocks = db.execute(
        "SELECT symbol, SUM(shares) AS shares " 
        "FROM transactions "
        "WHERE user_id = ? "
        "GROUP BY symbol "
        "HAVING shares > 0", session["user_id"])

    # Lookup each stock quote
    for stock in stocks:
        quote = lookup(stock["symbol"])
        stock["name"] = quote["name"]
        stock["price"] = quote["price"]
        stock["total"] = stock["shares"] * quote["price"]

    # Find user current cash and total cash
    current_cash = db.execute(
        "SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
    total_cash = current_cash + sum(stock["total"] for stock in stocks)

    return render_template("index.html", stocks=stocks, cash=current_cash, total=total_cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    
    # User reached route via POST
    if request.method == "POST":
        # Ensure number of shares is valid
        try:
            shares = int(request.form.get("shares"))
            if shares < 1:
                return apology("Invalid amount", 403)
        except ValueError:
            return apology("Invalid amount", 403)

        # Look up stock symbol 
        stock = (lookup(request.form.get("symbol")))

        # Ensure symbol is valid
        if not request.form.get("symbol") or stock is None:
            return apology("Invalid symbol", 403)

        # Render confirmation page
        return render_template(
            "confirmation.html", action="Buy", shares=shares, stock=stock)

    # User reached route via GET
    else:
        # Show form
        return render_template("buy.html")


@app.route("/buy/confirmation", methods=["POST"])
@login_required
def buy_confirm():
    """Confirm Buy"""

    # Get data from the form
    shares = int(request.form.get("shares"))
    stock = lookup(request.form.get("symbol"))

    # Get users cash from database
    price = float(stock["price"]) * shares
    cash = float(db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"])
    if cash < price:
        return apology("Insufficient cash", 403)

    # Update users cash
    db.execute("UPDATE users SET cash = ? WHERE id = ?", cash - price, session["user_id"])

    # Insert transaction
    db.execute("INSERT INTO transactions(user_id, symbol, shares, price) VALUES(?, ?, ?, ?)",
        session["user_id"], stock["symbol"], shares, stock["price"])
    
    return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Display the entries in the database on history.html
    stocks = db.execute(
        "SELECT symbol, shares, price, time "
        "FROM transactions "
        "WHERE user_id = ?", session["user_id"]
    )

    # Find trade type and total cash value
    for stock in stocks:
        if stock["shares"] > 0:
            stock["type"] = "Buy"
            stock["total"] = stock["shares"] * stock["price"]
        else:
            stock["type"] = "Sell"
            stock["total"] = -(stock["shares"] * stock["price"])
        stock_total = stock["shares"] * stock["price"]

    return render_template("history.html", stocks=stocks)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # User reached route via POST
    if request.method == "POST":

        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("Must enter symbol", 403)

        # Look up stock symbol 
        stock = (lookup(request.form.get("symbol")))

        # Check if symbol exists
        if stock is None:
            return apology("Invalid symbol", 403)

        # Render new template
        return render_template("quoted.html", stock=stock)

    # User reached route via GET
    else:
        return render_template("quote.html")
    
    
@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User reached route via POST
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("Must enter username", 403)

        # Ensure password was submitted
        if not request.form.get("password"):
            return apology("Must enter password", 403)

        # Ensure confirmation was submitted
        if not request.form.get("confirmation"):
            return apology("Must enter confirmation", 403)

        # Ensure password matches confirmation
        if request.form.get("password") != request.form.get("confirmation"):
            return apology("Password must match with confirmation", 403)

        # Ensure username is not taken
        try:
            if db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username")):
                return apology("Username has been taken", 403)
        except:
            return apology("Database error", 500)

        # Generate hash of user's password
        hashed = generate_password_hash(request.form.get("password"))

        # Add user and hash to database
        db.execute("INSERT INTO users(username, hash) VALUES(?, ?)", request.form.get("username"), hashed)

        # Log user in and redirect to homepage
        session["user_id"] = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))[0]["id"]

        return redirect("/")

    # User reached route via GET
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # User reached route VIA post
    if request.method == "POST":

        # Ensure number of shares is valid
        try: 
            shares = int(request.form.get("shares"))
            if shares < 1:
                return apology("Invalid amount", 403)
        except ValueError:
            return apology("Invalid amount", 403)

        # Look up stock symbol
        stock = lookup(request.form.get("symbol"))

        # Ensure stock is valid 
        if not request.form.get("symbol") or stock is None:
            return apology("Invalid symbol", 403)

        # Query user database
        row = db.execute(
            "SELECT symbol, SUM(shares) AS shares "
            "FROM transactions "
            "WHERE user_id = ? AND UPPER(symbol) = UPPER(?)", session["user_id"], stock["symbol"]
        )
        shares_owned = row[0]["shares"] or 0

        # Ensure user owns the stock
        if shares_owned <= 0:
            return apology("You do not own this stock", 403)
        # Ensure user owns more shares than the input
        if shares > shares_owned:
            return apology("You do not own enough shares of this stock", 403)

        # Render confirmation page
        return render_template(
            "confirmation.html", action="Sell", shares=shares, stock=stock)
    
    # User reached route VIA get
    else:
        return render_template("sell.html")
    

@app.route("/sell/confirmation", methods=["POST"])
@login_required
def sell_confirm():
    """Confirm sell"""

    # Get data from the form
    shares = int(request.form.get("shares"))
    stock = lookup(request.form.get("symbol"))
    price = stock["price"] * shares

    # Get user cash 
    cash = db.execute(
        "SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

    # Update user cash
    db.execute("UPDATE users SET cash = ? WHERE id = ?", cash + price, session["user_id"])

    # Insert into database
    db.execute("INSERT INTO transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)",
        session["user_id"], stock["symbol"], -shares, stock["price"])

    return redirect("/")