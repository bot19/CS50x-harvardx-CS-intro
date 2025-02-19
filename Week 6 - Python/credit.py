from cs50 import get_int

# adapt my credit C program into Python
# task: https://cs50.harvard.edu/x/2025/psets/6/credit/

# (1) get the CC number
while True:
    ccNumber = get_int("Number: ")
    if ccNumber > 0:
        break

# (2) get length of CC number vars
ccLength = 0
ccNumberReduce = ccNumber

# (3) CC number checksum vars
isAddSet = True  # digits to be added only, starts last number
addSetTotal = 0
timesAddSetTotal = 0

# (final) to store 1st and 2nd CC number digits
# need to assign value, but don't want to use 0 as it's a valid number
lastDigit = -1  # 1st CC number digit, as going right-to-left
secondLastDigit = -1  # 2nd CC number digit, as above

# do while loop for (2) and (3)
while True:
    # print(f"Find CC No. length: {ccNumberReduce} / {ccLength}")

    # (3) CC number checksum
    currentDigit = ccNumberReduce % 10  # current digit of CC number
    # which set of number is digit for? addSet or TimesAddSet?
    if isAddSet:
        # addSet: digits 0-9, only gets added, starts at last number
        addSetTotal = addSetTotal + currentDigit

        # ready for next digit for TimesAddSet
        isAddSet = False
    else:
        # TimesAddSet: starts second last digit, *2, split digits, sum up
        digitDoubled = currentDigit * 2

        # split digitDoubled if now 10+
        if digitDoubled > 9:
            # add to total 1st digit: 1 (10-18) & the 2nd digit
            timesAddSetTotal = timesAddSetTotal + 1 + (digitDoubled % 10)
        else:
            timesAddSetTotal = timesAddSetTotal + digitDoubled

        # ready for next digit for addSet
        isAddSet = True

    # for (final) CC type checks, store last & second last digits
    secondLastDigit = lastDigit
    lastDigit = currentDigit

    # (2) get length of CC number
    # reduces cc number by 1 digit as only take integers (ignore decimals)
    ccNumberReduce = ccNumberReduce // 10
    ccLength += 1  # count the number of digits

    # at integer 0, ie: (last digit) 4 / 10 = 0.4 = 0, we are done
    if ccNumberReduce <= 0:
        break

# (3) checksum number continuned: sum the set totals for final modulus
checksumSetsTotal = addSetTotal + timesAddSetTotal

# (final) output type of CC or invalid
if checksumSetsTotal % 10 == 0:
    # (3) if last digit in checksum total = 0 = passed = here; otherwise fail/exit (else)

    # (4) base on length & 1st 2 digits, work out which type of CC
    if (ccLength == 15 and lastDigit == 3 and (secondLastDigit == 4 or secondLastDigit == 7)):
        # AMEX
        print("AMEX")
    elif (lastDigit == 4 and (ccLength == 13 or ccLength == 16)):
        # Visa
        print("VISA")
    elif (ccLength == 16 and lastDigit == 5 and (secondLastDigit == 1 or secondLastDigit == 2 or secondLastDigit == 3 or secondLastDigit == 4 or secondLastDigit == 5)):
        # MasterCard
        print("MASTERCARD")
    else:
        # not any type of CC
        print("INVALID")
else:
    print("INVALID")
