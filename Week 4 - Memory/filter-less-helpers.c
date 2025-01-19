#include "helpers.h"
#include <math.h>

/*
 - only concepts learnt are utilised
 - all TODO parts are in this file only
 - all other files are pre-written
 - task: https://cs50.harvard.edu/x/2025/psets/4/filter/less/
 */

int sepia_value(float redRatio, float greenRatio, float blueRatio, BYTE rgbtRed, BYTE rgbtGreen,
                BYTE rgbtBlue);
void swap_pixel(RGBTRIPLE *leftPixel, RGBTRIPLE *rightPixel);
int sum_pixel_colours(int height, int width, RGBTRIPLE image[height][width], int pixelRow,
                      int pixelCol, int *sumRed, int *sumGreen, int *sumBlue);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // loop through each row (length is height, of img)
    for (int i = 0; i < height; i++)
    {
        // within row: loop through each pixel of row (length is width, of img)
        for (int j = 0; j < width; j++)
        {
            // each pixel: calc avg of R G B
            // these are 8 bit binaries, but math operations apparently are fine
            int sum_RGB = image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed;
            int avg_RGB = round(sum_RGB / 3.0); // int divide float to get float > round to int

            // then set all to that value (int)
            image[i][j].rgbtBlue = avg_RGB;
            image[i][j].rgbtGreen = avg_RGB;
            image[i][j].rgbtRed = avg_RGB;
        }
    }

    // filter applied to image in memory to be written out
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // loop through each row (length is height, of img)
    for (int i = 0; i < height; i++)
    {
        // within row: loop through each pixel of row (length is width, of img)
        for (int j = 0; j < width; j++)
        {
            // shorten code
            BYTE rgbtRed = image[i][j].rgbtRed;
            BYTE rgbtGreen = image[i][j].rgbtGreen;
            BYTE rgbtBlue = image[i][j].rgbtBlue;

            // get sepia colour & set
            image[i][j].rgbtBlue = sepia_value(0.272, 0.534, 0.131, rgbtRed, rgbtGreen, rgbtBlue);
            image[i][j].rgbtGreen = sepia_value(0.349, 0.686, 0.168, rgbtRed, rgbtGreen, rgbtBlue);
            image[i][j].rgbtRed = sepia_value(0.393, 0.769, 0.189, rgbtRed, rgbtGreen, rgbtBlue);
        }
    }

    return;
}

// do maths to get sepia colour (R/G/B) for pixel (int), ensure max 255 value
int sepia_value(float redRatio, float greenRatio, float blueRatio, BYTE rgbtRed, BYTE rgbtGreen,
                BYTE rgbtBlue)
{
    int newColour = round(redRatio * rgbtRed + greenRatio * rgbtGreen + blueRatio * rgbtBlue);

    if (newColour > 255)
    {
        return 255;
    }

    return newColour;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // work out half the width pixels
    int halfWidth = width / 2; // auto round down = handles odd width

    // loop through each row (length is height, of img)
    for (int i = 0; i < height; i++)
    {
        // within row: loop through HALF of pixels of row (length is width, of img)
        for (int j = 0; j < halfWidth; j++)
        {
            // index of right pixel to swap
            int rightIndex = width - 1 - j;

            // swap func to swap left & equivalent right pixels; pass in arr el addr
            swap_pixel(&image[i][j], &image[i][rightIndex]);
        }
    }

    return;
}

// pass by reference; passing in pointers to the pixels we want to swap
void swap_pixel(RGBTRIPLE *leftPixel, RGBTRIPLE *rightPixel)
{
    RGBTRIPLE temp = *leftPixel; // de-ref pointer; go to address & store pixel (in mem)
    // set the value at addr leftPixel points to = to value at addr rightPixel points to
    *leftPixel = *rightPixel;
    *rightPixel = temp;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // need a second array to hold all of the blurred pixels
    RGBTRIPLE tempImage[height][width];

    // loop through each row (length is height, of img)
    for (int i = 0; i < height; i++)
    {
        // within row: loop through each pixel of row (length is width, of img)
        for (int j = 0; j < width; j++)
        {
            // setup ints for sum of R, G, B of surrounding pixels
            int sumRed = 0;
            int sumGreen = 0;
            int sumBlue = 0;

            // run func. to sum up R, G, B of all real pixels & return pixel count for avg
            int noOfPixels =
                sum_pixel_colours(height, width, image, i, j, &sumRed, &sumGreen, &sumBlue);

            // calc int avg or R, G, B and assign to tempImage to preserve original image pixels
            tempImage[i][j].rgbtBlue = round((float) sumBlue / noOfPixels);
            tempImage[i][j].rgbtGreen = round((float) sumGreen / noOfPixels);
            tempImage[i][j].rgbtRed = round((float) sumRed / noOfPixels);
        }
    }

    // calculatd all the blurred pixels, now copy tempImage to image arr
    for (int r = 0; r < height; r++)
    {
        // within row: loop through each pixel of row (length is width, of img)
        for (int c = 0; c < width; c++)
        {
            image[r][c] = tempImage[r][c];
        }
    }

    return;
}

// sum the R, G, B values of real box pixels around current pixel, return pixel count
int sum_pixel_colours(int height, int width, RGBTRIPLE image[height][width], int pixelRow,
                      int pixelCol, int *sumRed, int *sumGreen, int *sumBlue)
{
    // box range around pixel; 1 row/col before and after
    int negRange = -1;
    int posRange = 1;

    // keep track of legit box pixels to return for division (find avg)
    int noOfBoxPixels = 0;

    // loop through each box row range; 3 = -1, 0, 1
    for (int i = negRange; i <= posRange; i++)
    {
        // within row: loop through box col pixel range
        for (int j = negRange; j <= posRange; j++)
        {
            // work out actual pixel position
            int row = pixelRow + i;
            int col = pixelCol + j;

            // ensure pixel position is legit; do summing
            if (row >= 0 && row < height && col >= 0 && col < width)
            {
                // pixel is legit, sum R/G/B colours of box pixel
                *sumRed = *sumRed + image[row][col].rgbtRed;
                *sumGreen = *sumGreen + image[row][col].rgbtGreen;
                *sumBlue = *sumBlue + image[row][col].rgbtBlue;

                // increment legit pixel count
                noOfBoxPixels++;
            }
        }
    }

    // done, return total legit box pixels count for avg calculation
    return noOfBoxPixels;
}
