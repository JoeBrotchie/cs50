#include "helpers.h"
#include <math.h>


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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
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
            int counter1 = -1;
            int counter2 = -2;
            int counter3 = -1;
            double redcounterGx = 0;
            double greencounterGx = 0;
            double bluecounterGx = 0;
            int height_i = i - 1;
            int width_j = j - 1;
            for (int t = 0; t < 3; t++)
            {
                width_j = j - 1;
                if ((height_i >= 0) && (height_i <= height - 1))
                {
                    if (height_i == i - 1)
                    {
                        for (int r = 0; r < 3; r++)
                        {
                            if ((width_j >= 0) && (width_j <= width - 1))
                            {
                                redcounterGx += (counter1 * copy[height_i][width_j].rgbtRed);
                                greencounterGx += (counter1 * copy[height_i][width_j].rgbtGreen);
                                bluecounterGx += (counter1 * copy[height_i][width_j].rgbtBlue);
                            }
                            counter1++;
                            width_j++;

                        }
                        counter1 = -1;
                    }
                    if (height_i == i)
                    {
                        for (int r = 0; r < 3; r++)
                        {
                            if ((width_j >= 0) && (width_j <= width - 1))
                            {
                                redcounterGx += (counter2 * copy[height_i][width_j].rgbtRed);
                                greencounterGx += (counter2 * copy[height_i][width_j].rgbtGreen);
                                bluecounterGx += (counter2 * copy[height_i][width_j].rgbtBlue);
                            }
                            counter2 += 2;
                            width_j++;
                        }
                        counter2 = -2;
                    }
                    if (height_i == i + 1)
                    {
                        for (int r = 0; r < 3; r++)
                        {
                            if ((width_j >= 0) && (width_j <= width - 1))
                            {
                                redcounterGx += (counter3 * copy[height_i][width_j].rgbtRed);
                                greencounterGx += (counter3 * copy[height_i][width_j].rgbtGreen);
                                bluecounterGx += (counter3 * copy[height_i][width_j].rgbtBlue);
                            }
                            counter3++;
                            width_j++;
                        }
                        counter3 = -1;
                    }
                }
                height_i++;
            }

            double redcounterGy = 0;
            double greencounterGy = 0;
            double bluecounterGy = 0;
            counter1 = -1;
            counter2 = -2;
            counter3 = -1;
            width_j = j - 1;
            height_i = i - 1;
            for (int t = 0; t < 3; t++)
            {
                height_i = i - 1;
                if ((width_j >= 0) && (width_j <= width - 1))
                {
                    if (width_j == j - 1)
                    {
                        for (int r = 0; r < 3; r++)
                        {
                            if ((height_i >= 0) && (height_i <= height - 1))
                            {
                            redcounterGy += (counter1 * copy[height_i][width_j].rgbtRed);
                            greencounterGy += (counter1 * copy[height_i][width_j].rgbtGreen);
                            bluecounterGy += (counter1 * copy[height_i][width_j].rgbtBlue);
                            }
                            counter1++;
                            height_i++;
                        }
                        counter1 = -1;
                    }
                    if (width_j == j)
                    {
                        for (int r = 0; r < 3; r++)
                        {
                            if ((height_i >= 0) && (height_i <= height - 1))
                            {
                                redcounterGy += (counter2 * copy[height_i][width_j].rgbtRed);
                                greencounterGy += (counter2 * copy[height_i][width_j].rgbtGreen);
                                bluecounterGy += (counter2 * copy[height_i][width_j].rgbtBlue);
                            }
                            counter2 += 2;
                            height_i++;
                        }
                        counter2 = -2;
                    }
                    if (width_j == j + 1)
                    {
                        for (int r = 0; r < 3; r++)
                        {
                            if ((height_i >= 0) && (height_i <= height - 1))
                            {
                                redcounterGy += (counter3 * copy[height_i][width_j].rgbtRed);
                                greencounterGy += (counter3 * copy[height_i][width_j].rgbtGreen);
                                bluecounterGy += (counter3 * copy[height_i][width_j].rgbtBlue);
                            }
                            counter3++;
                            height_i++;
                        }
                        counter3 = -1;
                    }
                }
                width_j++;
            }

            redcounterGx = pow(redcounterGx, 2);
            redcounterGy = pow(redcounterGy, 2);
            float red = redcounterGx + redcounterGy;
            red = sqrt(red);
            int red_r = round(red);
            if (red_r > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = red_r;
            }

            greencounterGx = pow(greencounterGx, 2);
            greencounterGy = pow(greencounterGy, 2);
            float green = greencounterGx + greencounterGy;
            green = sqrt(green);
            int green_r = round(green);
            if (green_r > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = green_r;
            }

            bluecounterGx = pow(bluecounterGx, 2);
            bluecounterGy = pow(bluecounterGy, 2);
            float blue = bluecounterGx + bluecounterGy;
            blue = sqrt(blue);
            int blue_r = round(blue);
            if (blue_r > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = blue_r;
            }

        }
    }
    return;
}
