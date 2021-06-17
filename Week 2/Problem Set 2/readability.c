#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

//Problem Set 2: Readability

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    //Get text from user
    string text = get_string("Text: ");
    
    //Count letters
    int letters = count_letters(text);
    
    //Count words
    int words = count_words(text);
    
    //Count sentences
    int sentences = count_sentences(text);
    
    //Number of letters per 100 words
    float L = (float) letters / words * 100.0;
    
    //Number of sentences per 100 words;
    float S = (float) sentences / words * 100.0;
    
    //Calculate index and print it
    float index = 0.0588 * L - 0.296 * S - 15.8;
    
    if (index >= 1 && index <= 16)
    {
        printf("Grade %i\n", (int) round(index));
    }
    
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    
    else
    {
        printf("Grade 16+\n");
    }
    
}

int count_letters(string text)
{
    int length = strlen(text);
    int letters = 0;
    
    for (int i = 0; i < length; i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
    }
    
    return letters;
}

int count_words(string text)
{
    int length = strlen(text);
    int words = 1;
    
    for (int i = 0; i < length; i++)
    {
        if (isspace(text[i]))
        {
            words++;
        }
    }
    
    return words;
}

int count_sentences(string text)
{
    int length = strlen(text);
    int sentences = 0;
    
    for (int i = 0; i < length; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }
    
    return sentences;
}
