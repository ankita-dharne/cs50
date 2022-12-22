#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    //Check for whether user provides no command-line arguments, or two or more
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }


    int key = atoi(argv[1]);

    if (key < 0)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    //getting input for plaintext that needs encryption
    string plaintext = get_string("plaintext: ");
    //Calculating the length of plaintextstyle50 caesar.c
    int n = strlen(plaintext);

    printf("ciphertext: ");

    // pi is the ith character in plaintext, and k is a secret key, then each letter, ci, in the ciphertext, c, is computed as
    //ci = (pi + k) %  in following block
    for (int i = 0; i < n; i++)
    {
        if (isalpha(plaintext[i]) != 0)
        {
            if (isupper(plaintext[i]) != 0)
            {
                printf("%c", ((plaintext[i] - 'A' + key) % 26) + 'A');
            }
            else
            {
                printf("%c", ((plaintext[i] - 'a' + key) % 26) + 'a');
            }
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
}