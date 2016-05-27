/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3. 
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * It uses linear search.
 * Returns true if value is in array of n values, else false.
 * Take care to return false right away if n isn’t even positive.
 */
bool search(int value, int values[], int n)
{

    int middlePointIndex;
    int startPointIndex = 0;
    int endPointIndex = n-1;
    
    
    while (startPointIndex <= endPointIndex)
    {
        middlePointIndex = (endPointIndex + startPointIndex)/2;
        
        if (value == values[middlePointIndex])
        {
            return true;
            break;
        } 
        
        else if (value < values[middlePointIndex])
        {
            endPointIndex = middlePointIndex - 1;
        }
        
        else 
        {
            startPointIndex = middlePointIndex + 1;
        }
    }
    
    if (startPointIndex > endPointIndex)
        return false;
        
    return false;
}

/**
 * Sorts array of n values.
 * Bouble sort
 */
void sort(int values[], int n)
{
    int swapCounter = 1;
    
    while (swapCounter != 0)
    {
        swapCounter = 0;
        for (int i = 0; i < n-1; i++)  
        {
            if (values[i] > values[i+1])
            {
                int transit;
                transit = values[i+1];
                values[i+1] = values[i];
                values[i] = transit;
                swapCounter++;
            }
        }    
    }
    
    return;
}