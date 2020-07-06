#include "helpers.h"
#include <math.h>
#include <stdio.h>


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //iterate through each row
    for (int i = 0; i < height; i++)
    {
        //iterate through each column
        for(int j = 0; j < width; j++)
        {
            //for each pixel, get the average of its b,g and r and set each colour channel to that value
            //don't know why i needed to convert all to floats but it worked
            float f_MEAN = round(((float)image[i][j].rgbtRed + (float)image[i][j].rgbtBlue + (float)image[i][j].rgbtGreen)/3.0);
            BYTE MEAN = (BYTE)f_MEAN;

            //don't need to use pointers, as the 2D array itself is passed to the function as a pointer
            //don't need to worry about the values changing, as mean is set before each of these, so they're all equal to the original mean
            image[i][j].rgbtRed = MEAN;
            image[i][j].rgbtBlue = MEAN;
            image[i][j].rgbtGreen = MEAN;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //iterate through each row
    for (int i = 0; i < height; i++)
    {
        //iterate through each column
        for(int j = 0; j < width; j++)
        {
            //set all colours as another variable before calculations so the values aren't changed
            float s_red = (float)image[i][j].rgbtRed;
            float s_green = (float)image[i][j].rgbtGreen;
            float s_blue = (float)image[i][j].rgbtBlue;

            //compute new values for sepia filter
            //compute calculation in floats, otherwise the BYTE type will return 0.
            float round_red = round(.393 * s_red + .769 * s_green + .189 * s_blue);
            float round_green = round(.349 * s_red + .686 * s_green + .168 * s_blue);
            float round_blue = round(.272 * s_red + .534 * s_green + .131 * s_blue);

            //set max to 255 for each, but maybe I will need to define seperate variables
            //and/or do the if statement before the function for each r, g and b if the program is gonna crash before this if statement:
            if (round_red > 255.0)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = (BYTE)round_red;
            }

            if (round_green > 255.0)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = (BYTE)round_green;
            }


            if (round_blue > 255.0)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = (BYTE)round_blue;
            }

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        //I think the while j is under half of width should work, as for example with width = 7, half is 3.5,
        //so it will carry out a loop for j=0,j=1,j=2,j=3 which is four loops which is what we want - if not use the round() function, it works.
        for(int j = 0; j < (float)width/2.0; j++)
        {
            //swapping each pixel with its counterpart, up until half way, otherwise it'll swap them all back again -
            //is this correct? do I need the * 'go to' operator?
            RGBTRIPLE temp = image[i][width - 1 - j];
            image[i][width - 1 - j] = image[i][j];
            image[i][j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float total_red = 0;
    float total_green = 0;
    float total_blue = 0;
    float pixel_count = 0;
    // float red_count = 0;
    // float green_count = 0;
    // float blue_count = 0;

    //for each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //take the average of all surrounding pixels
            for (int x = 1; x > -2; x--)
            {
                for (int y = 1; y > -2; y--)
                {
                    if (i - x >= 0 && j - y >= 0 && j - y < width && i - x < height)
                    {
                        total_red += (float)image[i-x][j-y].rgbtRed;
                        total_green += (float)image[i-x][j-y].rgbtGreen;
                        total_blue += (float)image[i-x][j-y].rgbtBlue;
                        pixel_count ++;
                    }
                }
            }


            image[i][j].rgbtRed = (BYTE)round(total_red/pixel_count);
            //printf("RED: %i",image[i][j].rgbtRed);
            image[i][j].rgbtGreen = (BYTE)round(total_green/pixel_count);
            //printf("GREEN: %i",image[i][j].rgbtGreen);
            image[i][j].rgbtBlue = (BYTE)round(total_blue/pixel_count);
            //printf("BLUE: %i",image[i][j].rgbtBlue);

            total_red = 0;
            // red_count = 0;
            total_green = 0;
            // green_count = 0;
            total_blue = 0;
            // blue_count = 0;
            pixel_count = 0;
        }
    }
    return;
}