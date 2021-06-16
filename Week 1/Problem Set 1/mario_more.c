#include <cs50.h>
#include <stdio.h>

//Problem set 1 - "Mario" - More Comfortable Version

int main(void)
{
    //Get pyramid height and check that is between limits
    int height;
    
    do
    {
        height = get_int("What is the height of the pyramid?\n");
    }
    while (height < 1 || height > 8);
    
    //Print whole pyramid
    for (int i = 0; i < height; i++)
    {
        //Print white space for left side of the pyramid's row
        for (int j = 1; j < height - i; j++)
        {
            printf(" ");
        }
        
        //Print left side of the row
        for (int k = 0; k <= i; k++)
        {
            printf("#");
        }
        
        //Print space between left and right side of the row
        printf("  ");
        
        //Print right side of the row
        for (int f = 0; f <= i; f++)
        {
            printf("#");
        }
        
        //Go to new line
        printf("\n");
        
    }
    
}
