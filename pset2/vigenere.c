#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

string convertStringToLower(string str);
int returnIndexOfAlphabetChar(string s);

string alphabet = "abcdefghijklmnopqrstuvwxyz";

int main(int argc, string argv[])
{
    //if there less or more then one argument
    if (argc != 2 )
    {
        printf ("usage : ./vigenere + key word \n");
        return 1;
    }
    
    //if key word contains anything other than letters   
    string keyPhrase = convertStringToLower(argv[1]);
    
    for (int i = 0, n = strlen(keyPhrase); i < n; i++)
    {
        if (keyPhrase[i] < 'a' || keyPhrase[i] > 'z')
        {
            printf ("usage : ./vigenere + key word \n");
            return 1;
        }
    }
    
    string plainText = GetString();
    


    for (int i = 0, j = 0, l = strlen(plainText), m = strlen(keyPhrase); i < l; i++)
    {
        if ((plainText[i] >= 'a' && plainText[i] <='z') || (plainText[i] >= 'A' && plainText[i] <='Z'))
        {
            if(isupper(plainText[i]))
            {
                if (j >= m)
                    j = 0;
            
                plainText[i] = ((plainText[i] + returnIndexOfAlphabetChar(&keyPhrase[j]) - 'A') % 26) + 'A';
                printf("%c", plainText[i]);
                j++;
            }
        
            if(islower(plainText[i]))
            {
                if (j >= m)
                    j = 0;
            
                plainText[i] = ((plainText[i] + returnIndexOfAlphabetChar(&keyPhrase[j]) - 'a') % 26) + 'a';
                printf("%c", plainText[i]);
                j++;
            }
        }
        else
            printf("%c", plainText[i]);
    }
    printf("\n");
}



// convert a mixed-case string to all lower case 
string convertStringToLower(string str)
{
    for(int i = 0; str[i]; i++)
        str[i] = tolower(str[i]);
    
    return(str);
}



int returnIndexOfAlphabetChar(string s)
{
//    string alphabet = "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0, n = strlen(s); i < n; i++)
    {
        for (int j = 0, m = strlen(alphabet); j < m; j++)
        {
            if (alphabet[j] == s[i])
                //printf("%d\n", j);
                return(j);  
        }
    }
    return 0;
}

