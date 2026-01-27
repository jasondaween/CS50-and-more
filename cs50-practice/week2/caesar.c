#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string k);
char rotate(char letter, int key);

int main(int argc, string argv[])
{
    // Make sure program is run with one command line argument
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    // Make sure argv[1] is a number
    if (!only_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    // Convert argv[1] from a string to an int
    int key = atoi(argv[1]);
    // Prompt user for text
    string plaintext = get_string("Plaintext: ");
    // For each character in plaintext
    for (int i = 0, len = strlen(plaintext); i < len; i++)
    {
        // Rotate the character if it's a letter
        plaintext[i] = rotate(plaintext[i], key);
    }
    printf("Ciphertext: %s\n", plaintext);
}

bool only_digits(string k)
{
    for (int i = 0, len = strlen(k); i < len; i++)
    {
        if (!isdigit(k[i]))
        {
            return false;
        }
    }
    return true;
}

char rotate(char letter, int key)
{
    if (isupper(letter))
    {
        return ((letter - 'A' + key) % 26 + 'A');
    }
    if (islower(letter))
    {
        return ((letter - 'a' + key) % 26 + 'a');
    }
    else
    {
        return letter;
    }
}
