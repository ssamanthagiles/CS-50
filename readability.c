#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)

{
    // Prompt the user for some text
    string text = get_string("Text: ");

    // Count the number of letters, words, and sentences in the text
    int letters = count_letters(text);
    // printf("%i\n", letters);
    int words = count_words(text);
    //  printf("%i\n", words);
    int sentences = count_sentences(text);
    // printf("%i\n", sentences);

    // Compute the Coleman-Liau index
    float L = ((float) letters / words) * 100.0;
    float S = ((float) sentences / words) * 100.0;
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    // Print the grade level
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    if (index > 1)
    {
        printf("Grade %d\n", index);
    }
}

int count_letters(string text)
{
    // Return the number of letters in text
    // Initialize a counter to 0
    // For each character in the text:
    // If the character is a letter:
    //  Increment the counter
    int lettercounter = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            lettercounter++;
        }
    }
    return lettercounter;
}

int count_words(string text)
{
    // Return the number of words in text
    int wordcounter = 1;
    for (int ii = 0; ii < strlen(text); ii++)
    {
        if (text[ii] == ' ')
        {
            wordcounter++;
        }
    }
    return wordcounter;
}

int count_sentences(string text)
{
    // Return the number of sentences in text
    int sentencecounter = 0;
    for (int iii = 0; iii < strlen(text); iii++)
    {
        if (text[iii] == '.' || text[iii] == '!' || text[iii] == '?')
        {
            sentencecounter++;
        }
    }
    return sentencecounter;
}