#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const char *choice(char c);
char GetAIChoice(void);
const char *FindResults(char UserChoice, char ai);

int main (void) {
    srand(time(NULL));
    
    printf("*************************\n");
    printf("Lets play rock paper scissors!\n");
    printf("Type r for rock, p for paper, and s for scissor\n");
    printf("*************************\n");
    printf("\n");

    // Get User Choice
    printf("*************************\n");
    char UserChoice;
    do {
        UserChoice = get_char("Enter r, p, or s: ");
        if (isupper(UserChoice) != 0) {
            UserChoice = tolower(UserChoice);
        }
    }
    while (UserChoice != 'r' && UserChoice != 'p' && UserChoice != 's');

    // Print User Choice
    printf("You picked %s.\n", choice(UserChoice));

    // Get AI Choice
    char ai = GetAIChoice();

    // Print AI Choice
    printf("AI picked %s.\n", choice(ai));

    // Print Winner
    const char *results = FindResults(UserChoice, ai);
    printf("%s\n", FindResults(UserChoice, ai));
    printf("*************************\n");
    return 0;
}

const char *choice(char c) {
    if (c == 'r') {
        return "rock";
    }
    else if (c == 'p') {
        return "paper";
    }
    else {
        return "scissor";
    }
    return NULL;
}

char GetAIChoice(void) {
    int aiChoice = rand() % 3;

    if (aiChoice == 0) {
        return 'r';
    }
    else if (aiChoice == 1) {
        return 'p';
    }
    else {
        return 's';
    }
    return 0;
}

const char *FindResults(char UserChoice, char ai) {
    if (UserChoice == 'r') {
        if (ai == 'r') {
            return "Tie!";
        }
        else if (ai == 'p') {
            return "You Lose!";
        }
        else {
            return "You Win!";
        }
    }
    else if (UserChoice == 'p') {
        if (ai == 'p') {
            return "Tie!";
        }
        else if (ai == 's') {
            return "You Lose!";
        }
        else {
            return "You Win!";
        }
    }
    else {
        if (ai == 's') {
            return "Tie!";
        }
        else if (ai == 'r') {
            return "You Lose!";
        }
        else {
            return "You Win!";
        }
    }
    return NULL;
}
