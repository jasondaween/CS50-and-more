#include <cs50.h>
#include <stdio.h>

const int N = 3;

float average(int length, int array[]);

int main(void)
{
    // Get scores
    int scores[N];
    for (int i = 0; i < N; i++)
    {
        do
        {
            scores[i] = get_float("Score %i: ", (i + 1));
            if (scores[i] < 0 || scores[i] > 100)
            {
                printf("Please input a number 0-100\n");
            }
        }
        while (scores[i] < 0 || scores[i] > 100);
    }
    // Print average
    printf("Average: %f\n", average(N, scores));
}

float average(int length, int array[])
{
    // Calculate average
    float sum = 0;
    for (int i = 0; i < length; i++)
    {
        sum += array[i];
    }
    return sum / (float) length;
}
