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

// Reflect image horizontally
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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //Store orignal image
    RGBTRIPLE copyOfImage[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copyOfImage[i][j] = image[i][j];
        }
    }

    //Make sobel arrays
    int Gx[3][3] = {{-1, 0 ,1}, {-2, 0, 2}, {-1, 0 ,1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2 ,1}};

    //Iterate over image
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            //Initialize variable to store new values for channels
            float gxBlue = 0;
            float gxGreen = 0;
            float gxRed = 0;
            float gyBlue = 0;
            float gyGreen = 0;
            float gyRed = 0;

            //Now Calculate the gxs
            //We use the sobel operator over the surrounding pixels in this pattern
            //x current pixel, o surrounding pixels
            //ooo
            //oxo
            //ooo
            //For sorrounding pixels that are outside of the image boundaries, assume a black pixel (Channel values at 0)


            for (int ii = -1; ii < 2; ++ii)
            {
                for (int jj = -1; jj < 2; jj++)
                {
                //Check for pixels outside edges
                if (i + ii >= height || i + ii < 0 || j + jj >= width || j + jj < 0)
                {
                    continue;
                }

                //Apply Sobel operator to pixels
                gxBlue += copyOfImage[i + ii][j + jj].rgbtBlue * Gx[ii + 1][jj + 1];
                gxGreen += copyOfImage[i + ii][j + jj].rgbtGreen * Gx[ii + 1][jj + 1];
                gxRed += copyOfImage[i + ii][j + jj].rgbtRed * Gx[ii + 1][jj + 1];
                gyBlue += copyOfImage[i + ii][j + jj].rgbtBlue * Gy[ii + 1][jj + 1];
                gyGreen += copyOfImage[i + ii][j + jj].rgbtGreen * Gy[ii + 1][jj + 1];
                gyRed += copyOfImage[i + ii][j + jj].rgbtRed * Gy[ii + 1][jj + 1];
                }
            }

            //Combine Gx and Gy values
            int newBlue = round(sqrt(gxBlue *gxBlue + gyBlue * gyBlue));
            int newGreen = round(sqrt(gxGreen *gxGreen + gyGreen * gyGreen));
            int newRed = round(sqrt(gxRed *gxRed + gyRed * gyRed));

            //Check values don't go over treshold value
            if(newBlue > 255)
            {
                newBlue = 255;
            }
            if(newGreen > 255)
            {
                newGreen = 255;
            }
            if(newRed > 255)
            {
                newRed = 255;
            }

            //Change "image" with new values for the channels
            image[i][j].rgbtBlue = newBlue;
            image[i][j].rgbtGreen = newGreen;
            image[i][j].rgbtRed = newRed;
        }
    }

    return;
}
