#include<cs50.h>
#include<stdio.h>

int main(void)
{
    //initializing all the variables used
    int n, i, j;
    do
    {
        //asking and accepting the height for the pyramid from the user
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8); //checking for the number to non negative and no more greater than 8
    
    //Loop for forming the rows of the pyramid
    for (i = 0; i < n; i++)
    {   
        //Loop for space before the right aligned pyramid
        for (j = 0; j < n - i - 1; j++)
        {
            printf(" ");
        }
        // Loop for right aligned pyramid
        for (j = 0; j < i + 1; j++)
        {
            printf("#");
        }
        // space between the left aligned and right aligned pyrmaid to give a complete pyramid
        printf("  ");
        // Loop for left aligned pyramid
        for (j = 0; j < i + 1; j++)
        {
            printf("#");
        }
        //for entering new line
        printf("\n");
    }
}