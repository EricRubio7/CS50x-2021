#include <cs50.h>
#include <stdio.h>

//Problem Set 1 - Less Comfortable Version

int main(void)
{
    //Get pyramid height and check that is betweem the limits
    int height;
    
    do
    {
        height = get_int("What is the height of the pyramid?\n");
    }
    
    while (height < 1 || height > 8);
    
    //Print pyramid
    for (int i = 0; i < height; i++)
    
    {
        
        //Print white space for pyramid row
        for (int j = 1; j < height - i; j++)
        
        {
            printf(" ");
        }
        
        //Print hashmarks for row
        for (int k = 0; k <= i; k++)
        {
            printf("#");
        }
        printf("\n");
    }
    
}

