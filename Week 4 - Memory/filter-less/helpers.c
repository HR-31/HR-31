#include <math.h>

#include "helpers.h"


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Take the average of the original values
            int x = round((image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3.0);

            // Set the new values equal to the average of the old values
            image[i][j].rgbtRed = x;
            image[i][j].rgbtBlue = x;
            image[i][j].rgbtGreen = x;
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
            // Apply the Sepia formula to each of the individual colours for each single R, G, B value
            int a = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int b = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            int c = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);

            // Learnt that I can use separate IF-ELSE trees to ensure my programme doesn't quit early
            // Ensuring the max value for R, G, B is never above 255
            if (a > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = a;
            }

            if (b > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = b;
            }

            if (c > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = c;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //

    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < (width / 2); b++)
        {
            // Learnt to use a temp variable to switch the positions of two values in an array
            int temp = image[a][b].rgbtRed;
            image[a][b].rgbtRed = image[a][width - (b + 1)].rgbtRed;
            image[a][width - (b + 1)].rgbtRed = temp;

            int temp2 = image[a][b].rgbtBlue;
            image[a][b].rgbtBlue = image[a][width - (b + 1)].rgbtBlue;
            image[a][width - (b + 1)].rgbtBlue = temp2;

            int temp3 = image[a][b].rgbtGreen;
            image[a][b].rgbtGreen = image[a][width - (b + 1)].rgbtGreen;
            image[a][width - (b + 1)].rgbtGreen = temp3;
        }
    }
    return;
}



// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Established a copy of the original Image array, so we don't unintentionally corrupt the blur effect
    RGBTRIPLE copy[height][width];

    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            copy[x][y] = image[x][y];
        }
    }


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Instead of summing up all of the values in an equation like above, here we have a running total which we divide by the count at the end
            int sumRed = 0;
            int sumGreen = 0;
            int sumBlue = 0;
            int count = 0;

            // Here we ensure we don't go outside of our array
            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    int newRow = i + k;
                    int newCol = j + l;

                    if (newRow >= 0 && newRow < height && newCol >= 0 && newCol < width)
                    {
                        sumRed += copy[newRow][newCol].rgbtRed;
                        sumGreen += copy[newRow][newCol].rgbtGreen;
                        sumBlue += copy[newRow][newCol].rgbtBlue;
                        count++;
                    }
                }
            }

            image[i][j].rgbtRed = round((float)sumRed / count);
            image[i][j].rgbtGreen = round((float)sumGreen / count);
            image[i][j].rgbtBlue = round((float)sumBlue / count);
        }
    }
    return;
}
