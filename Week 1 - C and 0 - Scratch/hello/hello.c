#include <stdio.h>
#include <cs50.h> // Needed to use get_string function

int main(void)
{
    string name = get_string("What is your name? "); // Asking user what their name is

    printf("hello, %s\n", name); // Printing out "hello ++ user name"
}

