#include <cs50.h>
#include <stdio.h>

int main(void)
{   
    //initialization of variables
    int count = 2;
    int sum = 0;
    //accepting the input from the user
    long card = get_long("enter card number: ");
    long temp = card;
    long temp2 = card;
    
    //loop foro checking the length of input entered & for taking the first three digit for validation of card
    while (temp > 100)
    {
        temp = temp / 10;
        count ++;
    }
    //luhn algorithm 
    for (int i = 1; i <= count; i++)
    {   
        //taking modulo of input for each digit
        int digit = temp2 % 10;
        //condition for checking the seconds/ even position in number
        if (i % 2 == 0)
        {   
            //condition for checking if the multiplication of digit exceeds 9
            if (digit * 2 > 9)
            {   
                //adding the digit of product of 2 which exceeds 9
                int d = 0;
                d += ((digit * 2) / 10);
                d += ((digit * 2) % 10);
                sum += d;
            }
            else
            {   
                //multiplying other digit by 2 and addings them together
                sum += digit * 2;
            }
            
        }
        else 
        {   
            //adding odd posiiton digits with the sum
            sum += digit;
        }
        
        temp2 = temp2 / 10;
    }
    //block for checking the valid credit card number and company
    if (sum % 10 == 0)
    { 
        if ((count == 15) && (temp == 34 || temp == 37))
        {
            printf("AMEX\n");
        }
        else if ((count == 16) && (temp > 50 && temp < 56))
        {
            printf("MASTERCARD\n");
        }
        else if ((count == 13 || count == 16)  && (temp / 10 == 4))
        {
            printf("VISA\n");
        } 
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
    
}