#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Problem Set #2 - Substitution

int is_string_alphabetic (string key);
int char_repeats (string key);

int main (int argc, string argv[])
{
    //Check there is only one argument
    if (argc == 2)
    {
        int key_length = strlen(argv[1]);
        //Check key consists of 26 non repeating alphabetic characters
        if (key_length != 26 || is_string_alphabetic(argv[1]) != 1 || char_repeats(argv[1]) != 1)
        {
            printf("Key must constist 26 non repeating alphabetic characters\n");
            return 1;
        }
        
        
        //Make two arrays: One with the key in upper case and the other with the key in lower case
        char upper_key[key_length];
        char lower_key[key_length];
        upper_key[key_length] = '\0';
        lower_key[key_length] = '\0';
        
        for (int i = 0; i < key_length; i++)
        {
            upper_key[i] = toupper(argv[1][i]);
            lower_key[i] = tolower(argv[1][i]);
        }
        
        //Prompt user for plain text
        string plain_text = get_string("plaintext:  ");
        int plain_length = strlen(plain_text);
        
        //Convert to cipher text
        char cipher_text[plain_length];
        cipher_text[plain_length] = '\0';
        
        for (int i = 0; i < plain_length; i++)
        {
            if (isupper(plain_text[i]))
            {
                int n = (int) plain_text[i] - 65 //Gets appropiate index for encryption key
                cipher_text[i] = upper_key[n];
            }
            
            else if (islower(plain_text[i]))
            {
                int n = (int) plain_text[i] - 97; //Gets appropiate index for encryption key
                cipher_text[i] = lower_key[n];
            }
            
            else
            {
                cipher_text[i] = plain_text[i]; // If characther is not alphabetic pass it as is
            }
        }
        
        //Print results
        printf("ciphertext: %s\n", cipher_text);

    }


    //Return error code if there is more than one argument
    else
    {
        printf("Please use only one argument\n");
        return 1;
    }

}

int is_string_alphabetic(string key) //Checks if string consints of alphabetic characters
{
    int length = strlen(key);
    for (int i = 0; i < length; i++)
    {
        if (isalpha (key[i]) == 0)
        {
            return 0;
        }
    }
    return 1;
}

int char_repeats(string key) //Check if a character repeats
{
    int length = strlen(key);

    for (int i = 0; i < length; i++)
    {
        int count = 0;
        for (int j = i + 1 ; j < length; j++)
        {
            if (key[i] == toupper(key[j]) || key[i] == tolower(key[j]))
            {
                count++;
            }
        }

        if (count > 0)
        {
            return 0;
        }
    }

    return 1;
}
