#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

bool only_digits(string key);

int main(int argc, string argv[])
{
    if (argc > 2 | argc == 1)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    if (only_digits(argv[1]) == false)
    {
        printf("usage: ./caesar key\n");
        return 1;
    }
    char cyphertext;
    int key = atoi(argv[1]);
    string planetext = get_string("plaintext: ");
    printf("ciphertext: ");
    for (int i = 0, length = strlen(planetext); i < length; i++)
    {
        if (isalpha(planetext[i]))
        {
            if (isupper(planetext[i]))
            {
                cyphertext = ((planetext[i] - 65 + key) % 26) + 65;
                printf("%c", cyphertext);
            }
            else
            {
               cyphertext = ((planetext[i] - 97 + key) % 26) + 97;
               printf("%c", cyphertext);
            }
        }
        else
        {
            cyphertext = planetext[i];
            printf("%c", cyphertext);
        }
    }
    printf("\n");
}




bool only_digits(string key)
{
    for (int i = 0, length = strlen(key); i < length; i++)
    {
        if (isdigit(key[i]) == false)
        {
            return false;
        }
    }
    return true;
}