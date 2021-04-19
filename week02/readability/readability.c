#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");

    float letter_count = count_letters(text);
    float word_count = count_words(text);
    float sentence_count = count_sentences(text);

    float average_number_of_letters_per_100_words = letter_count * 100.00 / word_count;
    float average_number_of_sentences_per_100_words = sentence_count * 100.00 / word_count;

    float grade_index = (0.0588 * 
        average_number_of_letters_per_100_words) - 
        (0.296 * average_number_of_sentences_per_100_words) - 15.8;

    int rounded_grade_index = round(grade_index);


    if (rounded_grade_index <= 1)
    {
        printf("Before Grade 1\n");
    }
    else if (rounded_grade_index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", rounded_grade_index);   
    }
}

int count_letters(string text)
{
    int text_length = strlen(text);
    int letter_count = 0;

    for (int i = 0; i < text_length; ++i)
    {
        if (isupper(text[i]) || islower(text[i]))
        {
            ++letter_count;
        }
    }
    return letter_count;
}

int count_words(string text)
{
    int text_length = strlen(text);
    int word_count = 1;

    for (int i = 0; i < text_length; ++i)
    {
        int ascii_value = text[i];
        
        if (ascii_value == 32)
        {
            ++word_count;
        }
    }
    return word_count;
}


int count_sentences(string text)
{
    int text_length = strlen(text);
    int sentence_count = 0;

    for (int i = 0; i < text_length; ++i)
    {
        int ascii_value = text[i];
        
        if (ascii_value == 33 || ascii_value == 46 || 
            ascii_value == 63)
        {
            ++sentence_count;
        }
    }
    return sentence_count;
}