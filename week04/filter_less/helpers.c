#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdbool.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; ++row)
    {
        for (int col = 0; col < width; ++col)
        {
            // copy current pixel
            RGBTRIPLE pixel = image[row][col];

            // calculate average from copied values
            int average = round((pixel.rgbtBlue + pixel.rgbtGreen + pixel.rgbtRed) / 3.0);
            
            // manipulate pixel of original image
            image[row][col].rgbtRed = average;
            image[row][col].rgbtGreen = average;
            image[row][col].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; ++row)
    {
        for (int col = 0; col < width; ++col)
        {
            // copy current pixel
            RGBTRIPLE pixel = image[row][col];

            // calculate sepia values for the color channels
            int sepiaRed = round(.393 * pixel.rgbtRed + .769 * pixel.rgbtGreen + .189 * pixel.rgbtBlue);
            int sepiaGreen = round(.349 * pixel.rgbtRed + .686 * pixel.rgbtGreen + .168 * pixel.rgbtBlue);
            int sepiaBlue = round(.272 * pixel.rgbtRed + .534 * pixel.rgbtGreen + .131 * pixel.rgbtBlue);
            
            // manipulate pixel of original image
            image[row][col].rgbtRed = fmin(255.0, sepiaRed);
            image[row][col].rgbtGreen = fmin(255.0, sepiaGreen);
            image[row][col].rgbtBlue = fmin(255.0, sepiaBlue);            
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; ++row)
    {
        for (int col = 0; col < width / 2; ++col)
        {
            // copy current pixel on the left side
            RGBTRIPLE pixel = *(&image[row][col]);

            // replace current pixel with the one on the right side
            image[row][col] = *(&image[row][width - col - 1]);

            // replace pixel on the right side with copied one
            image[row][width - col - 1] = *(&pixel);
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // create a copy of the image im memory
    RGBTRIPLE copy[height][width];
    for (int row = 0; row < height; ++row)
    {
        for (int col = 0; col < width; ++col)
        {
            copy[row][col] = *(&image[row][col]);
        }
    }

    // manipulate image
    for (int row = 0; row < height; ++row)
    {
        for (int col = 0; col < width; ++col)
        {
            // declare used vars
            int sum_red = 0, sum_green = 0, sum_blue = 0, iterator = 0;

            // treat nearby pixels as a 3x3 grid with the current pixel in its center
            for (int grid_row = -1; grid_row < 2; ++grid_row)
            {
                for (int grid_col = -1; grid_col < 2; ++grid_col)
                {
                    // check whether current location is inside image dimensions
                    bool is_inside_image = row + grid_row >= 0 
                        && row + grid_row < height 
                        && col + grid_col >= 0 
                        && col + grid_col < width;

                    if (is_inside_image)
                    {
                        // add up the color channel sums
                        sum_red += copy[row + grid_row][col + grid_col].rgbtRed;
                        sum_green += copy[row + grid_row][col + grid_col].rgbtGreen;
                        sum_blue += copy[row + grid_row][col + grid_col].rgbtBlue;

                        // add up the iterator
                        ++iterator;

                    } 
                }
            }

            // calculate averages for each color channel
            int avg_red = round( (float) sum_red / (float) iterator);
            int avg_green = round( (float) sum_green / (float) iterator);
            int avg_blue = round( (float) sum_blue / (float) iterator);
            
            // manipulate original image
            image[row][col].rgbtRed = avg_red;
            image[row][col].rgbtGreen = avg_green;
            image[row][col].rgbtBlue = avg_blue;
        }
    }
    return;
}
