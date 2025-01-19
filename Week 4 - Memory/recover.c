#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <stdint.h>

/*
 - only concepts learnt are utilised
 - task: https://cs50.harvard.edu/x/2025/psets/4/recover/
 */

bool jpeg_start(uint8_t buffer[]);

int main(int argc, char *argv[])
{
    // Accept a single command-line argument: ./recover card.raw
    // if wrong args, remind + exit status 1
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card: fopen
    FILE *memCard = fopen(argv[1], "r");

    // if file cannot be opened, exit status 1
	if (!memCard)
	{
		printf("Could not open file, check and try again\n");
        return 1;
	}

    // memCard stores data in 512 byte blocks, setup memory for this
    int BLOCK_SIZE = 512;
    uint8_t buffer[BLOCK_SIZE];

    // setup JPEG filename & numbering
    char filename[8]; // filename = 000.jpg\0 & increment
    int jpegNo = 0;

    // setup pointer to data in memory to be opened & written
    FILE *img = NULL;

    // While there's still data left to read from the memory card
    // fread returns number of bytes it read, should return 512 or 0; 0 = end
    while (fread(buffer, BLOCK_SIZE, 1, memCard) != 0)
	{
        // Create JPEGs from the data

        // check for start of JPEG
        bool startOfJpeg = jpeg_start(buffer);

        // start of JPEG?
        if (startOfJpeg)
        {
            // need to write to new JPEG file

            // if not 1st JPEG, start new JPEG, but need to close cur JPEG 1st
            if (jpegNo > 0 && img != NULL)
            {
                fclose(img);
            }

            // print to string, required to open file to write to it
            sprintf(filename, "%03i.jpg", jpegNo);

            // open JPEG file in write mode
            img = fopen(filename, "w");

            // check file opened successfully, otherwise terminate
            if (img == NULL)
            {
                printf("Could not open JPEG file :(\n");
                return 1;
            }

            // write to this JPEG file
            fwrite(buffer, BLOCK_SIZE, 1, img);

            // done, increment JPEG no. so we don't end up here
            jpegNo++;
        }
        else
        {
            // not a new JPEG, either middle of one or before 1st JPEG
            if (img != NULL)
            {
                // in the middle of a JPEG, continue writing to it
                fwrite(buffer, BLOCK_SIZE, 1, img);
            }
        }
	}

    // if any JPEG opened, close it
    fclose(img);

    // business done, close memCard
	fclose(memCard);
}

// work out if start of JPEG given the 512 buffer, param: address of arr 1st el
bool jpeg_start(uint8_t buffer[])
{
    // start of JPEG: 0xff, 0xd8, 0xff, and 4th value: 0xe0, 0xe1, 0xe2, 0xe3 ... 0xef
    // use bitwise arithmetic to ensure 4th value has 0xeX part; ie: 1110XXXX
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
       (buffer[3] & 0xf0) == 0xe0)
    {
        return true;
    }

    return false;
}
