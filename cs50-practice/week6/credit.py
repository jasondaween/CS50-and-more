def main():
    try:
        card_number = str(int(input("Number: ")))
    except ValueError:
        return "INVALID"

    # Validate the card number
    if checksum(card_number) == str(0):
        digits = len(card_number)

        # Determine which card
        if (digits == 15) and (int(card_number[:2]) in {34, 37}):
            return "AMEX"
        elif (digits == 16) and (int(card_number[:2]) in range(51,56)):
            return "MASTERCARD"
        elif (digits in {13, 16}) and (int(card_number[0]) == 4):
            return "VISA"
        else:
            return "INVALID"
    else:
        return "INVALID"


# Luhn's algorithm function
def checksum(card_number):
    # 1. Multiply every other digit by 2 and add them
    sum = 0
    i = -2
    while i > -1 * (len(card_number) + 1):
        multiplied_digit = str(int(card_number[i]) * 2)
        if int(multiplied_digit) >= 10:
            total = int(multiplied_digit[0]) + int(multiplied_digit[1])
            sum += total
        else:
            sum += int(multiplied_digit)
        i -= 2

    # 2. Add sum to sum of the rest of the numbers
    i = -1
    while i > -1 * (len(card_number) + 1):
        digit = int(card_number[i])
        sum += digit
        i -= 2

    # 3. Return last digit of sum
    return str(sum)[-1]


if __name__ == "__main__":
    print(main())
