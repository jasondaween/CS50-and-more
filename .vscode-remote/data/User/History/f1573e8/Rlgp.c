#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    srand(time(NULL));

    char playAgain;
    int totalScore = 0, difficulty, maxNumber = 100, maxAttempts;

    // Ask user for difficulty
    printf("Select Difficulty: \n");
    printf("Difficulty 1: 10 Attempts\n");
    printf("Difficulty 2: 7 Attempts\n");
    printf("Diffculty 3: 5 Attempts");
    

    do {
        int guess, attempt = 0;
        int score;

        // Generate random number
        int number = rand() % maxNumber + 1;

        while (number != guess && attempt < maxAttempts) {
            // Ask user to guess
            while (1) {
                printf("Guess the number (0-%i): ", maxNumber);
                if (scanf("%d", &guess) != 1) {
                    printf("Invalid input! Please enter a number.\n");
                    while (getchar() != '\n');
                    continue;
                }
                if (guess < 0 || guess > maxNumber) {
                    printf("Guess a number between 0-%i\n", maxNumber);
                    continue;
                }

                break;
            }
            attempt++;

            // Check user's guess
            if (guess > number) {
                printf("Number is lower\n");
            }
            if (guess < number) {
                printf("Number is higher\n");
            }
            printf("You have %i attempts left\n", 5 - attempt);
        }

        if (guess == number) {
            printf("You got it! (%i)\n", number);
            printf("You took %i attempts.\n", attempt);
        }

        else {
            printf("You failed! The number was %i\n", number);
        }

        // Get score for this round
        score = ((maxAttempts - attempt + 1) * 2);
        printf("Your score for this round is %i\n", score);

        // Add to total score
        totalScore += score;
        printf("Total Score: %i\n", totalScore);

        // Ask to play again
        printf("Play again? (y/n): ");
        scanf(" %c", &playAgain);
    } while (playAgain == 'y' || playAgain == 'Y');

    printf("Final score: %i\n", totalScore);

    return 0;
}