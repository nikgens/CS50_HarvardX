#include <cs50.h>
#include <stdio.h>

int main(void)
{
    printf("minutes: ");
    int time = GetInt();
    int bottles = 1.5*128/16*time;
    printf("bottles: %i\n", bottles);
}