from cs50 import get_int

# asking and accepting the height for the pyramid from the user
while True:
    h = get_int("Height: \n")
    if h < 1 or h > 8:
        h = get_int('height: ')
    if h >= 1 or h <= 8:
        break

# Loop for left side pyramid
for i in range(h):
    print((h - 1 - i) * " ", end="")
    print((i + 1) * "#")
