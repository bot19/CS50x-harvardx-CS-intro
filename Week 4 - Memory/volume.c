// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/*
 - only concepts learnt are utilised
 - parts pre-written, only complete TODO parts
 - task: https://cs50.harvard.edu/x/2025/psets/4/volume/
 */

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    // fixed 44 bytes size, direct copy (without modification)
    // 1st 44 bytes of file = header, from input file

    // get 44 bytes of mem to store; array ok; don't need malloc as size known
    uint8_t header[HEADER_SIZE]; // array of type: unsigned 8 bit/1 byte (told to use)

    // read input's header into memory
    fread(header, HEADER_SIZE, 1, input); // "header" arr gives address of arr[0] in memory

    // write out this 44 bytes into output file, as is
    fwrite(header, HEADER_SIZE, 1, output);

    // TODO: Read samples from input file and write updated data to output file
    // current position: post header/44 bytes, at seq of samples to end of file

    // samples are 2 bytes each; 16 bit/2 byte int, signed; -ve, 0, +ve
    int16_t sample;

    // loop through, until end, reading in each sample
    while (fread(&sample, sizeof(sample), 1, input) != 0)
    {
        // modify sample by input volume value
        sample = sample * factor;

        // write out modified sample to output file
        fwrite(&sample, sizeof(sample), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
