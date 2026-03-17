#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool only_alphabets(string key);
bool different_letters(string key);

int main(int argc, string argv[])
{
    // Make sure program is run with one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // Make sure command-line argument is alphabet letters only
    if (!only_alphabets(argv[1]))
    {
        printf("Key must only contain alphabetic characters.\n");
        return 1;
    }
    // Make sure command-line argument is 26 different letters
    if (!different_letters(argv[1]) || strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 different characters.\n");
        return 1;
    }
    // Prompt user for text
    string plaintext = get_string("plaintext: ");
    // For each character in plain text
    for (int i = 0, len = strlen(plaintext); i < len; i++)
    {
        // Substitute capital letters
        if (isupper(plaintext[i]))
        {
            int index = plaintext[i] - 'A';
            plaintext[i] = toupper(argv[1][index]);
        }
        // Substitute lowercase letters
        else if (islower(plaintext[i]))
        {
            int index = plaintext[i] - 'a';
            plaintext[i] = tolower(argv[1][index]);
        }
    }
    printf("ciphertext: %s\n", plaintext);
}

bool only_alphabets(string key)
{
    for (int i = 0, len = strlen(key); i < len; i++)
    {
        if (!isalpha(key[i]))
        {
            return false;
        }
    }
    return true;
}
bool different_letters(string key)
{
    bool seen[26] = {false};
    for (int i = 0, len = strlen(key); i < len; i++)
    {
        char c = tolower(key[i]);
        int index = c - 'a';
        if (seen[index])
        {
            return false;
        }
    }
    return true;
}
