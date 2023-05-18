#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


bool only_letters(string key);
bool key_length(string key);
bool no_repetition(string key);

int main(int argc, string argv[])
{
    if (argc > 2 | argc == 1)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    if (only_letters(argv[1]) == false)
    {
        printf("Key must only contain alphabetic characters.\n");
        return 1;
    }
    if (key_length(argv[1]) == false)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    if (no_repetition(argv[1]) == false)
    {
        printf("Key must not contain repeated characters.\n");
        return 1;
    }
    int l;
    string cipher = argv[1];
    string plaintext = get_string("plaintext : ");
    printf("ciphertext: ");
    for (int i = 0, length = strlen(plaintext); i < length; i++)
    {
        if (isalpha(plaintext[i]))
        {
            for (int j = 0, length2 = strlen(cipher); j < length2; j++)
            {
                if (isupper(plaintext[i]))
                {
                    if (cipher[j] == plaintext[i])
                    {
                        l = (plaintext[i] - 65);
                        printf("%c", cipher[l]);
                    }
                }
                if (islower(plaintext[i]))
                {
                    if (tolower(cipher[j]) == plaintext[i])
                    {
                        l = (plaintext[i] - 97);
                        printf("%c", tolower(cipher[l]));
                    }
                }
            }
        }
        else
        {
            printf("%c", plaintext[i]);
        }


    }
    printf("\n");
}

bool only_letters(string key)
{
    for (int i = 0, length = strlen(key); i < length; i++)
    {
        if (isalpha(key[i]) == false)
        {
            return false;
        }
    }
    return true;
}

bool key_length(string key)
{
    int length = strlen(key);
    if ((length == 26) == false)
    {
        return false;
    }
    return true;
}

bool no_repetition(string key)
{
    int letter;
    for (int i = 0, length = strlen(key); i < length; i++)
    {
        key[i] = toupper(key[i]);
        letter = key[i] - 65;
        for (int j = 0; j < length; j++)
        {
            if ((key[j] - 65) == letter)
            {
                if (j != i)
                {
                    return false;
                }
            }
        }
    }
    return true;
}