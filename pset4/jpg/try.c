/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from CF image
 */
 
#include <stdio.h>
#include <cs50.h>
#include <stdint.h>
 
#define BLOCKSIZE 512 
#define BYTE 8


int main(void)
{
    // define file pointer to the input file
    FILE *inptr = fopen("card.raw", "r");

    
    // standart check for no errors
    if(!inptr)
        printf("Error opening file\n");

    
    // define buffer with size of 512 bytes to store date from fread 
    uint8_t buffer[BLOCKSIZE];
    
    // JPG file counter to name finded and newFileName files
    int counter = 0;
    
    // define file pointer to the output file
    FILE *outptr = NULL;

    
    // read from inptr to buffer with step of 512 byte, one step at a time, while there is blocks of 512 in file
    while (fread(buffer, BLOCKSIZE, 1, inptr) == 1)
    {
      
        // if block contains puttern bytes
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] >= 0xe0 && buffer[3] <= 0xef))
        {
            // if outptr not NULL, close it. this close already existing file when find beginin of a new jpg
            if (outptr !=NULL)
                fclose(outptr);
            
            // char array to store the resultant string of new file
            char title[BYTE];

            // make a new file with a name, that increments by counter
            sprintf(title, "%03d.jpg", counter);
            
            // open file for writing with name stored in char array
            outptr = fopen(title, "w");
            
            // incriment file counter for naming
            counter++;
        }
        
        // write one block of size 512 bytes from buffer to output if outfile not NULL
        if (outptr != NULL)
            fwrite(buffer, BLOCKSIZE, 1, outptr);
    }
    
    // close the file with last JPG when wile loop ends. if outfile not NULL
    if (outptr != NULL)
        fclose(outptr);

    // close input file
    fclose(inptr);

    
    return 0;
}
