#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            RGBTRIPLE pixel = image[i][j];
            float average = round((pixel.rgbtBlue + pixel.rgbtGreen + pixel.rgbtRed) / 3.0);
            pixel.rgbtRed = average;
            pixel.rgbtGreen = average;
            pixel.rgbtBlue = average;
            image[i][j] = pixel;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            float sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            float sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            float sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            
            if (sepiaRed > 255) {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255) {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255) {
                sepiaBlue = 255;
            }
            
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;            
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; ++row)
    {
        for (int col = 0; col < round(width * 0.5); ++col)
        {
            int tmp_red = image[row][col].rgbtRed;
            int tmp_green = image[row][col].rgbtGreen;
            int tmp_blue = image[row][col].rgbtBlue;
            image[row][col].rgbtBlue = image[row][width-col-1].rgbtBlue;
            image[row][col].rgbtGreen = image[row][width-col-1].rgbtGreen;
            image[row][col].rgbtRed = image[row][width-col-1].rgbtRed;
            image[row][width-col-1].rgbtBlue = tmp_blue;
            image[row][width-col-1].rgbtGreen = tmp_green;
            image[row][width-col-1].rgbtRed = tmp_red;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE original[height][width];

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            original[i][j] = *(&image[i][j]);
        }
    }

    for (int r = 0; r < height; ++r)
    {
        for (int c = 0; c < width; ++c)
        {
            float sum_red = 0.0;
            float sum_green = 0.0;
            float sum_blue = 0.0;
            // shows us how many values we got
            float iterator = 0.0;
            // iterate over all 9 possible values by going from -1 to +1
            for (int row = -1; row < 2; ++row)
            {
                for (int col = -1; col < 2; ++col)
                {
                    // check if boundaries
                    if (r+row >= 0 && r+row < height && c+col >= 0 && c+col < width)
                    {
                        sum_red += original[r+row][c+col].rgbtRed;
                        sum_green += original[r+row][c+col].rgbtGreen;
                        sum_blue += original[r+row][c+col].rgbtBlue;
                        iterator = iterator + 1.0;

                    } 
                }
            }

            float avg_red = round(sum_red/iterator);
            float avg_green = round(sum_green/iterator);
            float avg_blue = round(sum_blue/iterator);
            
            image[r][c].rgbtRed = avg_red;
            image[r][c].rgbtGreen = avg_green;
            image[r][c].rgbtBlue = avg_blue;
        }
    }
    return;
}
