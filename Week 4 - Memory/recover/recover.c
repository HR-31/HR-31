#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        // Open file
        FILE *file = fopen(argv[1], "r");

        if (file == NULL)
        {
            printf("Input .raw file is empty\n");
            return 1;
        }

        int n = 512;

        char *buffer = (char *)malloc(n * sizeof(char)); // *buffer is a pointer

        if (buffer == NULL)
        {
            printf("Memory allocation failed\n");
            return 2;
        }

        int counter = 0;
        char filename[8];

        //Initialise the Image variable where we store the data for each image at a time
        FILE *img = NULL;

        //Loops through file until it reaches the last block.
        while (fread(buffer, 1, n, file) == n)
        {
            if (((unsigned char)buffer[0] == 0xff) && ((unsigned char)buffer[1] == 0xd8) && ((unsigned char)buffer[2] == 0xff)
                && (((unsigned char)buffer[3] & 0xf0) == 0xe0))
            {
                if (img != NULL)
                {
                    //Close current file
                    fclose(img);
                }

                //Creating new jpg file
                sprintf(filename, "%03i.jpg", counter);

                //Increase counter to keep track
                counter++;

                //Open new jpg file
                img = fopen(filename, "w");
            }


            //If there is still an open file then continue writing to it
            if (img != NULL)
            {
                fwrite(buffer, n, 1, img);
            }
        }

        if (img != NULL)
        {
            fclose(img);
        }

        //Close input file
        fclose(file);

        // Release memory
        free(buffer);

    }
    else
    {
        // Prompting user to enter the correct number of CL arguments
        printf("Correct usage is exactly one command-line argument...\n");
        return 1;
    }
}

