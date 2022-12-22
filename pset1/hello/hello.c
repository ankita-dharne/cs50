#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //Taking input from user for their name
    string name = get_string("What's your name?\n");
    
    //Printing the hello with the input name
    printf("Hello, %s\n", name);
}