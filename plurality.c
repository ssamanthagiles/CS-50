#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of 9candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
// typedef is used to create a type of our own
{
    string name;
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
// argc
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    // going through all the command line arguments
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        // initalizing allt the votes to 0
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{

    // Iterate over each candidate
    for (int i = 0; i < candidate_count; i++)
    {

        // Access the candidate using candidates[i]
        // Check if candidate's name matches given name
        // If yes, increment candidate's votes and return true
        if (strcmp(candidates[i].name, name) == 0)
        {
            // The strings are identical
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // initalize a variable max_votes to 0
    int max_votes = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > max_votes)
        {
            max_votes = candidates[i].votes;
        }
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == max_votes)
        {
            printf("%s\n", candidates[i].name);
        }
    }
}