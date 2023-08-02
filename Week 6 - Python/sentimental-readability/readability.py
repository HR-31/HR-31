from cs50 import get_string


def main():
    # User input
    word = get_string("Text: ")

    # Assigning variables to functions
    a = count_letters(word)
    b = count_words(word)
    c = count_sentences(word)

    # Computing C-L index
    L = (a / b) * 100
    S = (c / b) * 100

    index = (0.0588 * L) - (0.296 * S) - 15.8

    # Deciding what to print to terminal
    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        # Round function applies in Python just the same as C
        print(f"Grade {round(index)}")


# Words function
def count_words(text):
    count = 0

    n = len(text)

    for i in range(n):
        if text[i].isspace():
            count += 1
        elif i == (n - 1):
            count += 1

    return count


# Letters function
def count_letters(text):
    count = 0

    for i in range(len(text)):
        if text[i].isalpha():
            count += 1

    return count


# Sentences function
def count_sentences(text):
    count = 0
    n = len(text)

    for i in range(n):
        if text[i] == '.':
            count += 1
        elif text[i] == '!':
            count += 1
        elif text[i] == '?':
            count += 1

    return count


main()