from cs50 import get_int


def main():
    height = get_height_in_range(1, 8)
    print_pyramid(height)


def print_pyramid(height):
    width = 1
    while width <= height:
        print_string_repeated(" ", height - width)
        print_string_repeated("#", width)
        print_string_repeated(" ", 2)
        print_string_repeated("#", width)
        print()
        width += 1


def get_height_in_range(start, end):
    height = get_int("Height: ")
    while height < start or height > end:
        height = get_int("Height: ")
    return height


def print_string_repeated(string, number):
    for i in range(number):
        print(string, end="")


main()
