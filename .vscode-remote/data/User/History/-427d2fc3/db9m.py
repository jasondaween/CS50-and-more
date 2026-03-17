import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)
app.secret_key = "coolsecretkey"

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")

        if not name or not month or not day:
            flash("Missing Inputs!")
            return redirect("/")
        try:
            month = int(month)
            day = int(day)
        except ValueError:
            flash("Missing Month and/or Day!")
            return redirect("/")

        if month in [4, 6, 9, 11] and day > 30:
            flash("Invalid Date!")
            return redirect("/")
        if month == 2 and day > 29:
            flash("Invalid Date!")
            return redirect("/")
        # TODO: Add the user's entry into the database
        db.execute("insert into birthdays(name, month, day) values(?, ?, ?)", name, month, day)
        return redirect("/")

    else:

        # TODO: Display the entries in the database on index.html
        birthdays = db.execute("select * from birthdays")
        return render_template("index.html", birthdays=birthdays)


