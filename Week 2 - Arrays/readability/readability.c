#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // Get user text
    string word = get_string("Text: ");

    // Assigning variables to the functions so I can easily refer to them
    float a = count_letters(word);
    float b = count_words(word);
    float c = count_sentences(word);

    float L = (a / b) * 100;
    float S = (c / b) * 100;

    // Computing the Coleman-Liau index
    float index = (0.0588 * L) - (0.296 * S) - 15.8;


    // Computing what to print to terminal based on result above
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        int h = round(index); // Played around with double and float to get the right answer. But very cleverly just used variable 'h'!
        printf("Grade %i\n", h);
    }

}


// Count number of letters in string and print as integer
int count_letters(string text)
{
    int count = 0;

    for (int i = 0, n = strlen(text); i <= n; i++)
    {
        if (isalpha(text[i]))
        {
            count += 1;
        }
    }
    return count;

}

// Count words in the string using isspace to spot 'spaces'
int count_words(string text)
{
    int count = 0;

    for (int i = 0, n = strlen(text); i <= n; i++)
    {
        if (isspace(text[i]))
        {
            count += 1;
        }
        else if (i == n)
        {
            count += 1;
        }

    }
    return count;
}

// Count sentences using ., ! and ? to denote end of a sentence.
// Did really well to create these functions from a mix a googling and lecture tips. Well done!
int count_sentences(string text)
{
    int count = 0;

    for (int i = 0, n = strlen(text); i <= n; i++)
    {
        char a = text[i];

        if (a == '.')
        {
            count += 1;
        }
        else if (a == '!')
        {
            count += 1;
        }
        else if (a == '?')
        {
            count += 1;
        }
    }
    return count;

}
