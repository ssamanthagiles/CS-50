#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;
int main(int argc, char *argv[])
{
    // this function demonstrates accepting a single line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // the function essentially opens the memmory card
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        return 1;
    }

    // this is creating a buffer for a block of data!
    BYTE buffer[512];
    FILE *currentFile = NULL;
    int fileNumber = 0;

    // this function reads 512 bytes at a time !!!
    while (fread(buffer, 1, 512, card) == 512)
    {
        // If the first 4 bytes in the buffer form the start of a JPEG file, this function will close the current file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (fileNumber > 0)
            {
                fclose(currentFile);
            }
            char filename[8];
            // this makes a new JPEG file each time a new JPEG signature is found in the forensic image
            sprintf(filename, "%03i.jpg", fileNumber);
            fileNumber++;
            // this opens a new file with created new filename !!
            currentFile = fopen(filename, "w");

            fwrite(buffer, 1, 512, currentFile);
        }

        else if (fileNumber > 0)
        {
            fwrite(buffer, 1, 512, currentFile);
        }
    }
    // this finally closes the currently open JPEG file and the forensic image file
    fclose(currentFile);
    fclose(card);
    return 0;
}