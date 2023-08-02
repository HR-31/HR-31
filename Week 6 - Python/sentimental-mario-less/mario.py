from cs50 import get_int

# Ensures user only inputs a number of 1 to 8 inclusive
while True:
    n = get_int("Height: ")
    if 0 < n < 9:  # I like how its a clean mathematical representation. OR didn't seem to work here
        break

# Printing blocks. Didn't need to use nested loops here.
for i in range(n):

    # This got tekky as I had to account for automatic 'space' provided by python at the end of line AND inbetween each argument
    print(" " * (n - i - 1) + "#" * (i + 1), end="")
    print()

