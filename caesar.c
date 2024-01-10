#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LENGTH 100

// Make sure every character in argv[1] is a digit
bool only_digits(string s)
{
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
    }
    return true;
}

// Make sure program was run with just one command-line argument
int main(int argc, string argv[])
{
    if (argc != 2 || !only_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    int key = atoi(argv[1]);
    // Prompt user for plaintext
    string plaintext = get_string("plaintext: ");
    char ciphertext[LENGTH + 1] = {'\0'};

    int n = strlen(plaintext);
    // starting my for loop
    for (int i = 0; i < n; i++)
    {
        char c = plaintext[i];
        char ciphered_letter;
        if (isalpha(c))
        {
            // if character is uppercase
            if (isupper(c))
            {
                ciphered_letter = ((c - 'A' + key) % 26) + 'A';
                ciphertext[i] = ciphered_letter;
            }
            // if character is lowercase
            else if (islower(c))
            {
                ciphered_letter = ((c - 'a' + key) % 26) + 'a';
                ciphertext[i] = ciphered_letter;
            }
        }
        // handling non-letter characters
        else
        {
            ciphertext[i] = c;
        }
    }
    ciphertext[n] = '\0';
    printf("ciphertext: %s\n", ciphertext);
    return 0;
}
