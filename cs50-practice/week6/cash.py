# ask user for change owed
while True:
    try:
        change = round(float(input("Change: ")) * 100)
        if change > 0:
            break
    except ValueError:
        pass

coins = 0

# while loop until change = 0
while change > 0:
    if change >= 25:
        change -= 25
    elif change >= 10:
        change -= 10
    elif change >= 5:
        change -= 5
    else:
        change -= 1
    coins += 1
print(f"{coins}")
