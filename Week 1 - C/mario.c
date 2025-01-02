#include <cs50.h>
#include <stdio.h>

// let C know about this function
void printChar(bool printHash, bool useSpaces);

int main(void)
{
    // Prompt user for positive integer 1-8
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // print pyramid rows
    for (int i = 0; i < height; i++)
    {
        // print pyramid row columns: left side
        for (int left = 0; left < height; left++)
        {
            // using height var (adjust 0-base) & current row
            // to work out which col index to draw # for pyramid
            int indexToPrintHash = height - 1 - i;
            // ie: for 4 height:
            // row 0 (3 - 0 = 3), 0 1 2 #
            // row 1 (3 - 1 = 2), 0 1 # #
            // row 2 (3 - 2 = 1), 0 # # #
            // row 3 (3 - 3 = 0), # # # #
            printChar(indexToPrintHash <= left, true);
        }

        // spacing between left right side
        printf("  ");

        // print pyramid row columns: right side
        for (int right = 0; right < height; right++)
        {
            // logic simpler: print number of hash as row index
            printChar(right <= i, false);
        }

        // make new line
        printf("\n");
    }
}

// abstract character printing into function
void printChar(bool printHash, bool useSpaces)
{
    if (printHash)
    {
        printf("#");
    }
    else
    {
        // pyramid left side to print spaces & not for right side
        if (useSpaces)
        {
            printf(" ");
        }
    }
}
