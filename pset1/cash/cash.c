#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{   
    //Initializing the variables
    float change;
    int count = 0; //counter for calculating the cents required
    do
    {   
        //accepting the input from user for the amount owed
        change = get_float("How much change is owed?\n");
    }
    while (change < 0);  //condition to ensure positive values only
    
    //rounding up the accepted input
    int cents = round(change * 100);
    
    //loop to ensure the algorithm is carry until the amount is equal to 0
    while (cents > 0)
    {   
        //condition to check if the amount is enough to carry out the calculation
        if (cents >= 25)
        {
            cents = cents - 25; //subtracting the 25 from actual amount
            count++; //updating the counter
        }
        else if (cents >= 10)
        {
            cents = cents - 10;  //subtracting the 10 from actual amount
            count++; //updating the counter
        }
        else if (cents >= 5)
        {
            cents = cents - 5;  //subtracting the 5 from actual amount
            count++; //updating the counter
        }
        else
        {
            cents = cents - 1;  //subtracting the 1 from actual amount
            count++; //updating the counter
        }
    }
    //printing out the actual cents required
    printf("minimum number of coins possible: %d\n", count);
    
}