#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) //Loop through rows
    {
        for (int j = 0; j < width; j++) //Loop through colums
        {
            float pixelSum = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed);
            int avgPixelvalue = round(pixelSum / 3);
            image[i][j].rgbtBlue = avgPixelvalue;
            image[i][j].rgbtGreen = avgPixelvalue;
            image[i][j].rgbtRed = avgPixelvalue;
        }
    }


    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) //Loop through rows
    {
        for (int j = 0; j < width; j++) //Loop through colums
        {
            
            //Make Sepia pixels
            int sepiaBlue = (int) round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            int sepiaGreen = (int) round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            int sepiaRed = (int) round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            //Change original pixels into sepia pixels
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }

    return;
}

//Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++) //Loop trough rows
    {
        for (int j = 0; j < width / 2; j++) //Loop through columns
        {
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    //Store a copy of the original image
    RGBTRIPLE copyOfImage[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copyOfImage[i][j] = image[i][j];
        }
    }


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            //Initialize where new value for the pixel colors will be stored
            float newBlue = 0;
            float newGreen = 0;
            float newRed = 0;


            //Initialize variables that will be used to make a "box" of pixels
            int hBox = 0; //Height of box
            int wBox = 0; //Width of box
            int totalBoxPixels = 0; // Total amount of pixels in the box or hBox * wBox

            //Conditional branches do:
            //1) Identify edge cases for pixels
            //2) Calculates the new pixel value as appropiate for the pixel case

            if (i == 0 && j == 0) //Upper left corner pixel
            {
                //Box Pattern - Where x = current pixel o = sorrounding pixels
                //2x2 Box
                //xo
                //oo
                hBox = 2;
                wBox = 2;
                //int totalPixels = h_box * w_box; We can move this out
                for (int ii = 0; ii < hBox; ii++) //Loop through rows of box
                {
                    for (int jj = 0; jj < wBox; jj++) //Loop through colums of box
                    {
                        newBlue += copyOfImage[ii][jj].rgbtBlue;
                        newGreen += copyOfImage[ii][jj].rgbtGreen;
                        newRed += copyOfImage[ii][jj].rgbtRed;
                    }
                }
            }
            else if (i == 0 && j > 0 && j < width - 1) //First row excluding corners
            {
                //Box Pattern - Where x = current pixel o = sorrounding pixels
                //2x3 Box
                //oxo
                //ooo
                hBox = 2;
                wBox = 3;
                for (int ii = 0; ii < hBox; ii++) //Loop through rows of box
                {
                    for (int jj = -1; jj < wBox - 1; jj++) //Loop through colums of box - Columns:j - 1, j + 0, j + 1
                    {
                        newBlue += copyOfImage[ii][j + jj].rgbtBlue;
                        newGreen += copyOfImage[ii][j + jj].rgbtGreen;
                        newRed += copyOfImage[ii][j + jj].rgbtRed;
                    }
                }
            }
            else if (i == 0 && j == width - 1) //Upper right corner pixel
            {

                //Box Pattern - Where x = current pixel o = sorrounding pixels
                //2x2 Box
                //xo
                //oo
                hBox = 2;
                wBox = 2;
                for (int ii = 0; ii < hBox; ii++) //Loop through rows of box
                {
                    for (int jj = -1; jj < wBox - 1; jj++) //Loop through colums of box - Columns:j - 1, j + 0
                    {
                        newBlue += copyOfImage[ii][j + jj].rgbtBlue;
                        newGreen += copyOfImage[ii][j + jj].rgbtGreen;
                        newRed += copyOfImage[ii][j + jj].rgbtRed;
                    }
                }
            }
            else if (i > 0 && i < height - 1 && j == 0) //Left edge excluding corners
            {
                //Box Pattern - Where x = current pixel o = sorrounding pixels
                //3x2 Box
                //oo
                //xo
                //oo
                hBox = 3;
                wBox = 2;
                for (int ii = -1; ii < hBox - 1; ii++) //Loop through rows of box
                {
                    for (int jj = 0; jj < wBox ; jj++) //Loop through colums of box
                    {
                        newBlue += copyOfImage[i + ii][jj].rgbtBlue;
                        newGreen += copyOfImage[i + ii][jj].rgbtGreen;
                        newRed += copyOfImage[i + ii][jj].rgbtRed;
                    }
                }
            }
            else if (i > 0 && i < height - 1 && j > 0 && j < width - 1) //Body
            {
                //Box Pattern - Where x = current pixel o = sorrounding pixels
                //3x3 Box
                //ooo
                //oxo
                //ooo
                hBox = 3;
                wBox = 3;
                for (int ii = -1; ii < hBox - 1; ii++) //Loop through rows of box
                {
                    for (int jj = -1; jj < wBox - 1; jj++) //Loop through colums of box
                    {
                        newBlue += copyOfImage[i + ii][j + jj].rgbtBlue;
                        newGreen += copyOfImage[i + ii][j + jj].rgbtGreen;
                        newRed += copyOfImage[i + ii][j + jj].rgbtRed;
                    }
                }
            }
            else if (i > 0 && i < height - 1 && j == width - 1) //Right edge excluding corners
            {
                //Box Pattern - Where x = current pixel o = sorrounding pixels
                //3x2 Box
                //oo
                //ox
                //oo
                hBox = 3;
                wBox = 2;
                for (int ii = -1; ii < hBox - 1; ii++) //Loop through rows of box
                {
                    for (int jj = -1; jj < wBox - 1; jj++) //Loop through columns of box
                    {
                        newBlue += copyOfImage[i + ii][j + jj].rgbtBlue;
                        newGreen += copyOfImage[i + ii][j + jj].rgbtGreen;
                        newRed += copyOfImage[i + ii][j + jj].rgbtRed;
                    }
                }
            }
            else if (i == height - 1 && j == 0) //Lower left corner pixel
            {
                //Box Pattern - Where x = current pixel o = sorrounding pixels
                //2x2 Box
                //oo
                //xo
                hBox = 2;
                wBox = 2;
                for (int ii = -1; ii < hBox - 1; ii++) //Loop through rows of box
                {
                    for (int jj = 0; jj < wBox ; jj++) //Loop through columns of box
                    {
                        newBlue += copyOfImage[i + ii][j + jj].rgbtBlue;
                        newGreen += copyOfImage[i + ii][j + jj].rgbtGreen;
                        newRed += copyOfImage[i + ii][j + jj].rgbtRed;
                    }
                }
            }
            else if (i == height - 1 && j > 0 && j < width - 1) //Last row excluding corners
            {
                //Box Pattern - Where x = current pixel o = sorrounding pixels
                //2x3 Box
                //ooo
                //oxo
                hBox = 2;
                wBox = 3;
                for (int ii = -1; ii < hBox - 1; ii++) //Loop through rows of box
                {
                    for (int jj = -1; jj < wBox - 1; jj++) //Loop through columns of box
                    {
                        newBlue += copyOfImage[i + ii][j + jj].rgbtBlue;
                        newGreen += copyOfImage[i + ii][j + jj].rgbtGreen;
                        newRed += copyOfImage[i + ii][j + jj].rgbtRed;
                    }
                }
            }
            else if (i == height - 1 && j == width - 1) //Lower right corner pixel
            {
                //Box Pattern - Where x = current pixel o = sorrounding pixels
                //2x Box
                //oo
                //ox
                hBox = 2;
                wBox = 2;
                for (int ii = -1; ii < hBox - 1; ii++) //Loop through rows of box
                {
                    for (int jj = -1; jj < wBox - 1; jj++) //Loop through columns of box
                    {
                        newBlue += copyOfImage[i + ii][j + jj].rgbtBlue;
                        newGreen += copyOfImage[i + ii][j + jj].rgbtGreen;
                        newRed += copyOfImage[i + ii][j + jj].rgbtRed;
                    }
                }
            }

            totalBoxPixels = hBox * wBox; //Calclate size of box to average value

            //Get average value for pixel and adjust below treshold value if needed
            int avgBlue = round(newBlue / totalBoxPixels);
            if (avgBlue > 255)
            {
                avgBlue = 255;
            }
            int avgGreen = round(newGreen / totalBoxPixels);
            if (avgGreen > 255)
            {
                avgGreen = 255;
            }
            int avgRed = round(newRed / totalBoxPixels);
            if (avgRed > 255)
            {
                avgRed = 255;
            }

            //Assign new value to image
            image[i][j].rgbtBlue = avgBlue;
            image[i][j].rgbtGreen = avgGreen;
            image[i][j].rgbtRed = avgRed;
        }
    }
    return;
}
