
#include <cs50.h>
#include <stdio.h>



//checksum function declaration- which will take the card number as an argument:
bool checksum_odd(long card);
bool checksum_even(long card);

int main(void)
{

    long card;
    do //get card number, where it must be more than 0
    {
        card = get_long("Please enter card number:");
    }
    while (card < 0);

    // amex check
    //checking if card is 15 in length and starts with 34 or 37
    if((card/100000000000000 >0 && card /1000000000000000 <1) && (card/10000000000000 == 34 || card/10000000000000 == 37))
    {
        //if so, put it through the checksum function and print amex if true
        bool check = checksum_odd(card);
        if (check == true)
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }

    // Visa Check 16  - checking if card is 16 digits and starts with 4
    else if((card/1000000000000000 >0 && card /10000000000000000 <1) && (card/1000000000000000 == 4 ))
    {
       // putting through checksum
         bool check = checksum_even(card);
         if (check == true)
         {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }


        // Visa Check 13 - checking if card is 13 digits and starts with 4
    else if((card/1000000000000 >0 && card /10000000000000 <1) && (card/1000000000000 == 4 ))
    {
        //putting through checksum
        bool check = checksum_odd(card);
        if (check == true)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }

    // mastercard check - must be 16 digit and start with 51, 52, 53 or 54
    else if((card/1000000000000000 >0 && card /10000000000000000 <1) && (card/100000000000000 == 51 || card/100000000000000 == 52 || card/100000000000000 == 53 || card/100000000000000 == 54 || card/100000000000000 == 55 ))
    {
    //putting through checksum
        bool check = checksum_even(card);
         if (check == true)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else{
        printf("INVALID\n");
    }


} //int main bracket



//checksum function for odd numbers

bool checksum_odd(long card)
{
    long x = card;
    bool test = false;

    //working out how long the card is, keep dividing by 10 until it equals 0, while adding 1 to x each round
    long length = 0;
    while(x!= 0)
    {
        x /=10;
        length +=1;
    }

    int z = length;
    int digitarray_length;
    int digitarray_length_forlooping;
    int addto_array;
    int luhns_check;
    int leftover = 0;
    int leftover_sum = 0;


    // if length of the card is an odd number
    if(!(z % 2 == 0))
    {
        // working out how long the array should be of every other number
        digitarray_length = ((z-1)/2);
        digitarray_length_forlooping = digitarray_length;
        int size = digitarray_length;
        int everyothernumber_array[size];


        //while length is greater than 0, modulo 10 the card - and add that value to leftover sum
        while(z>0)
        {
            leftover  = card % 10;
            leftover_sum  += leftover;
            card = card / 10;
            z-=1;
        // then catch the next number in an array of the every other numbers and repeat until we've gone through all the numbers
            if(z>0)
            {
                addto_array = card % 10;
                // its this line that doesnt work which must mean i dont know how to set arrays
                everyothernumber_array[size-1] = addto_array;
                card = card / 10;
                size -=1;
            }
            else {
                    z = 0;
                }
        }

        int product_digits = 0;
        // work out the sum of the digits in the array - this requires iterating over each array element, so we have a loop in a loop and we're adding the product digits together
        for(x=0; x < digitarray_length_forlooping; x++)
        {
            everyothernumber_array[x] *=2;
            while (everyothernumber_array[x] != 0)
            {
                product_digits += everyothernumber_array[x] %10;
                everyothernumber_array[x] /= 10;

            }
        }

        // here i'm doing luhns check, if it's 0 we know its a valid card number
        luhns_check = product_digits + leftover_sum;
        if(luhns_check % 10 == 0)
        {
            test = true;

        }
        else
        {
            test = false;
        }
    }
    return test;


}
    //checksumodd end

// here's the function for an even number  -sames steps, but changes made to accurately get every other number etc, i should move this into one big fucntion really
bool checksum_even(long card)
{
    long x = card;
    bool test = false;
    long length = 0;
    while(x!= 0)
    {
        x /=10;
        length +=1;
    }

    int z = length;
    int digitarray_length;
    int digitarray_length_forlooping;
    int addto_array;
    int luhns_check;
    int leftover = 0;
    int leftover_sum = 0;



    if(z % 2 == 0)
    {
        digitarray_length = (z/2);
        digitarray_length_forlooping = digitarray_length;
        int size = digitarray_length;
        int everyothernumber_array[size];


        while(z>0)
        {
            leftover  = card % 10;
            leftover_sum  += leftover;
            card = card / 10;
            z-=1;

            if(z>0)
            {
                addto_array = card % 10;
                // its this line that doesnt work which must mean i dont know how to set arrays
                everyothernumber_array[size-1] = addto_array;
                card = card / 10;
                size -=1;
            }
            else {
                    z = 0;
                }
        }

        int product_digits = 0;
// new section adding the products digits
        for(x=0; x < digitarray_length_forlooping; x++)
        {
            everyothernumber_array[x] *=2;
            while (everyothernumber_array[x] != 0)
            {
                product_digits += everyothernumber_array[x] %10;
                everyothernumber_array[x] /= 10;

            }
        }
        luhns_check = product_digits + leftover_sum;
        if(luhns_check % 10 == 0)
        {
            test = true;

        }
        else
        {
            test = false;
        }
    }
    return test;


}





