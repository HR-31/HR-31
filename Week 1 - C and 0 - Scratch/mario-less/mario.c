#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int h;
    do
    {
        h = get_int("Height: ");
    }
    while ((h < 1) ||  // height input cannot be less than one OR more than 8
           (h > 8));   // first real use of a do-while loop, so very pleased


    for (int row = 1; row <= h; row++)  // first nest loop. This row sets up the rows
    {
        for (int dots = (h - 1); dots >= row; dots--)  // this row sets up the dots.
        {
            printf(" ");
        }

        for (int hashes = 1; hashes <= row; hashes++)  // this row sets up the hashes
        {
            printf("#");
        }
        printf("\n");
    }





}