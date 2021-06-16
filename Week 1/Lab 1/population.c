#include <cs50.h>
#include <stdio.h>

//Lab 1 - Population Growth

int main(void)
{

    int startSize;
    // TODO: Prompt for start size
    do
    {
        startSize = get_int("What is the population start size? ");
    }
    while (startSize < 9);
    
    // TODO: Prompt for end size
    int endSize;
    do
    {
        endSize = get_int("What is the population end size? ");
    }
    while (endSize < startSize);

    // TODO: Calculate number of years until we reach threshold
    int currentSize = startSize;
    int Years = 0;
    while (currentSize < endSize){
        currentSize = currentSize + currentSize/3 - currentSize/4;
        Years++;
    }

    // TODO: Print number of years
    printf("Start size: %i\n", startSize);
    printf("End size: %i\n", endSize);
    printf("Years: %i\n", Years);
}
