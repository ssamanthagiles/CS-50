##Prompt user for text:
text = input("Text: ")
##Initalize counters for letters
letters = 0
##Initalize counters for words
words = 0
##Initalize counters for sentences
sentences = 0

##for each character in the text
for char in text:
    ##if character is an alphabetic character, increment the letter counter
    if char.isalpha():
        letters += 1

    ##If chaeracter is a space, increment the word counter
    if char == " ":
        words += 1
    ##If the character is a space, increment the word counter
    if char == "." or char == "!" or char == "?":
        sentences += 1

##Since words are typically separated by spaces, add 1 to the word counter to account for the last word
words += 1

##Calculate the average number of letters per 100 words.
average_letters_per_100_words = (letters / words) * 100

##Calculate the average number of sentences per 100 words.
average_number_of_sentences = (sentences / words) * 100


##Use the Coleman-Liau index formula to calculate the readability grade level.
index = (
    0.0588 * average_letters_per_100_words - 0.296 * average_number_of_sentences - 15.8
)

grade = round(index)

##Print the correct grade level
if grade < 1:
    print("Before Grade 1")
elif grade > 16:
    print("Grade 16+")
else:
    print(f"Grade {grade}")

## Started this problem set on 10/29 in office hours at Widener Library
## Received help from CA João Henrique Santos on printing the correct grade level (L 41), everything else I did by myself
