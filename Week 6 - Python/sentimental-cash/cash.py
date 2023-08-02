# TODO

from cs50 import get_float

while True:
    cents = get_float("Change Owed: ")
    if cents >= 0.0:
        break

# Convert cents so I can work with integers instead of float
cents = cents * 100

# Calculate the number of quarters to give the customer
quarters = cents // 25
cents = cents - quarters * 25

# Calculate the number of dimes to give the customer
dimes = cents // 10
cents = cents - dimes * 10

# Calculate the number of nickels to give the customer
nickels = cents // 5
cents = cents - nickels * 5

# Calculate the number of nickels to give the customer
pennies = cents // 1
cents = cents - pennies * 1

# Sum coins
coins = int(quarters + dimes + nickels + pennies)

# Print total number of coins to give the customer
print(coins)