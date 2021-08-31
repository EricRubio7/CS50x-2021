#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


typedef uint8_t BYTE; //New type to store a byte of data
const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{

    //Check command line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover card.raw\n");
        return 1;
    }
    
    //Open file and return an error message if file cannot be opened
    char *input_name = argv[1];
    FILE *input = fopen(input_name, "r");
    if (input == NULL)
    {
        printf("Could not open file. \n");
        return 2;
    }
    
    int jpegCount = 0; //To count jpegs
    BYTE buffer[BLOCK_SIZE]; //Buffer is an array of size 512 BYTEs
    char filename[8]; //Create new string to store file name
    FILE *img = NULL; //Create pointer for new images

    while (fread(&buffer, sizeof(buffer), 1, input) == 1)
    {
       
        //Check the first 4 bytes to identify if block is a jpeg image
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            
            sprintf(filename, "%03i.jpg", jpegCount); //Make "filename" string
            
            if (jpegCount == 0) //Case for first image
            {
                //Write bufffer to new image
                img = fopen(filename, "w");
                fwrite(&buffer, sizeof(buffer), 1, img);
            }
            else
            {
                //Close previous image and open and write a new one
                fclose(img); 
                img = fopen(filename, "w");
                fwrite(&buffer, sizeof(buffer), 1, img); 
            }
            jpegCount++;
        }
        else //Block is not the start of a new jpeg
        {
            if (jpegCount != 0) //Continue writing on current jpeg
            {
                fwrite(&buffer, sizeof(buffer), 1, img);
            }
        }
    }
    //Close all files
    fclose(input);
    fclose(img);
    
    return 0;
}
