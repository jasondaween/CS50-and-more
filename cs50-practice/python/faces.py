# Main function
def main():
    string = input(" ")
    convertedstring = convert(string)
    print(convertedstring)


# Convert function
def convert(text):
    text = text.replace(":)", "🙂")
    text = text.replace(":(", "🙁")
    return text


if __name__ == "__main__":
    main()
