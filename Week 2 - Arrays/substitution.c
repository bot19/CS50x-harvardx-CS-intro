#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

/*
 - only concepts learnt are utilised
 - task: https://cs50.harvard.edu/x/2024/psets/2/substitution/
 */

// index maps to alphabet, ie: a b c d e, etc, if 1 = present, check for duplicates
int letterDupCheck[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void encipher_print(string key, string plaintext);

int main(int argc, string argv[])
{
    // (1) get key (via Command Line Argument)
    if (argc != 2)
    {
        // validate: no key, or multiple args/key has space
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }

    // (2) validate key
    string key = argv[1];

    // (2a) check length; should be 26 length to match alphabet
    if (strlen(key) != 26)
    {
        printf("Error: key must contain 26 characters.\n");
        return 1; // error status
    }

    for (int i = 0, l = strlen(key); i < l; i++)
    {
        char keyLetter = tolower(key[i]);

        // (2b) check non-alphabetic char
        if (!(keyLetter >= 'a' && keyLetter <= 'z'))
        {
            printf("Error: key must contain only letters.\n");
            return 1;
        }
        else
        {
            // is a letter, ensure no duplicates
            int alphabetIndex = keyLetter - 'a';

            // (2c) check any duplicate chars
            if (letterDupCheck[alphabetIndex] > 0)
            {
                printf("Error: key must contain each alphabetical letter once.\n");
                return 1;
            }
            else
            {
                letterDupCheck[alphabetIndex] = 1;
            }
        }
    }

    // (3) get plaintext
    string plaintext = get_string("plaintext:  ");

    // (4) encipher & print ciphertext
    encipher_print(key, plaintext);

    // printf("key: %s\ntext: %s\n", key, plaintext);
    return 0;
}

void encipher_print(string key, string plaintext)
{
    int textLength = strlen(plaintext);
    char cipertext[textLength];

    // (4a) map each alphabetical letter
    for (int i = 0; i < textLength; i++)
    {
        // current letter
        char letter = plaintext[i];
        int alphabetIndex = tolower(letter) - 'a';

        // (4b) preserve case for letters
        if (letter >= 'A' && letter <= 'Z')
        {
            // uppercase
            cipertext[i] = toupper(key[alphabetIndex]);
        }
        else if (letter >= 'a' && letter <= 'z')
        {
            // lowercase
            cipertext[i] = tolower(key[alphabetIndex]);
        }
        else
        {
            // (4c) leave non-alphabetic chars as-is
            cipertext[i] = letter;
        }
    }

    // add on string end char as cipertext initialised as array, not string
    cipertext[textLength] = '\0';

    // (5) print ciphertext
    printf("ciphertext: %s\n", cipertext);
}
