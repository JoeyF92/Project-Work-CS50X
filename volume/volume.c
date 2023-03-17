// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;
// use typedef to create custom datatype BYTE with uint8_t
typedef uint8_t BYTE;
typedef int16_t SAMPLE_AUDIO;

int main(int argc, char *argv[])
{
    // Check to see command-line arguments present
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor (check file can be opened etc)
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // check output file can be opened using w mode - w for writing
    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // compute the factor - converting the factor to a floating point number
    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file

    //create an array of bytes for the header
    BYTE header[44];
    // so i think i've read the header and stored it in a header[44] array
    //we dont' use &header - as an array is the address of the first entry of an array
    fread(header, sizeof(BYTE), 44, input);
    //i'm tryng to now write that header array into the new file
    fwrite(header, sizeof(BYTE), 44, output);

    //now we're reading the body of the wav file to our sampleaudio body variable
    SAMPLE_AUDIO body;
    while (fread(&body, sizeof(SAMPLE_AUDIO), 1, input) == 1)
    {
        //while we fread = 1, take the sample audio and times it by the factor
        body = body * factor;
        //then fwrite this to the new file
        fwrite(&body, sizeof(SAMPLE_AUDIO), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
