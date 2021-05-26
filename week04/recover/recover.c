// Recovers jpgs from file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
 
int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // open memory card
    FILE *f = fopen(argv[1], "r");

    // jpg counter
    int jpgs_found = -1;

    // allocate space for buffer and open jpg
    uint8_t buffer[512];
    FILE *img;


    // repeat until end of card:
    // read 512 bytes into buffer
    while (fread(&buffer, 512, 1, f))
    {
        // if start is jpg header
        if (
            buffer[0] == 0xff && 
            buffer[1] == 0xd8 && 
            buffer[2] == 0xff && 
            (buffer[3] & 0xf0) == 0xe0
        ) {
            printf("test");
            // check for first found jpg
            if (jpgs_found == -1)
            {
                // if first, add counter
                ++jpgs_found;
                
            }
            else 
            {
                // close recently opened file
                ++jpgs_found;
                fclose(img);
            }

            // allocate space for filename
            char filename[8];

            // create filename
            sprintf(filename, "%03i.jpg", jpgs_found );

            // open file
            img = fopen(filename, "w");

            // write to open file
            fwrite(&buffer, 512, 1, img);
        }
        else
        {
            if (jpgs_found > -1)
            {
                fwrite(&buffer, 512, 1, img);
            }
        }
    }

    // close remaining files
    fclose(img);
    fclose(f);
}