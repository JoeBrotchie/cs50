# TODO
from cs50 import get_float

while True:
    cents = get_float("change owed: ")
    if cents > 0:
        break

cents = cents * 100

quarters = int(cents / 25)
cents = cents - quarters * 25

dimes = int(cents / 10)
cents = cents - dimes * 10

nickels = int(cents / 5)
cents = cents - nickels * 5

pennies = cents

coins = int(quarters + dimes + nickels + pennies)

print(f"{coins}")