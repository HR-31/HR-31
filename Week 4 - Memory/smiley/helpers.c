#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) //Standard loop through all vertical blocks
    {
        for (int j = 0; j < width; j++) //Standard loop through all horizontal blocks
        {
            // Condition to check for black boxes: if colours are 0
            if (image[i][j].rgbtBlue == 0 && image[i][j].rgbtGreen == 0 && image[i][j].rgbtRed == 0)
            {
                image[i][j].rgbtGreen = 255; // Assigning colours to the blocks
                image[i][j].rgbtBlue = 200;
                image[i][j].rgbtRed = 156;
            }
        }
    }
}
