#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

bool only_digits(string s);
char rotate(char c, int i);


int main(int argc, string argv[])
{
    if (argc == 2)
    {
        if (only_digits(argv[1]) > 0)
        {
            int k = atoi(argv[1]); // First use of atoi function

            string plaintext = get_string("plaintext: ");

            printf("ciphertext: ");

            for (int i = 0, n = strlen(plaintext); i < n; i++)

            {
                char a = rotate(plaintext[i], k); // Nicely went through each character
                printf("%c", a);
            }
            printf("\n");

        }
        else
        {
            printf("Usage: ./caesar key\n"); // Printing error message for incorrect cmd argument
            return 1;
        }
    }
    else
    {
        printf("What are you playing at? ....fool\n");
        return 1;                           // Exit status. Helps us find errors.
    }


}

bool only_digits(string s)
{
    int n = strlen(s);
    int count = 0;

    for (int i = 0; i <= n; i++)
    {

        if (isdigit(s[i]) > 0)
        {
            count++;
        }
    }

    if (count != n)  // By putting this if function outside of the above for function, I was able to get Only Digits to check each character of the string provided! Well done for persisting!
    {
        return 0;
    }
    else
    {
        return 1;
    }


    return 0;



}




char rotate(char c, int i) // Tough function to create but you did it!!
{
    if (isalpha(c) > 0)
    {
        if (islower(c) > 0)
        {
            char a = ((c - 97 + i) % 26) + 97;  // Used ASCII figures for capital letters
            return a;
        }
        else if (isupper(c) > 0)
        {
            char a = ((c - 65 + i) % 26) + 65;  // // Used ASCII figures for lowercase letters
            return a;
        }
    }
    else
    {
        return c;
    }
    return 0;

}










