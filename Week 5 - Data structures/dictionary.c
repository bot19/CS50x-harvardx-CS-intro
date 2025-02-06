// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

/*
 - only concepts learnt are utilised
 - parts pre-written, complete all function logic
 - task: https://cs50.harvard.edu/x/2025/psets/5/speller/
 */

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 17576; // 1st 3 letters = 26^3

// Hash table
node *table[N];

// global var for dictionary size
int dictionary_size = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // hash word to find hash table index/bucket
    int hash_no = hash(word);

    // access LL at index/bucket & traverse to find word
    if (table[hash_no] == NULL)
    {
        // no LL at table index/bucket, word not found
        return false;
    }
    else
    {
        // traverse (loop) to find word; keep looping until next ptr is NULL
        for (node *ptr = table[hash_no]; ptr != NULL; ptr = ptr->next)
        {
            // compare word of current node; case insensitive & apostrophes
            if (strcasecmp(ptr->word, word) == 0)
            {
                // if word match = found = return true
                return true;
            }
        }
    }

    // traversed LL at hash table and didn't find any matches
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function = will hash first 3 letters of word

    // base-26: 26^2 (third), 26^1 (second), 26^0 = 1 (first)
    int third = 676;
    int second = 26;
    int first = 1; // don't really need to multiply by this

    // calc length of string; account for 1-2 letter words
    int str_length = strlen(word);

    if (str_length == 1)
    {
        return toupper(word[0]) - 'A';
    }

    if (str_length == 2)
    {
        return (toupper(word[0]) - 'A') * second + (toupper(word[1]) - 'A');
    }

    // words 3 letters or longer
    return (toupper(word[0]) - 'A') * third + (toupper(word[1]) - 'A') * second +
           (toupper(word[2]) - 'A');
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // initialise hash table array to NULL values vs garbage; needed?
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // open dictionary file + check if successful
    FILE *source = fopen(dictionary, "r");
    if (!source)
    {
        return false;
    }

    // memory to store the scanned word
    char word_scanned[LENGTH + 1];

    // read strings from file, 1/line at a time to end of file (loop)
    while (fscanf(source, "%s", word_scanned) != EOF)
    {
        // create new node for word; need malloc + strcpy
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false; // exit of malloc issues; need to free mem later
        }

        // copy data into node
        strcpy(n->word, word_scanned);

        // hash word to obtain hash value
        int hash_no = hash(word_scanned);

        // insert node into hash table at index/bucket & latest in linked list
        if (table[hash_no] == NULL)
        {
            // bucket is empty, set node pointer to be head of linked list
            table[hash_no] = n;

            // set current node's next; don't have next node's pointer/addr yet
            n->next = NULL;
        }
        else
        {
            // linked list exist, add new node to head of linked list

            // prev 1st node of LL to be after/next of our current node
            n->next = table[hash_no];

            // get LL head to point to our node (new 1st node of LL)
            table[hash_no] = n;
        }

        // increment dictionary size
        dictionary_size++;
    }

    // close file
    fclose(source);

    // dictionary opened, scanned fully & closed, all done
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dictionary_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // go through hash table
    for (int i = 0; i < N; i++)
    {
        // for each bucket/index, traverse the LL & free each node
        node *ptr = table[i];
        while (ptr != NULL)
        {
            // create temp pointer to allow LL traversal & free nodes
            node *next = ptr->next;

            free(ptr);
            ptr = next;
        }
    }

    // if you reach here = everytihng freed
    return true;
}
