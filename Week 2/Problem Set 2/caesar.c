#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Problem Set #2 - Caesar
int main (int argc, string argv[])
{
    // Check there is only one argument
    if (argc == 2)
    {
        //Check if characters are digits
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            //Return error if character is not a digit
            if (isdigit(argv[1][i]) == 0)
            {
                printf("Ussage: ./caesar key\n");
                return 1;
            }
        }

        //Get key as an integer
        int key = atoi(argv[1]);
        int shift = key % 26;

        //Prompt user for message
        string plain_text = get_string("plaintext:  ");

        //Iterate over the string and encrypt the text
        int length = strlen(plain_text);
        char cipher_text[length];
        cipher_text[length] = '\0';
        
        for (int i = 0; i < length; i++)
        {

            //Case where letter is upper case
            if (isupper(plain_text[i]))
            {
                //Shift character
                char cipher_char = plain_text[i] + shift;

                //Check if resulting character wraps over Z
                if (cipher_char <= 90) //Character does not wrap over Z
                {
                    cipher_text[i] = cipher_char;
                }
                else //Character does wrap over Z
                {
                    char wrap_shift = cipher_char - 91;
                    cipher_text[i] = 'A' + wrap_shift;
                }
            }

            //Case where letter is lower case
            else if (islower(plain_text[i]))
            {
                //Shift character
                char let = (char) plain_text[i];
                char cipher_char = (char) plain_text[i] + shift;
                int cipher_int = (int) plain_text[i] + shift; //Needed to make sure char has an ASCII representation
                
                //Check if resulting character wraps over z
                if (cipher_int <= 122)
                {
                    cipher_text[i] = cipher_char;
                }

                else //Character does wrap over z
                {
                    char wrap_shift = cipher_char - 123;
                    cipher_text[i] = 'a' + wrap_shift;
                }
            }

            else //All other cases such as '.', '0', '!'
            {
            cipher_text[i] = plain_text[i];
            }
        }

        //Print results
        printf("ciphertext: %s\n", cipher_text);
    }

    //Return error code if there is more than one argument
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}
