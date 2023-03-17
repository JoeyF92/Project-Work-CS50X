#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //check argument count is 2
    if (argc != 2)
    {
        printf("Usage: ./recover.c card.raw\n");
        return 1;
    }

    //open raw file
    FILE *raw_file = fopen(argv[1], "r");

    //check file exists
    if (!raw_file)
    {
        printf("Can't open file");
        return 1;
    }

    //creatng block of 512 bytes for reading !!? issue with 511 over 512?
    BYTE buffer[511];

    //create a counter so we know how many jpegs read
    int counter = 0;

    //create a file pointer for new images
    FILE *recovered_jpg = NULL;

    //create space for filename to name new jpegs !! don't foget to free
    char *jpg_name = malloc(8 * sizeof(char));

    //start iterating over blocks of the raw file
    while (fread(buffer, sizeof(BYTE), 512, raw_file) == 512)
    {
        //if we fnd the first jpeg, open file and start writing to it
        if ((counter == 0) && (buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && ((buffer[3] & 0xf0) == 0xe0))
        {
            recovered_jpg = fopen("000.jpg", "w");
            fwrite(buffer, sizeof(BYTE), 512, recovered_jpg);
            counter++;
            continue;
        }

        //if counter is not 0 and it's not the start of a new jpeg, continue writing
        if ((counter > 0) && !(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0))
        {
            fwrite(buffer, sizeof(BYTE), 512, recovered_jpg);
        }

        //if it's the start of a new jpeg + we already have one open
        if ((counter > 0) && (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0))
        {
            fclose(recovered_jpg);
            sprintf(jpg_name, "%03i.jpg", counter);
            recovered_jpg = fopen(jpg_name, "w");
            fwrite(buffer, sizeof(BYTE), 512, recovered_jpg);
            counter++;
        }

    }
    free(jpg_name);
    fclose(recovered_jpg);
    fclose(raw_file);

}