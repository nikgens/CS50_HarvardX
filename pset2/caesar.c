#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

char returnCircledLetter(char reverse);

int main(int argc, string argv[])
{
    //if there less or more then one argument
    if (argc != 2 )
    {
        printf ("usage : ./caesar + key \n");
        return 1;
    }
    
    //argument into integer
    int k = atoi(argv[1]);

    if (k > 26)
        k= k % 26;
    
    //if argument not a digit    
    if ( k == 0 )
    {
        printf ("usage : ./caesar + key \n");
        return 1;
    }   
    
    string plainText = GetString();
    
    for (int i = 0, n = strlen(plainText); i < n; i++)
    {
        if ((plainText[i] >= 'a' && plainText[i] <='z') || (plainText[i] >= 'A' && plainText[i] <='Z'))
        {
            if(isupper(plainText[i]))
            {
                plainText[i] = ((plainText[i] + k - 'A') % 26) + 'A';
                printf("%c", plainText[i]);
            }
        
            if(islower(plainText[i]))
            {
                plainText[i] = ((plainText[i] + k - 'a') % 26) + 'a';
                printf("%c", plainText[i]);
            }
        }
        else
            printf("%c", plainText[i]);
    }
    printf("\n");
    
    return 0;
}

