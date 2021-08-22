from cs50 import get_float


COIN_SIZES = [25, 10, 5, 1]


def main():
    change = get_change()
    change = convert_change_to_cents(change)
    number_of_coins = calc_total_number_of_coins(change)
    print(number_of_coins)


def get_change():
    change = get_float("Change owed: ")
    while change < 0:
        change = get_float("Change owed: ")
    
    return change


def convert_change_to_cents(change):
    return int(round(change * 100))


def calc_total_number_of_coins(change):
    number_of_coins = 0 
    for coin_size in COIN_SIZES:
        # Count new coins
        counted_coins = calc_number_of_coins_with_size(change, coin_size)
        # Add new coins to total number of coins
        number_of_coins += counted_coins
        # Calculate remaining change
        change -= counted_coins * coin_size
    
    return number_of_coins


def calc_number_of_coins_with_size(change, coin_size):
    number_of_coins = 0
    while coin_size <= change:
        number_of_coins += 1
        change -= coin_size
    
    return number_of_coins


main()
