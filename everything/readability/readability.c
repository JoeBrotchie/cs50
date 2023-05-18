#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void)
{
    string text = get_string("text: ");

    float letter = 0;
    float word = 1;
    float  sentence = 0;
    for(int i = 0, length = strlen(text); i < length; i++)
    {
        if(isupper(text[i]) || islower(text[i]))
        {
            letter += 1;
        }
        else if(isspace(text[i]))
        {
            word += 1;
        }
        else if(text[i] == 46 || text[i] == 33 || text[i] == 63)
        {
            sentence += 1;
        }
    }
    float l = (letter / word * 100);
    float s = (sentence / word * 100);
    int index = round(0.0588 * l - 0.296 * s - 15.8);
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}