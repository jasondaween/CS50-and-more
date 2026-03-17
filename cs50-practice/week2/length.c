#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string name = get_string("Name: ");
    for (int i = 0, n = strlen(name); i < n; i++)
    {
        // Change name[i] to uppercase
        printf("%c", toupper(name[i]));
    }
    printf("\n");
}
