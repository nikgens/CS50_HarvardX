#include <cs50.h>
#include <stdio.h>

int main(void) 
{
    int height;
    do
    {
        printf("Height: ");
        height = GetInt();
    }
    while ( height < 0 || height > 23);

    for (int i = 0; i < height ; i++)
    {
        int count = i;
        while (count < height-1)
        {
            printf(" ");
            count++;
        }
        
        int countStairs = 0;
        while (countStairs < i+2)
        {
            printf("#");
            countStairs++;
        }


        printf("\n");
    }    

}