#include <cs50.h>
#include <stdio.h>

int get_int_above(int number, string prompt);

int main(void)
{
    // TODO: Prompt for start size
    int population = get_int_above(9, "Start size: ");

    // TODO: Prompt for end size
    int population_end = get_int_above(population, "End size: ");

    // TODO: Calculate number of years until we reach threshold
    int years = 0;

    while (population < population_end)
    {
    	population = population + population / 3 - population / 4;
    	++years;
    }
    

    printf("Years: %i", years);
}

int get_int_above(int number, string prompt)
{
    int n;
    do
    {
        n = get_int("%s ", prompt);
    }
    while (n < number);
    return n;
}