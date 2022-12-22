#include <stdio.h>
#include <string.h>
#include <math.h>
#include <cs50.h>


int main(void)
{
    //initialization
    int len, letters = 0, sentences = 0, words = 1;


    // Get input
    string text = get_string("Text : ");
    len = strlen(text);

    for (int i = 0; i < len; i++)


    {
        //Count letters with the help of ASCII
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
        {
            letters++;
        }

        //Count words with every space encountered
        //first word doesn't have space
        if (text[i] == ' ')
        {
            words++;
        }


        //Count sentences with every encountered period, ! & question mark
        if (text[i] == '!' || text[i] == '.' || text[i] == '?')
        {
            sentences++;
        }

    }

    //average of letters and sentences per 100 words
    float L = (100 * ((float) letters / (float) words));
    float S = (100 * ((float) sentences / (float) words));

    //Calculate Coleman-Liau index
    float index0 = (0.0588 * L) - (0.296 * S) - 15.8;
    int index = (round(index0));

    //Result
    if (index >= 1 && index < 16)
    {
        printf("Grade %i", (int) index);
    }
    else if (index < 1)
    {
        printf("Before Grade 1");
    }
    else
    {
        printf("Grade 16+");
    }
    printf("\n");
}