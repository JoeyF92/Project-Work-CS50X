#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


int main(void)
{
    //get text from user
    string text = get_string("Text:");

    //decalaring variables that i'll use for counting letters words and sentences
    int letter_count = 0;
    int word_count = 0;
    int sentence_count = 0;

    //work out the length of the text using strlen()
    int text_length = strlen(text);


    for (int x=0; x<=text_length; x++)
    {
        //with isalpha or ispunct - if it gives a none zero value its an alphabet or punctuation
        int is_alpha = isalpha(text[x]);
        int is_punct = ispunct(text[x]);

        //testing to see if letter is alphabetical
        if (is_alpha != 0)
        {
            letter_count +=1;
        }

        //testing to see if it's a space - ie no alphabet or punctuation
        if (is_alpha == 0 && is_punct == 0)
        {
            word_count +=1;
        }

        //testing to see if its the end of a sentence with . ? or !
        if (text[x] == '.' || text[x] == '!' || text[x] == '?')
        {
            sentence_count +=1;
        }
    }

    //calculating L - the average number of letters per 100 words. Do number of letters/ number of characters x 100
    float L = (float) letter_count / (float) word_count * 100;
    //calculating S - the average number of letters per 100 words. Do number of letters/ number of characters x 100
    float S = (float) sentence_count / (float) word_count * 100;

    // calculating the coleman-lieu index
    float coleman = 0.0588 * L - 0.296 * S - 15.8;

    //rounding the coleman-lieu index - add the math library
    int index = round(coleman);


    //here we are printing what grade the text is:

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }

    if (index >= 1 && index < 16)
    {
        printf("Grade %i\n", index);
    }

    if (index >= 16)
    {
        printf("Grade 16+\n");
    }


}