/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }
    
    // remember the factor to resize
    int factor = atoi(argv[1]);
    
    //ensure factor is positive from 1 to 100
    if (factor < 1 && factor > 100)
    {
        printf("'n' must be from 1 to 100\n");
        return 2;
    }
    
    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    
    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }

    // save origin width and height
    int biWidthOrigin = bi.biWidth;
    int biHeightOrigin = bi.biHeight;
    
    //multiply widtn and height in px for N-times
    bi.biWidth *= factor;
    bi.biHeight *= factor;
    
    // determine padding 
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int paddingOrigin = (4 - (biWidthOrigin * sizeof(RGBTRIPLE)) % 4) % 4;

    // new image size
    bi.biSizeImage = abs(bi.biHeight) * ((bi.biWidth * sizeof(RGBTRIPLE)) + padding);
    
    // new file size
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    

    // iterate over infile's scanlines
    for (int i = 0, Height = abs(biHeightOrigin); i < Height; i++)
    {
        // Read each scanline factor times
        for (int j = 0; j < factor; j++)
        { 
            // iterate over pixels in scanline
            for (int k = 0; k < biWidthOrigin; k++)
            {
                // temporary storage
                RGBTRIPLE triple;
            
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
                // write RGB triple to outfile. I added for loop for this statment to print N-times pixel in horisontal
                for (int l = 0; l < factor; l++)
                {
                   fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // Add a new padding
            for (int m = 0; m < padding; m++)
                fputc(0x00, outptr);
                
            // Return to the beginning of a scanline
            if (j < factor - 1)
                fseek(inptr, -biWidthOrigin * sizeof(RGBTRIPLE), SEEK_CUR);
        }
        // skip over padding in origin file, if any
        fseek(inptr, paddingOrigin, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);
    
    // that's all folks
    return 0;
}
