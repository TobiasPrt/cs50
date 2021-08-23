from cs50 import get_int


VALID_CARDNUMBER_LENGTHS = [13, 15, 16]


def main():
    cardnumber = get_int("Number: ")
    cardnumber_length = calc_length_of_cardnumber(cardnumber)

    if not cardnumber_length in VALID_CARDNUMBER_LENGTHS:
        print("INVALID")
        return

    checksum = calc_checksum_of_cardnumber(cardnumber, cardnumber_length)

    if not checksum % 10 == 0:
        print("INVALID")
        return

    card_type = identify_card_type(cardnumber, cardnumber_length)
    print(card_type)


def calc_length_of_cardnumber(number):
    return len(str(number))


def calc_checksum_of_cardnumber(number, length):
    checksum = 0
    number = str(number)
    for i in range(0, len(number)):
        is_even = (length - i) % 2 == 0
        digit = int(number[i])
        checksum += add_to_checksum(number[i], is_even, length)

    return checksum


def add_to_checksum(digit, is_even, length):
    digit = int(digit)
    if is_even:
        digit *= 2
    if digit > 9:
        digit = sum_digits(digit)
    return digit


def sum_digits(number):
    sum = 0
    while number > 0:
        sum += number % 10
        number //= 10

    return sum


def identify_card_type(number, length):
    if is_VISA(number, length):
        return "VISA"
    elif is_AMEX(number, length):
        return "AMEX"
    elif is_MASTERCARD(number, length):
        return "MASTERCARD"
    else:
        return "INVALID"


def is_VISA(number, length):
    first_digit = int(str(number)[0])
    if first_digit == 4 and length in [13, 16]:
        return True
    return False


def is_AMEX(number, length):
    first_two_digits = int(str(number)[0:2])
    if first_two_digits in [34, 37] and length == 15:
        return True
    return False


def is_MASTERCARD(number, length):
    first_two_digits = int(str(number)[0:2])
    if first_two_digits in [51, 52, 53, 54, 55] and length == 16:
        return True
    return False


main()