#include <cs50.h>
#include <math.h>
#include <stdio.h>

int main(void)
{
    int cents;
    int change = 0;
    do
    {
        cents = get_int("Change owed: ");
    }
    while (cents < 0);

    while (cents > 0)
    {
        if (cents >= 25)
        {
            cents -= 25;
        }
        else if (cents >= 10)
        {
            cents -= 10;
        }
        else if (cents >= 5)
        {
            cents -= 5;
        }
        else
        {
            cents--;
        }
        change++;
    }
    printf("%i\n", change);
}
