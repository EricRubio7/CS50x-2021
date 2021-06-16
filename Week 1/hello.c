#include <cs50.h>
#include <stdio.h>
int main(void)
{
    //Gets person's name
    string name = get_string("What is your name?\n");
    printf("hello, %s\n", name);
}
