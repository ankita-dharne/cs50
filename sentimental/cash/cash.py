from cs50 import get_float

# counter for calculating the cents required
count = 0
while (True):
    # condition to ensure positive values only
    change = get_float("How much change is owed?\n")
    if (change > 0):
        break
# rounding up the accepted input
cents = round(int(change * 100))

# loop to ensure the algorithm is carry until the amount is equal to 0
while (cents > 0):
    # condition to check if the amount is enough to carry out the calculation
    if (cents >= 25):
        # subtracting the 25 from actual amount
        cents = cents - 25
        # updating the counter
        count = count + 1
    elif (cents >= 10):
        # subtracting the 10 from actual amount
        cents = cents - 10
        # updating the counter
        count = count + 1
    elif (cents >= 5):
        # subtracting the 5 from actual amount
        cents = cents - 5
        # updating the counter
        count = count + 1
    else:
        # subtracting the 1 from actual amount
        cents = cents - 1
        # updating the counter
        count = count + 1
# printing out the actual cents required
print("minimum number of coins possible:", count)