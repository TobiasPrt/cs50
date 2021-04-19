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
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // check length of key
    int key_length = strlen(argv[1]);
    if (key_length > 26 || key_length < 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    
    // iterate to check if all digit
    int argument_length = strlen(argv[1]);
    for (int i = 0; i < argument_length; ++i)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Usage: ./substitution key\n");
            return 1;
        }
    }

    // save key
    string key = argv[1];

    // check for duplicates
    for (int i = 0; i < argument_length; ++i)
    {
        for (int j = 0; j < argument_length; ++j)
        {
            if (i != j && tolower(key[i]) == tolower(key[j]))
            {
                printf("Don't use duplicate letters.\n");
                return 1;
            }
        }
    }

    
    
    // get input text
    string input = get_string("plaintext: ");
    
    // print ciphertext
    printf("ciphertext: ");

    // iterate over each char
    int input_length = strlen(input);
    for (int i = 0; i < input_length; ++i)
    {
        int ascii_value = input[i];

        if (islower(input[i]))
        {
            int position_in_alphabet = ascii_value - 97;
            int replacement_char = tolower(key[position_in_alphabet]);
            printf("%c", replacement_char);
        } else if (isupper(input[i]))
        {
            int position_in_alphabet = ascii_value - 65;
            int replacement_char = toupper(key[position_in_alphabet]);
            printf("%c", replacement_char);
        }
        else
        {
            printf("%c", input[i]);
        }
    }
    
    
    printf("\n");
}