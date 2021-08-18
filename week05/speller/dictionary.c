#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

// Implements a dictionary's functionality
#include "dictionary.h"



// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 311;

// Hash table
node *table[N];

// Number of loaded words
int loadedWords = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Get index for bucket in which word would be
    int index = hash(word);

    // Set return value
    bool word_is_found = false;

    // Declare cursor
    node* cursor = table[index];

    // Loop over linked list in specific bucket
    while(cursor != NULL)
    {
        // Check whether word is at position of the cursor
        word_is_found = strcasecmp(cursor->word, word) == 0;

        // If the word is at the position of the counter return true
        if (word_is_found)
        {
            break;
        }

        // Move cursor to next element in linked list
        cursor = cursor->next;
    }

    // Return false if word is not in dictionary
    return word_is_found;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Assign memory for hash
    unsigned int hash = 1;

    // Loop over string and multiply the int values of the chars
    int i = 0;
    while(word[i] != '\0')
    {
        // Convert to lower to make sure upper and lower case variants of words are in the same bucket
        hash = hash * tolower(word[i]);
        i++;
    }

    // Return the remainder with the number of buckets in hash table
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *file  = fopen(dictionary, "r");

    // Check if file could be opened
    if (file == NULL)
    {
        return false;
    }

    // Create buffer to store word in memory
    char buffer[LENGTH + 1];

    // Read strings from file one at a time
    while(fscanf(file, "%s", buffer) != EOF)
    {
        // Allocate memory for each word
        node *n = malloc(sizeof(node));

        // Return false if mallox returned null, when there is not enough memory
        if (n == NULL) {
            return false;
        }

        // Copy word in location of the node
        strcpy(n->word, buffer);

        // Hash the word to create an index, which determines which linked list to use
        unsigned int index = hash(buffer);

        // Set pointer of node to head of linked list
        n->next = table[index];

        // Set the pointer of the table head to current node
        table[index] = n;

        loadedWords++;
    }

    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return loadedWords;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Loop through all buckets in hash table
    for (int i = 0; i < N; ++i)
    {
        // Set cursor to the begin of the linked list in given bucket
        node* cursor = table[i];
        
        // Loop through linked list
        while (cursor != NULL)
        {
            // Store current cursor position in tmp
            node* tmp = cursor;

            // Move cursor to next element of linked list
            cursor = tmp->next;

            // Free memory at position of tmp (last cursor position)
            free(tmp);
        }
    }

    return true;
}
