# TODO

from cs50 import get_string

# Uses CS50's getstring function to ask user for a name
name = get_string("What is your name? ")

# Prints hello,name to the terminal using much more succinct code than C: printf("Hello, %s/n", name)
print(f"hello, {name}")