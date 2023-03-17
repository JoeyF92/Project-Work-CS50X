
// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table - i picked 650 (26 * 26)
const unsigned int N = 650;

int word_count = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    //put word we're checking through hash
    unsigned int hash_num = hash(word);

    //set a cursor to point at the hash index value in the table
    node *trav  = table[hash_num];


    //if our cursor doesnt point to null
    while (trav != NULL)
    {
        //check if first item on the link list matches the word
        if (strcasecmp(word, trav->word) == 0)
        {
            //if it does return true
            return true;
        }

        //if it doesnt, traverse the linked list to the next node
        trav = trav->next;

    }
    //if word still not found, we return false
    return false;

}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int first_hash = 0;
    int second_hash = 0;

    //convert the [0] and [1] of letter to uppercase
    char first_letter = toupper(word[0]);
    char second_letter = toupper(word[1]);

    //we're going to assign a value based on the first two letters of a word
    //65 is the ascii capital A and 90 is Z
    for (int i = 65; i <= 90; i++)
    {
        if (first_letter == i)
        {
            //if first letter is A (65), -64 so we get 1 - and x 26 as there's 26 letters in alphabet
            first_hash = (i - 64) * 26;
        }

        if (second_letter == i)
        {
            second_hash = i - 64;
        }
    }
    return first_hash + second_hash;

}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    //open dictionary file
    FILE *file = fopen(dictionary, "r");

    //return 1 if it can't be opened
    if (!file)
    {
        return 1;
    }

    char buffer[LENGTH + 1];
    //use fscanf to read words from the file into a buffer
    while (fscanf(file, "%s", buffer) != EOF)
    {
        //create space for a new node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return NULL;
        }

        //copy the string from buffer into our new node
        strcpy(n->word, buffer);

        //put the word through the hash function
        int hash_number = hash(buffer);

        //point our new node to the address of the hash table, at the hash number array point
        n->next = table[hash_number];

        //now we've added it to the linked list, we update the start of hash table to point to the new node
        table[hash_number] = n;

        word_count++;

    }
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
    //loop through each index of the table array
    for (int i = 0; i <= N; i++)
    {
        //set a pointer to the ith value of the array
        node *trav1 = table[i];
        //set a secondary pointer
        node *trav2;

        //if trav1 points to nothing, continue as nothing to free

        if (trav1 == NULL)
        {
            continue;
        }

        else if (trav1->next == NULL)
        {
            free(trav1);
            continue;
        }

        while (trav1->next != 0)
        {
            trav2 = trav1;
            trav1 = trav1->next;
            free(trav2);
        }
        free(trav1);

    }

    return true;
}
