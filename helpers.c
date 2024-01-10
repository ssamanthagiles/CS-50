#include "helpers.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int min(int a, int b)
{
    return a < b ? a : b;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

// int sumRed;
// int sumGreen;
// int sumBlue;
// int count = 0;

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        // Look through each column
        for (int j = 0; j < width; j++)
        {
            // Take average of red, green, and blue
            int average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            // Update pixel values by setting each RGB value to average
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Copy pixel position into pixel variable
            RGBTRIPLE pixel = image[i][j];
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            // Compute sepia values
            int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

            // Update pixel with sepia values
            image[i][j].rgbtRed = sepiaRed > 255 ? 255 : sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen > 255 ? 255 : sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue > 255 ? 255 : sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    //     for each row i from 0 to height
    for (int i = 0; i < height; i++)
    {
        // for each pixel j from 0 to width/2
        for (int j = 0; j < width / 2; j++)
        {
            // swap pixel at position j with pixel at position (width - j - 1) in row i
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// blur image !!
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // declaring & initalizing integer values
            int red = 0;
            int green = 0;
            int blue = 0;
            int count = 0;
            // in this case, s stands for row
            for (int s = max(0, i - 1); s <= min(height - 1, i + 1); s++)
            {
                // in this case a = column
                for (int a = max(0, j - 1); a <= min(width - 1, j + 1); a++)
                {
                    // increments the count variable after each loop
                    count++;
                    // adds red, green, blue values of surrounding pixels to the pixel of the image
                    red += image[s][a].rgbtRed;
                    blue += image[s][a].rgbtBlue;
                    green += image[s][a].rgbtGreen;
                }
            }
            // Calculating the average red, blue, and green values
            copy[i][j].rgbtRed = round((float) red / count);
            copy[i][j].rgbtBlue = round((float) blue / count);
            copy[i][j].rgbtGreen = round((float) green / count);
        }
    }
    // updates the original image with the new blur data
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }
}
