#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

/*
 - only concepts learnt are utilised
 - task: https://cs50.harvard.edu/x/2024/psets/2/readability/
 */

// could abstract, but logic pretty simple. Leaving as is.
int main(void)
{
    // get text
    string text = get_string("Text: ");

    // calc letters, words, sentences
    int letters = 0;
    int words = 1; // accommodates last sentence not counted in logic
    int sentences = 0;

    for (int i = 0, l = strlen(text); i < l; i++)
    {
        char currentChar = text[i];

        // (1) get letters count
        // only count letters
        if ((currentChar >= 'a' && currentChar <= 'z') ||
            (currentChar >= 'A' && currentChar <= 'Z'))
        {
            // printf("%c\n", currentChar);
            letters += 1;
        }

        // (2) get words count; 32 is space character
        if (currentChar == 32)
        {
            words += 1;
        }

        // (3) get sentences count
        if (currentChar == '.' || currentChar == '!' || currentChar == '?')
        {
            sentences += 1;
        }
    }

    // get ratios per 100 words
    float wordRatio = 100 / (float) words;
    float letterRatio = (float) letters * wordRatio;
    float sentencesRatio = (float) sentences * wordRatio;

    // work out grade
    float index = 0.0588 * letterRatio - 0.296 * sentencesRatio - 15.8;

    // printf("L %i / W %i / S %i / RW %f / G %f\n", letters, words, sentences, wordRatio, index);

    // print grade logic
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) round(index));
    }
}
