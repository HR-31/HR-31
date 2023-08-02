#include <cs50.h>
#include <stdio.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Ask how many cents the customer is owed
    int cents = get_cents();

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("%i\n", coins);
}



int get_cents(void)
{
    // TODO
    int a;
    do
    {
        a = get_int("Number of Cents: ");
    }
    while (a < 0);
    return a;
}

int calculate_quarters(int cents)
{
    // TODO
    int b;
    {
        b = (cents / 25);
    }
    return b;
}

int calculate_dimes(int cents)
{
    // TODO
    int c;
    {
        c = (cents / 10);
    }
    return c;
}

int calculate_nickels(int cents)
{
    // TODO
    int d;
    {
        d = (cents / 5);
    }
    return d;
}

int calculate_pennies(int cents)
{
    // TODO
    int e;
    {
        e = (cents / 1);
    }
    return e;
}
