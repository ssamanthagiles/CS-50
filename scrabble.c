#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

//I'm assigning points to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // With this step i'm basically gathering user input to give me two words that player one states and player two states
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Compute the score of each word
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    //I'm using this step to help me determine the winner, so if score 1 is greater than score 2 it'll print that player one wins
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    //when player 1's score = player 2's score, there's a tie
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    // I'm creating a new int variable score to help me keep track of the score
    int score = 0;

    // Using a for loop to help me compute the score for each character
    for (int i = 0, len = strlen(word); i < len; i++)
    {
        if (isupper(word[i]))
        {
            score += POINTS[word[i] - 'A'];
        }
        else if (islower(word[i]))
        {
            score += POINTS[word[i] - 'a'];
        }
    }

    return score;
}