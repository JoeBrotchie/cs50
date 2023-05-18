// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 100000;

// Hash table
node *table[N];

int word_c = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int pos = hash(word);
    node *cursor = malloc(sizeof(node));
    if (cursor == NULL)
    {
        printf("could not make space for cursor\n");
        free(cursor);
        return false;
    }
    cursor = table[pos];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int pos = 0;
    if (isalpha(word[0]))
    {
        pos += (toupper(word[0]) - 65);
    }
    if (strlen(word) > 1)
    {
        if (isalpha(word[1]))
        {
            pos += (toupper(word[1]) - 64) * 26 + 1;
        }
    }
    return pos;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("could not open dictionary\n");
        fclose(dict);
        return false;
    }

    char *word = malloc(LENGTH + 1);
    if (word == NULL)
    {
        fclose(dict);
        free(word);
        return false;
    }
    while (fscanf(dict, "%s", word) != EOF)
    {
        node *tmp = malloc(sizeof(node));
        if (tmp == NULL)
        {
            fclose(dict);
            free(word);
            return false;
        }

        int pos = hash(word);
        strcpy(tmp->word, word);
        if (table[pos] == NULL)
        {
            tmp->next = NULL;
        }
        else
        {
            tmp->next = table[pos];
        }
        table[pos] = tmp;
        word_c++;
    }
    fclose(dict);
    free(word);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_c;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    node *tmp = malloc(sizeof(node));
    if (tmp == NULL)
    {
        free(tmp);
        return false;
    }
    node *cursor = malloc(sizeof(node));
    if (cursor == NULL)
    {
        free(tmp);
        free(cursor);
        return false;
    }
     for (int i = 0; i < N; i++)
    {
        cursor = table[i];
        tmp = cursor;
        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
        free(cursor);
    }
    return true;
}
