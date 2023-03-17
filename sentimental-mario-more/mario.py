# TODO

# get an integer from the user

# put it in a loop, so if user enters none integer, we keep asking for the integer
while True:
    try:
        number = int(input("Enter a number between 1-8 inclusive: "))
        if number >= 1 and number <= 8:
            break
    except ValueError:
        print("That is not an int!")


# create two counter varaibles - one for the spaces and one for the hashes
hash_number = 1
space_number = number

# the first loop is for the height of the pyramid
for i in range(number):

    # the inside loops dictates the spacing and hashes- we're decreasing the spaces as we go down the pyramid
    for j in range(space_number-1, 0, -1):
        print(" ", end="")

    # and increasing the hashes as we go down the pyramid
    for k in range(hash_number):
        print("#", end="")

    print("  ", end="")

    for k in range(hash_number):
        print("#", end="")
    print()

    # decrease/increase the relevant counters - and repeat
    hash_number += 1
    space_number -= 1

