#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

/*
 - only concepts learnt are utilised
 - task: https://cs50.harvard.edu/x/2024/psets/2/scrabble/
 */

int calculate_points(string word);

int main(void)
{
    // get the 2 words
    string words[2];

    // could use individual vars
    // doing this hints at looping for additional players as extension
    words[0] = get_string("Player 1: ");
    words[1] = get_string("Player 2: ");

    // vars to hold points total
    int points[2];
    points[0] = 0;
    points[1] = 0;

    // calculate total letter points for each word
    points[0] = calculate_points(words[0]);
    points[1] = calculate_points(words[1]);

    // printf("Player 1: %s %i, Player 2: %s %i\n", words[0], points[0], words[1], points[1]);

    // print the winner
    if (points[0] > points[1])
    {
        printf("Player 1 wins!\n");
    }
    else if (points[1] > points[0])
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

/*
 - shorter way to calc points is to use points in array (global)
 - ie: int POINTS[] = {1, 3, 3, ... 8, 4, 10};
 - and minus 'A' from current letter to get alphabet index (see ASCII table)
 - ie: score += POINTS[word[i] - 'A'];
 - ie: if you had C, C - A would give you like 2, POINTS[2] = 3, etc
 */
int calculate_points(string word)
{
    int wordPoints = 0;

    for (int j = 0, l = strlen(word); j < l; j++)
    {
        // ensure letter is uppercase (UC)
        char upperCaseChar = toupper(word[j]);

        // if UC char, proceed; to exclude punctuation, numbers, etc
        if (upperCaseChar >= 'A' && upperCaseChar <= 'Z')
        {
            // 5 = K
            if (upperCaseChar == 'K')
            {
                wordPoints += 5;
            }
            // 8 = J X
            else if (upperCaseChar == 'J' || upperCaseChar == 'X')
            {
                wordPoints += 8;
            }
            // 10 = Q Z
            else if (upperCaseChar == 'Q' || upperCaseChar == 'Z')
            {
                wordPoints += 10;
            }
            // 2 = D G
            else if (upperCaseChar == 'D' || upperCaseChar == 'G')
            {
                wordPoints += 2;
            }
            // 3 = B C M P
            else if (upperCaseChar == 'B' || upperCaseChar == 'C' || upperCaseChar == 'M' ||
                     upperCaseChar == 'P')
            {
                wordPoints += 3;
            }
            // 4 = F H V W Y
            else if (upperCaseChar == 'F' || upperCaseChar == 'H' || upperCaseChar == 'V' ||
                     upperCaseChar == 'W' || upperCaseChar == 'Y')
            {
                wordPoints += 4;
            }
            // 1 = A E I L N O R S T U
            else
            {
                wordPoints += 1;
            }
        }
    }

    // return totalled points
    return wordPoints;
}
