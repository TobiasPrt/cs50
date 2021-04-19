#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // check if one cmd line arg is set
    if (argc < 2 || argc > 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    
    // iterate to check if all digit
    int argument_length = strlen(argv[1]);
    for (int i = 0; i < argument_length; ++i)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    // convert to int
    int key = atoi(argv[1]);
        
    
    // get input text
    string input = get_string("plaintext: ");
    
    // print ciphertext
    printf("ciphertext: ");

    // iterate over each char
    int input_length = strlen(input);
    for (int i = 0; i < input_length; ++i)
    {
        int ascii_value = input[i] + key;
        
        if (isupper(input[i]))
        {
            while (ascii_value > 90)
            {
                ascii_value -= 26;
            }
            printf("%c", ascii_value);
        }
        else if (islower(input[i]))
        {
            while (ascii_value > 122)
            {
                ascii_value -= 26;
            }
            printf("%c", ascii_value);
        }
        else
        {
            printf("%c", input[i]);
        }
    }
    
    printf("\n");
}