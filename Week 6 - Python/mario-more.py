from cs50 import get_int

# adapt my mario-more C program into Python
# task: https://cs50.harvard.edu/x/2025/psets/6/mario/more/

def main():
    # Prompt user for positive integer 1-8
    while True:
        height = get_int("Height: ")
        if height > 0 and height < 9:
            break

    # print pyramid rows
    for i in range(height):
        # print pyramid row columns: left side
        for left in range(height):
            # using height var (adjust 0-base) & current row
            # to work out which col index to draw # for pyramid
            indexToPrintHash = height - 1 - i
            # ie: for 4 height:
            # row 0 (3 - 0 = 3), 0 1 2 #
            # row 1 (3 - 1 = 2), 0 1 # #
            # row 2 (3 - 2 = 1), 0 # # #
            # row 3 (3 - 3 = 0), # # # #
            printChar(indexToPrintHash <= left, True)

        # spacing between left right side
        print("  ", end="")

        # print pyramid row columns: right side
        for right in range(height):
            # logic simpler: print number of hash as row index
            printChar(right <= i, False)

        # make new line
        print("")

# abstract character printing into function
def printChar(printHash, useSpaces):
    if printHash:
        print("#", end="")
    else:
        # pyramid left side to print spaces & not for right side
        if (useSpaces):
            print(" ", end="")


main()
