# Main Function
def main():
    # Get a text from user
    while True:
        text = input("Text: ")
        if len(text) > 0:
            break

    # Count Letters
    letters = count_letters(text)

    # Count Words
    words = count_words(text)

    # Count Sentences
    sentences = count_sentences(text)

    # Compute Index
    index = compute_index(letters, words, sentences)

    # Print Stats
    print(f"Letters: {letters}")
    print(f"Words: {words}")
    print(f"Sentences: {sentences}")
    print("Index: ", end="")

    # Print Grade Level
    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


# Count Letters Function
def count_letters(string):
    letters = 0

    for i in range(len(string)):
        if string[i].isalnum():
            letters += 1

    return letters


# Count Words Function
def count_words(string):
    words = 1

    for i in range(len(string)):
        if string[i] == ' ' and string[i + 1].isalnum():
            words += 1

    return words


# Count Sentences Function
def count_sentences(string):
    sentences = 0

    for i in range(len(string)):
        if string[i] in ['?', '.', '!'] and string[i - 1].isalnum():
            sentences += 1

    return sentences


# Compute Index Function
def compute_index(letters, words, sentences):
    L = letters / words * 100
    S = sentences / words * 100
    index = round(0.0588 * L - 0.296 * S - 15.8)

    return index


if __name__ == "__main__":
    main()
