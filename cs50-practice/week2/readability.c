#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int readability_index(int letters, int words, int sentences);

int main(void)
{
    // Get a text from the user
    string text = get_string("Text: ");
    // Count text length
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);
    // Print each
    printf("%i letters\n", letters);
    printf("%i words\n", words);
    printf("%i sentences\n", sentences);
    // Compute the Coleman-Liau index
    int index = readability_index(letters, words, sentences);
    // Print the grade level
    if (index < 1)
    {
        printf("Below Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

int count_letters(string text)
{
    int letter = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isalnum(text[i]))
        {
            letter++;
        }

    }
    return letter;
}
int count_words(string text)
{
    int word = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (text[i] == ' ')
        {
            word++;
        }
    }
    return word + 1;
}
int count_sentences(string text)
{
    int sentence = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            sentence++;
        }
    }
    return sentence;
}
int readability_index(int letters, int words, int sentences)
{
    float L = letters / words * 100.0;
    float S = sentences / words * 100.0;
    int index = (int) round(0.0588 * L - 0.296 * S - 15.8);
    return index;
}
