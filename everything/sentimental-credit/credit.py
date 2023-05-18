# TODO
from cs50 import get_string

number = get_string("number: ")

luhm = 0
for i in range(len(number) - 2, -1, -2):
    digit = int(number[i]) * 2
    luhm = luhm + (digit % 10)
    luhm = luhm + int(digit / 10)
for i in range(len(number) - 1, -1, -2):
    luhm = luhm + int(number[i])

if luhm % 10 == 0:
    if len(number) == 15:
        if ((int(number[0]) == 3) and (int(number[1]) == 4) or (int(number[1]) == 7)):
            print("AMEX")
        else:
            print("INVALID")

    elif len(number) == 16:
        if ((int(number[0]) == 5) and ((int(number[1]) > 0) and (int(number[1]) < 6))):
            print("MASTERCARD")
        elif int(number[0]) == 4:
            print("VISA")
        else:
            print("INVALID")

    elif len(number) == 13:
        if int(number[0]) == 4:
            print("VISA")
        else:
            print("INVALID")
            
    else:
        print("INVALID")
else:
    print("INVALID")

