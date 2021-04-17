#include <stdio.h>
#include <cs50.h>
#include <math.h>

int input_length;
long card_number;
int calc_checksum(int digits_left);
int calc_input_length(long number);
bool validate_input_length(int length);
string identify_card_type(long card_number, int input_length);

int main(void)
{
    // get card number
    card_number = get_long("Number: ");

    // calculate length of number 
    input_length = calc_input_length(card_number);

    // check input length
    if (!validate_input_length(input_length))
    {
        printf("INVALID\n");
        return 0;
    }

    // calculate checksum
    int checksum = calc_checksum(1);
    if (!(checksum % 10 == 0)) {
        printf("INVALID\n");
        return 0;
    }

    // identify & print card type
    string card_type = identify_card_type(card_number, input_length);
    printf("%s\n", card_type);
}

int calc_input_length(long number)
{
    if (number < 10)
    {
        return 1;
    }
    return 1 + calc_input_length(number / 10);
}

bool validate_input_length(int length)
{
    switch(length) {
        case 13:
        case 15:
        case 16:
            return true;
            break;
        default:
            return false;
    }
}

int calc_checksum(int current_position)
{
    int mod = powl(10, current_position);
    // get current digit
    int digit = card_number % mod / mod;

    // calculate number to add to checksum
    int add = digit;
    if ((input_length - current_position) % 2 == 1)
    {
        add = add * 2;
    }
    add = (add / 10) + (add % 10);

    // end recursion, when at first position
    if (current_position == input_length)
    {
        return add;
    }

    // calculate next position
    return add + calc_checksum(current_position + 1);
}

string identify_card_type(long card_number, int input_length)
{
    int first_digit = card_number / powl(10, input_length - 1);
    int first_two_digits = card_number / powl(10, input_length - 2);

    switch(input_length) {
        case 13:
            if (first_digit == 4)
            {
                return "VISA";
            }
            break;
        case 15:
            if (first_two_digits == 34 || first_two_digits == 37)
            {
                return "AMEX";
            }
            break;
        case 16:
            if (first_two_digits >= 51 && first_two_digits <= 55)
            {
                return "MASTERCARD";
            }
            if (first_digit == 4)
            {
                return "VISA";
            }
            break;
    }

    return "INVALID";
}













