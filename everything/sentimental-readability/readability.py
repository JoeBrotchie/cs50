# TODO
from cs50 import get_string

text = get_string("text: ")

letter = 0
word = 1
sentence = 0
for i in range(len(text)):
    if text[i].isalpha() == True:
        letter += 1
    elif text[i].isspace() == True:
        word += 1
    elif (text[i] == ".") or (text[i] == "?") or (text[i] == "!"):
        sentence += 1
l = (letter / word * 100)
s = (sentence / word * 100)
index = round(0.0588 * l - 0.296 * s - 15.8)
if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print(f"Grade {index}" )