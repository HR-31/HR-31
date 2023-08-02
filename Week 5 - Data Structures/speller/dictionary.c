#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>

#include "dictionary.h"

#define LENGTH 45

unsigned int word_count = 0;


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// todo(lower case because Optional): Choose number of buckets in hash table
const unsigned int N = 676; // todo: Change this to ---> 26 letters to the power of 2 (checking first two letters of word)

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    //Hash word to obtain hash value
    int hash_value = hash(word);

    //Set pointer Cursor to the first entry of the linked list
    node *cursor = table[hash_value];

    //Traverse linked list for the Word
    while (cursor != NULL)
    {
        //Check if word matches
        if (strcasecmp(word, cursor -> word) == 0)
        {
            return true;
        }
        //Set cursor pointer to the header of the next node i.e. the Next value in your current node struct
        cursor = cursor -> next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    //Hashing 1st letter
    int letter1 = (tolower(word[0]) - 97);

    if (strlen(word) <= 1)
    {
        return letter1;
    }

    //Hashing 2nd letter
    if (letter1 == 0)
    {
        int letter2 = (tolower(word[1]) - 97);
        return (letter1 * 26) + letter2 + 26;
    }
    else
    {
        int letter2 = (tolower(word[1]) - 97);
        return (letter1 * 26) + letter2;
    }
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary
    FILE *file = fopen(dictionary, "r");

    if (file == NULL)
    {
        printf("Input file dictionary is empty\n");
        return false;
    }

    // Read strings from file
    char *word = (char *)malloc(LENGTH * sizeof(char));


    while (fscanf(file, "%s", word) != EOF)
    {
        node *n = malloc(N * sizeof(node));

        // Create a new node for each word
        if (n == NULL)
        {
            printf("Malloc error, not enough memory\n");
            return false;
        }

        strcpy(n -> word, word); // 1st word is the array in the Node struct. 2nd word is the variable I created above
        n -> next = NULL;

        // Hashing each word
        int x = hash(word);

        // Insert Node into Hash Table
        n -> next = table[x];
        table[x] = n;

        // Increasing global variable word_count for size function below
        word_count++;
    }

    fclose(file);

    free(word);
    return true;

}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Iterate over hash table, covering each node and freeing up memory
    for (int i = 0; i < N; i++)
    {
        // Create pointer to point at head of node
        node *cursor = table[i];

        // Create pointer temp so that the rest of linked list is not lost
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor -> next;
            free(tmp);
        }
    }
    return true;
}