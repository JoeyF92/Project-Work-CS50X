#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    //Print the winner, by comparing scores

    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }

    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }

    else
    {
        printf("Tie!\n");
    }
}

//function for computing the score of the inputted word
int compute_score(string word)
{

    //working out length of users word, so we can loop over it
    int str_length = strlen(word);
    int score = 0;

    //looping over word, to work out score for each letter
    for (int i = 0; i <= str_length; i++)
    {
        //if it's not alphabetical we just move on
        if (isalpha(word[i]) != 0)
        {
            //here we compare the letter to the scrabble array score - and add that to our score variable
            char letter = tolower(word[i]);

            if (letter == 'a')
            {
                score += POINTS[0];
            }

            if (letter == 'b')
            {
                score += POINTS[1];
            }

            if (letter == 'c')
            {
                score += POINTS[2];
            }

            if (letter == 'd')
            {
                score += POINTS[3];
            }

            if (letter == 'e')
            {
                score += POINTS[4];
            }


            if (letter == 'f')
            {
                score += POINTS[5];
            }

            if (letter == 'g')
            {
                score += POINTS[6];
            }


            if (letter == 'h')
            {
                score += POINTS[7];
            }

            if (letter == 'i')
            {
                score += POINTS[8];
            }


            if (letter == 'j')
            {
                score += POINTS[9];
            }

            if (letter == 'k')
            {
                score += POINTS[10];
            }

            if (letter == 'l')
            {
                score += POINTS[11];
            }

            if (letter == 'm')
            {
                score += POINTS[12];
            }

            if (letter == 'n')
            {
                score += POINTS[13];
            }

            if (letter == 'o')
            {
                score += POINTS[14];
            }

            if (letter == 'p')
            {
                score += POINTS[15];
            }

            if (letter == 'q')
            {
                score += POINTS[16];
            }

            if (letter == 'r')
            {
                score += POINTS[17];
            }

            if (letter == 's')
            {
                score += POINTS[18];
            }

            if (letter == 't')
            {
                score += POINTS[19];
            }

            if (letter == 'u')
            {
                score += POINTS[20];
            }

            if (letter == 'v')
            {
                score += POINTS[21];
            }

            if (letter == 'w')
            {
                score += POINTS[22];
            }

            if (letter == 'x')
            {
                score += POINTS[23];
            }

            if (letter == 'y')
            {
                score += POINTS[24];
            }

            if (letter == 'z')
            {
                score += POINTS[25];
            }

        }
    }

    // returning score so we can compare the users inputs
    return score;



}
