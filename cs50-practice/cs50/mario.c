#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Get user input for height
    int height;
    do
    {
        height = get_int("Height: ");
    }
    // Keeps asking for height until it is between 1-8
    while (height < 1 || height > 8);
    // Print pyramid height
    for (int i = 0; i < height; i++)
    {
        // Print spaces
        for (int j = 0; j < (height - i - 1); j++)
        {
            printf(" ");
        }
        // Print bricks
        for (int k = 0; k < (i + 1); k++)
        {
            printf("#");
        }
        // Print two spaces
        printf("  ");
        // Print right hashes
        for (int m = 0; m < (i + 1); m++)
        {
            printf("#");
        }
        // Print new line.
        printf("\n");
    }
}
