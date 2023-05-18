#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

const int BLOCK = 512;
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
    {
        printf("Could not open file\n");
        return 1;
    }


    FILE *img = NULL;
    char *filename = malloc(8 * sizeof(char));
    int numberofjpg = 0;
    BYTE buffer[BLOCK];
    while (fread(buffer, 1, sizeof(BYTE) * BLOCK, f) == sizeof(BYTE) * BLOCK)
    {
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && ((buffer[3] & 0xf0) == 0xe0))
        {
            if (numberofjpg == 0)
            {
                sprintf(filename, "%03i.jpg", numberofjpg);
                img = fopen(filename, "w");
                fwrite(buffer, sizeof(BYTE) * BLOCK, 1, img);
            }
            else
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", numberofjpg);
                img = fopen(filename, "w");
                fwrite(buffer, sizeof(BYTE) * BLOCK, 1, img);
            }
            numberofjpg++;
        }
        else
        {
            if (numberofjpg !=  0)
            {
                fwrite(buffer, sizeof(BYTE) * BLOCK, 1, img);
            }
        }
    }
    free(filename);
    fclose(img);
    fclose(f);

    return 0;

}