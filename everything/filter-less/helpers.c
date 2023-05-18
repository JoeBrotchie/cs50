#include "helpers.h"
#include <math.h>
#include <stdio.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double pixle_average = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed);
            pixle_average = pixle_average / 3;
            int pixle_average_r = round(pixle_average);
            image[i][j].rgbtBlue = pixle_average_r;
            image[i][j].rgbtGreen = pixle_average_r;
            image[i][j].rgbtRed = pixle_average_r;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double sepiaRed = (.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaRed_r = round(sepiaRed);
             if (sepiaRed_r > 255)
            {
                sepiaRed_r = 255;
            }
            double sepiaGreen = (0.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaGreen_r = round(sepiaGreen);
             if (sepiaGreen_r > 255)
            {
                sepiaGreen_r = 255;
            }
            double sepiaBlue = (.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            int sepiaBlue_r = round(sepiaBlue);
            if (sepiaBlue_r > 255)
            {
                sepiaBlue_r = 255;
            }
            image[i][j].rgbtRed = sepiaRed_r;
            image[i][j].rgbtGreen = sepiaGreen_r;
            image[i][j].rgbtBlue = sepiaBlue_r;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int p;
    for (int i = 0; i < height; i++)
    {
        p = width - 1;
        for (int j = 0; j < width / 2; j++)
        {
            int redhold = image[i][j].rgbtRed;
            int greenhold = image[i][j].rgbtGreen;
            int bluehold = image[i][j].rgbtBlue;
            image[i][j].rgbtRed = image[i][p].rgbtRed;
            image[i][j].rgbtGreen = image[i][p].rgbtGreen;
            image[i][j].rgbtBlue = image[i][p].rgbtBlue;
            image[i][p].rgbtRed = redhold;
            image[i][p].rgbtGreen = greenhold;
            image[i][p].rgbtBlue = bluehold;
            p--;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j].rgbtRed = image[i][j].rgbtRed;
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int counter = 0;
            double redcounter = 0;
            double greencounter = 0;
            double bluecounter = 0;
            int height_i = i - 1;
            int width_j = j - 1;
            for (int t = 0; t < 3; t++)
            {
                width_j = j - 1;
                if ((height_i >= 0) && (height_i <= height - 1))
                {
                    for (int r = 0; r < 3; r++)
                    {
                        if ((width_j >= 0) && (width_j <= width - 1))
                        {
                            redcounter += copy[height_i][width_j].rgbtRed;
                            greencounter += copy[height_i][width_j].rgbtGreen;
                            bluecounter += copy[height_i][width_j].rgbtBlue;
                            counter++;
                        }
                        width_j++;
                    }
                }
                height_i++;
            }
            redcounter = redcounter / counter;
            int redcounter_r = round(redcounter);
            image[i][j].rgbtRed = redcounter_r;

            greencounter = greencounter / counter;
            int greencounter_r = round(greencounter);
            image[i][j].rgbtGreen = greencounter_r;

            bluecounter = bluecounter / counter;
            int bluecounter_r = round(bluecounter);
            image[i][j].rgbtBlue = bluecounter_r;
        }
    }
    return;
}
