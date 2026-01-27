#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

float first;
float second;
string operation;

float calculate(void);

int main (void)
{
    // ask user for first number
    printf("************************\n");
    first = get_float("First number: ");
    printf("************************\n");
    printf("\n");
    // ask user for operation
    printf("************************\n");
    do {
        operation = get_string("Operation: ");
        if (strcmp(operation, "+") != 0 && strcmp(operation, "-") != 0 && strcmp(operation, "*") != 0 && strcmp(operation, "/") != 0){
            printf("+ - * /\n");
        }
    }
    while (strcmp(operation, "+") != 0 && strcmp(operation, "-") != 0 && strcmp(operation, "*") != 0 && strcmp(operation, "/") != 0);
    printf("************************\n");
    printf("\n");
    // ask user for second number
    printf("************************\n");
    second = get_float("Second number: ");
    printf("************************\n");
    printf("\n");
    // calculate answer
    float answer = calculate();
    // print answer
    printf("************************\n");
    printf("%g %s %g = %g\n", first, operation, second, answer);
    printf("************************\n");
    return 0;
}

float calculate(void)
{
    if (strcmp(operation, "+") == 0) {
        return first + second;
    }
    if (strcmp(operation, "-") == 0) {
        return first - second;
    }
    if (strcmp(operation, "*") == 0) {
        return first * second;
    }
    if (strcmp(operation, "/") == 0) {
        return first / second;
    }
    return 0.0;
}
