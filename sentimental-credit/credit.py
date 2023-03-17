# TODO

import re


def main():
    # get card number from user - do as a while loop, to re prompt if input is invalid
    card_number = (input("Enter a card number: "))

    # amex check - checking if card is 15 in length and starts with 34 or 37
    if re.search("[0-9]{15}", card_number) and (re.search("^34", card_number) or re.search("^37", card_number)):
        # if it is and if checksum then true, print amex
        if checksum(card_number):
            print("AMEX")
        else:
            print("INVALID")
            exit()
    # visa check 1- check if card is 16 digits and starts with 4
    elif re.search("[0-9]{16}", card_number) and re.search("^4", card_number):
        # if it is and if checksum then true, print Visa
        if checksum(card_number):
            print("VISA")
        else:
            print("INVALID")
            exit()

    # Visa Check 2 - checking if card is 13 digits and starts with 4
    elif re.search("[0-9]{13}", card_number) and re.search("^4", card_number):
        # if it is and if checksum then true, print Visa
        if checksum(card_number):
            print("VISA")
        else:
            print("INVALID")
            exit()
    # mastercard check - checking if 16 digit and start with 51, 52, 53 or 54
    elif re.search("[0-9]{16}", card_number) and (re.search("^51", card_number) or re.search("^52", card_number) or re.search("^53", card_number) or re.search("^54", card_number) or re.search("^55", card_number)):
        # if it is and if checksum then true, print Mastercard
        if checksum(card_number):
            print("MASTERCARD")
        else:
            print("INVALID")
            exit()

    else:
        print("INVALID")
        exit()


def checksum(number):

    # convert cardnumber into an array of the digits- map iterates over the string converting, adding a function of my choice (in this case int)
    # then list() converts the map object to a list
    card_list = list((map(int, number)))

    # step 1 of luhn's algorythm
    luhns_one = []
    num = len(number)

    # if the card length number is odd, do the following:
    if num % 2 != 0:
        # iterate over card_list backwards, every other number
        for i in range(num-1, 0, -2):

            # times i-2 by 2 as part of the algorithm
            num2 = card_list[i-1]
            num2 *= 2

            # if i-2 is just one digit, append that to luhns_one
            if (num2 / 10) < 1:
                luhns_one.append(num2)
            # if i-2 is two digits, append the digits seperately to the array, so we can add them all up
            else:
                luhns_one.append(1)
                luhns_one.append(num2 % 10)

        # now add up all the numbers in the luhns_one list by looping over it
        luhns_one_total = 0

        for i in luhns_one:
            luhns_one_total += i

        # part 2 of luhns algorithm -  add the sum of the numbers that we didn't multiple by 2 + add my luhns_one_value to that
        luhns_two_total = luhns_one_total
        for i in range(num, 0, -2):
            luhns_two_total += card_list[i-1]

        # finally, im checking if the total number ends in zero - if it does, we have a valid number and we return true
        if luhns_two_total % 10 == 0:
            return True
        else:
            return False

    # if the card number length is even, do the following:
    elif num % 2 == 0:
        # iterate over card_list backwards, every other number
        for i in range(num, 0, -2):

            # times i-2 by 2 as part of the algorithm
            num2 = card_list[i-2]
            num2 *= 2

            # if i-2 is just one digit, append that to luhns_one
            if (num2 / 10) < 1:
                luhns_one.append(num2)
            # if i-2 is two digits, append the digits seperately to the array, so we can add them all up
            else:
                luhns_one.append(1)
                luhns_one.append(num2 % 10)

        # now add up all the numbers in the luhns_one list by looping over it
        luhns_one_total = 0

        for i in luhns_one:
            luhns_one_total += i

        # part 2 of luhns algorithm -  add the sum of the numbers that we didn't multiple by 2 + add my luhns_one_value to that
        luhns_two_total = luhns_one_total
        for i in range(num, 0, -2):
            luhns_two_total += card_list[i-1]

        # finally, im checking if the total number ends in zero - if it does, we have a valid number and we return true
        if luhns_two_total % 10 == 0:
            return True
        else:
            return False


if __name__ == '__main__':
    main()

