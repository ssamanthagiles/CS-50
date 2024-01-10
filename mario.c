#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Get user input section
    int numofbricks;

    do
    {
        numofbricks = get_int("Height: ");
    }
    while (numofbricks <= 0);

    // Print pyramid section
    for (int i = 0; i < numofbricks; i++)
    // spaces_left
    {
        for (int hash = 0; hash < numofbricks; hash++)
        {
            if (hash < numofbricks - i - 1)
            {
                printf(" ");
            }
            // printing hashtags
            else
            {
                printf("#");
            }
        }
        // new line
        printf("\n");
    }
}
