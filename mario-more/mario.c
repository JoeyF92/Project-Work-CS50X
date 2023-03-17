#include <cs50.h>
#include <stdio.h>

int main(void)
{

    int number = get_int("Please select a height from levels 1 - 8: ");

    while (number < 1 || number > 8)
    {
        number = get_int("Please select a height from levels 1 - 8: ");
    }

    for (int i = 1; i <= number; i++)
    {

        for (int t = number; t > i; t--)
        {
            printf(" ");
        }

        for (int j = 0; j < i; j++)
        {
            printf("#");
        }

        printf(" ");
        printf(" ");

        for (int j = 0; j < i; j++)
        {
            printf("#");
        }

        printf("\n");

    }



}