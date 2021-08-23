from cs50 import get_string


def main():
    input = get_string("Text: ")

    letters = count_letters(input)
    words = count_words(input)
    sentences = count_sentences(input)

    grade = calculate_grade(letters, words, sentences)
    print(grade)

    if grade <= 1:
        print("Before Grade 1")
    elif grade >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {grade}")


def count_letters(text):
    count = 0
    for c in text:
        count = count + 1 if c.isalpha() else count
    return count


def count_words(text):
    return text.count(" ") + 1


def count_sentences(text):
    questions = text.count("?")
    prompts = text.count("!")
    sentences = text.count(".")
    return questions + prompts + sentences


def calculate_grade(letters, words, sentences):
    avg_letters_per_100_words = letters * 100 / words
    avg_sentences_per_100_words = sentences * 100 / words
    index = (0.0588 * avg_letters_per_100_words) - (0.296 * avg_sentences_per_100_words) - 15.8
    return round(index)


main()
