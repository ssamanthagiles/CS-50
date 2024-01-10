// Implements a dictionary's functionality

#include "dictionary.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define TABLE_SIZE 1000

int word_count = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{

    // Get the hash value
    int hash_value = (int) hash(word);

    // Use the hash value to find the linked list in the hash table
    node *current_node = table[hash_value];

    // Traverse the linked list
    // while node is not NULL
    while (current_node != NULL)
    {
        // If the word is found, return true
        // if node's word is equal to lowercase_word
        if (strcasecmp(current_node->word, word) == 0)
        {
            // word is found
            return true;
        }

        // Move to the next node
        current_node = current_node->next;
        // node = node's next pointer
    }

    // If the word is not found, return false
    return false;
}

// Hashes word to a number
// TODO: Improve this hash function
// function hash(string word, int 169,981 ):
unsigned int hash(const char *word)
{
    int hashValue = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        hashValue = (hashValue * 31 + word[i]) % 169981;
    }
    return hashValue;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    // whether reached end of file or not...
    // went to small group office hours on 11/17/23 at 6:00 pm on zoom and went to sunday office hours
    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        // Add each word to the hash table
        node *new_node = malloc(sizeof(node));
        // copy into next node...
        strcpy(new_node->word, word);
    }
    // Close the file
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO

    for (int i = 0; i < N; i++)
    {
        // set a cursor node to the head of the list at that index
        node *cursor = table[i];
        // while the cursor is not NULL:
        while (cursor != NULL)
        {
            // set a temp node to the cursor
            node *temp = cursor;
            // move the cursor to the next node
            cursor = cursor->next;
            // free the temp node
            free(temp);
        }
    }
    return true;
}
