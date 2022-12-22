#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef uint8_t BYTE;
#define BLOCK_SIZE 512 //FAT file system photo

int main(int argc, char *argv[])
{
    //Check on whether user has provided an image to recover
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    char *input_file = argv[1];
    //Opening the file
    FILE *input_pointer = fopen(input_file, "r");
    //Checking if the file is empty
    if (input_file == NULL)
    {
        printf("Unable to open: %s\n", input_file);
        return 1;
    }

    // Initialise variables
    BYTE buffer[BLOCK_SIZE];
    // File counter, initialise
    int count = 0;
    FILE *output_file = NULL;
    int jpg_image_found = 0; //False


    //Read through the whole block, repeat for all files
    while (fread(&buffer, BLOCK_SIZE, 1, input_pointer) == 1)
    {
        //if start of new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //Check if JPEG has been found
            if (jpg_image_found == 1)
            {
                // Close the file
                fclose(output_file);
            }
            else
            {
                jpg_image_found = 1;
            }
            char filename[8];
            sprintf(filename, "%03i.jpg", count);
            //writing on the file
            output_file = fopen(filename, "w");
            count++;
        }
        if (jpg_image_found == 1)
        {
            //copy over the blocks from buffer into new file
            fwrite(&buffer, BLOCK_SIZE, 1, output_file);
        }
    }
    if (output_file == NULL)
    {
        fclose(output_file);
    }
    if (input_pointer == NULL)
    {
        fclose(input_pointer);
    }
    return 0;
}