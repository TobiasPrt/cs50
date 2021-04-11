#include <stdio.h>
#include <cs50.h>

int get_int_between_range(int start, int end);
void print_string_repeated(string string, int count);

int main(void)
{
    int rows = get_int_between_range(1, 8);
    int cols = 1;
    
    do
    {
        print_string_repeated(" ", rows - cols);
        print_string_repeated("#", cols);
        print_string_repeated(" ", 2);
        print_string_repeated("#", cols);

        printf("\n");  

        ++cols;
    }
    while (cols <= rows);
}

int get_int_between_range(int start, int end)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < start || n > end);
    return n;
}

void print_string_repeated(string string, int count)
{
    for (int i = 0; i < count; ++i)
    {
        printf("%s", string);
    }
}