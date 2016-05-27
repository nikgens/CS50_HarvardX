#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    int quarter = 25; 
    int dime = 10; 
    int nickel = 5; 
    int pennie = 1; 
    int counter = 0;
    
    printf("O hai! How much change is owed?\n");
    float amount  = GetFloat();
    while ( amount <= 0 )
    {
        printf("How much change is owed?\n");
        amount  = GetFloat();
    }
    int amountRound = round(amount*100);
    //printf("You amountRound is: %i\n", amountRound);
    if (amountRound >= quarter)
    {
        do 
        {
            amountRound = amountRound - quarter;
            counter++;
        } 
        while (amountRound >= quarter);
        //printf("You amountRound after quarter is: %i\n", amountRound);
        //printf("You counter is: %i\n", counter);
    }
    
    if (amountRound >= dime)
    {
        do 
        {
            amountRound = amountRound - dime;
            counter++;
        } 
        while (amountRound >= dime);
        //printf("You amountRound after dime is: %i\n", amountRound);
        //printf("You counter is: %i\n", counter);
    }
    
    if (amountRound >= nickel)
    {
        do 
        {
            amountRound = amountRound - nickel;
            counter++;
        } 
        while (amountRound >= nickel);
        //printf("You amountRound after nickel is: %i\n", amountRound);
        //printf("You counter is: %i\n", counter);
    }  
    
    if (amountRound >= pennie)
    {
        do 
        {
            amountRound = amountRound - pennie;
            counter++;
        } 
        while (amountRound >= pennie);
        //printf("You amountRound after pennie is: %i\n", amountRound);
        //printf("You counter is: %i\n", counter);
    }    
    printf("%i\n", counter);
}