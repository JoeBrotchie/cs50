#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int x;
    do
    {
        x = get_int("hight: ");
    }
    while (x < 1 || x > 8);

    for (int i = 0; i < x; i++)
    {
        for (int j = x; j > i+1; j--)
        {
            printf(" ");
        }
        for (int l = 0; l < i+1; l++)
        {
            printf("#");
        }
        printf("  ");
        for (int l = 0; l < i+1; l++)
        {
            printf("#");
        }
        printf("\n");
    }
}