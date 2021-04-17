#include <stdio.h>
#include <cs50.h>
#include <math.h>

int number_of_coins = 0;
float get_float_above(int number, string prompt);
int count_number_of_coins(int change_in_cents, int coin_size);

int main(void)
{
    float change_in_dollars = get_float_above(0, "Change owed:");
    int change_in_cents = round(change_in_dollars * 100);

    change_in_cents = count_number_of_coins(change_in_cents, 25);
    change_in_cents = count_number_of_coins(change_in_cents, 10);
    change_in_cents = count_number_of_coins(change_in_cents, 5);
    change_in_cents = count_number_of_coins(change_in_cents, 1);

    printf("%i\n", number_of_coins);
}

float get_float_above(int number, string prompt)
{
    float n;
    do
    {
        n = get_float("%s ", prompt);
    }
    while (n <= number);
    return n;
}

int count_number_of_coins(int change_in_cents, int coin_size)
{
    while ( coin_size <= change_in_cents )
    {
        change_in_cents = change_in_cents - coin_size;
        ++number_of_coins;
    }
    return change_in_cents;
}