#include <stdio.h>
#include <cs50.h>
#include <string.h>

bool CheckName(string s);
string CapitalizeLowCase(string s);
void FindFirstLetter (string s);

int main (void)
{
    string name = GetString();
    
    if (CheckName(name))
        FindFirstLetter(CapitalizeLowCase(name));
    else
        printf("wrong name\n");

    return(0);
}


// Check that name contains only letters a-z, A-Z and space
bool CheckName(string s)
{
    bool check = false;
    
    for (int i = 0, l = strlen(s); i < l; i++)
    {
        if ((s[i] >= 'a' && s[i] <='z') || (s[i] >= 'A' && s[i] <='Z') || s[i] == 32)
            check = true;
        else 
        {
            check = false;
            break;
        }
    }
    return(check);
}

// make all letters upper case
string CapitalizeLowCase(string s)
{
    for (int i = 0, l = strlen(s); i < l; i++)
    {
        if (s[i] >= 'a' && s[i] <='z')
            s[i] = s[i] - ('a' - 'A');
    }

    return(s);
}

// find first letter of each word in string and print
void FindFirstLetter (string s)
{
    int counter = 1;
    char initials[10];
    initials[0] = s[0];
    
    for (int i = 0, l = strlen(s); i < l; i++)
    {
        if (s[i] == 32)
        {
            initials[counter] = s[(i+1)];
            counter++;
        }
    }
    
    printf("%s\n", initials);
}    