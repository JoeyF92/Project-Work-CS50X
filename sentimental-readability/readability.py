# TODO

from cs50 import get_string

# get user to input a string
text = get_string("Please enter some text:")


# count the number of words in the paragraph (by how many spaces present + 1)
word_count = text.count(' ') + 1

# count the number of sentences in the paragraph, by how many .s, !s or ?s there are:
sentence_count = text.count('?') + text.count('.') + text.count('!')

# count the number of letters present in the paragraph:
letter_count = 0
for i in text:
    if i.isalpha():
        letter_count += 1

# calculating L - the average number of letters per 100 words. Do number of letters/ number of characters x 100
L = (letter_count / word_count) * 100

# calculating S - the average number of the average number of sentences per 100 word. Do number of sentences/ number of words x 100
S = sentence_count / word_count * 100

# calculating the coleman-lieu index
coleman = round(0.0588 * L - 0.296 * S - 15.8)

# logic for what grade will be printed out:
if coleman < 1:
    print("Before Grade 1")

elif coleman > 16:
    print("Grade 16+")

else:
    print("Grade {}".format(coleman))
