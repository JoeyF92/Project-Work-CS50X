#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

int main(int argc, string argv[])

{
    //check that the user has entered just one arguement in the command line
    if (argc != 2)
    {
        printf("please enter a single command-line argument\n");
        return 1;
    }

    // check the user has entered a 26 digit character as the arguement
    string cipher = argv[1];
    int length = strlen(cipher);
    if (length != 26)
    {
        printf("please enter a 26 character length arguement\n");
        return 1;
    }

    //check user has entered all alphanumeric characters + if so, we convert it all to a lower case array.
    char cipher_lower[25];

    //here i'm looping through the cipher array, and converting any uppercase digits to lowercase under new array cipher_lower[]
    //and also checking for duplicate characters in the key

    char is_multiple[25];

    for (int i = 0; i < 26; i++)
    {
        is_multiple[i] = cipher[i];
    }



    for (int i = 0; i < 26; i++)
    {
        cipher_lower[i] = tolower(cipher[i]);

        if (isalpha(cipher_lower[i]) == 0)
        {
            printf("please enter a only alphabetical characters are your argument - 26 please \n");
            return 1;
        }
        //this inner loop will check that that character hasnt been used before in the key
        for (int y = 0; y < i; y++)
        {

            if (cipher_lower[i] == tolower(is_multiple[y]))
            {

                printf("please don't use duplicate characters\n");
                return 1;

            }


        }

    }

    //now we have the cipher array set up, we can now ask the user for an input and work on making the converted  output

    //getting the plain text input from the user
    string plain_text = get_string("Plain text: ");

    //getting the length of the entered text so we can loop it
    //add +1 to length plain to make space for the null terminator
    int length_plain = strlen(plain_text) + 1;

    char plain_output[length_plain - 1];


    for (int i = 0; i <= length_plain; i++)
    {
        bool is_lower = true;
        //here i'm creating the output array - and updating it if the character is alphanumeric below
        plain_output[i] = plain_text[i];


        //if the character is not alphabetic go inside below loop
        if (isalpha(plain_text[i]) != 0)
        {
            //check if character is lower case - if not change is_lower so we know what needs converting to uppercase
            if (islower(plain_text[i]) == 0)
            {
                is_lower = false;
            }

            //ghere we're work out what letter we need to reference from cipher text
            int reference_num;

            if (plain_output[i] == 'a' || plain_output[i] == 'A')
            {
                reference_num = 0;
            }



            if (plain_output[i] == 'b' || plain_output[i] == 'B')
            {
                reference_num = 1;
            }



            if (plain_output[i] == 'c' || plain_output[i] == 'C')
            {
                reference_num = 2;
            }



            if (plain_output[i] == 'd' || plain_output[i] == 'D')
            {
                reference_num = 3;
            }



            if (plain_output[i] == 'e' || plain_output[i] == 'E')
            {
                reference_num = 4;
            }



            if (plain_output[i] == 'f' || plain_output[i] == 'F')
            {
                reference_num = 5;
            }



            if (plain_output[i] == 'g' || plain_output[i] == 'G')
            {
                reference_num = 6;
            }



            if (plain_output[i] == 'h' || plain_output[i] == 'H')
            {
                reference_num = 7;
            }



            if (plain_output[i] == 'i' || plain_output[i] == 'I')
            {
                reference_num = 8;
            }



            if (plain_output[i] == 'j' || plain_output[i] == 'J')
            {
                reference_num = 9;
            }



            if (plain_output[i] == 'k' || plain_output[i] == 'K')
            {
                reference_num = 10;
            }



            if (plain_output[i] == 'l' || plain_output[i] == 'L')
            {
                reference_num = 11;
            }



            if (plain_output[i] == 'm' || plain_output[i] == 'M')
            {
                reference_num = 12;
            }


            if (plain_output[i] == 'n' || plain_output[i] == 'N')
            {
                reference_num = 13;
            }



            if (plain_output[i] == 'o' || plain_output[i] == 'O')
            {
                reference_num = 14;
            }



            if (plain_output[i] == 'p' || plain_output[i] == 'P')
            {
                reference_num = 15;
            }



            if (plain_output[i] == 'q' || plain_output[i] == 'Q')
            {
                reference_num = 16;
            }



            if (plain_output[i] == 'r' || plain_output[i] == 'R')
            {
                reference_num = 17;
            }



            if (plain_output[i] == 's' || plain_output[i] == 'S')
            {
                reference_num = 18;
            }



            if (plain_output[i] == 't' || plain_output[i] == 'T')
            {
                reference_num = 19;
            }



            if (plain_output[i] == 'u' || plain_output[i] == 'U')
            {
                reference_num = 20;
            }



            if (plain_output[i] == 'v' || plain_output[i] == 'V')
            {
                reference_num = 21;
            }


            if (plain_output[i] == 'w' || plain_output[i] == 'W')
            {
                reference_num = 22;
            }


            if (plain_output[i] == 'x' || plain_output[i] == 'X')
            {
                reference_num = 23;
            }



            if (plain_output[i] == 'y' || plain_output[i] == 'Y')
            {
                reference_num = 24;
            }



            if (plain_output[i] == 'z' || plain_output[i] == 'Z')
            {
                reference_num = 25;
            }



            //updating the output array with any of the alphabetic text inputted
            plain_output[i] = cipher_lower[reference_num];

            //updating the array for any characters than should be uppercase
            if (is_lower == false)
            {
                plain_output[i] -= 32;
            }

        }

        //printf("Cipher Text: %c ", plain_output[i]);
    }
    //printf("Cipher Text: %s \n ", plain_output);

    printf("ciphertext: ");
    for (int i = 0; i < length_plain - 1; i++)
    {
        printf("%c", plain_output[i]);
    }
    printf("\n");
    return 0;


}