#include <ctype.h>
#include <stdio.h>

double wallet = 0.0;
double bank = 100.0;
void Deposit();
void Withdraw();
void Paycheck();

int main(void)
{
    int choice;
    do {
        // print out a list of choices
        printf("\n");
        printf("*************************\n");
        printf("Welcome to Bank of Jason!\n");
        printf("1. View Bank Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Receive Paycheck\n");
        printf("5. Exit\n");
        printf("*************************\n");
        printf("\n");

        // ask user for their choice
        do {
            printf("Enter your choice: ");
            scanf("%i", &choice);
        } while (choice < 1 || choice > 5);
        printf("\n");

        // if user picks option 1
        if (choice == 1) {
            printf("*************************\n");
            printf("Viewing your bank account...\n");
            printf("Wallet: %.2lf\n", wallet);
            printf("Balance: %.2lf\n", bank);
            printf("*************************\n");
        }

        // if user picks option 2
        else if (choice == 2) {
            Deposit();
        }

        // if user picks option 3
        else if (choice == 3) {
            Withdraw();
        }

        // if user picks option 4
        else if (choice == 4) {
            Paycheck();
        }

        // if user picks option 5
        else {
            printf("Goodbye!\n");
        }

    } while (choice != 5);

    return 0;
}

void Deposit() {
    double n;

    do {
        printf("*************************\n");
        printf("Deposit Amount: ");
        scanf("%lf", &n);

        if (n > wallet || n < 0) {
            printf("Invalid amount! Your wallet has $%.2lf\n", wallet);
        }
    } while (n > wallet || n < 0);

    bank += n;
    wallet -= n;

    printf("Deposit successful!\n");
    printf("*************************\n");
}

void Withdraw() {
    double n;

    do {
        printf("*************************\n");
        printf("Withdraw Amount: ");
        scanf("%lf", &n);

        if (n > bank || n < 0) {
            printf("Invalid amount! Your bank balance is $%.2lf\n", bank);
        }
    } while (n > bank || n < 0);

    wallet += n;
    bank -= n;

    printf("Withdraw successful!\n");
    printf("*************************\n");
}

void Paycheck() {
    double n;

    do {
        printf("*************************\n");
        printf("Paycheck Amount: ");
        scanf("%lf", &n);

        if (n <= 0) {
            printf("Insufficient amount!\n");
        }
    } while (n <= 0);

    bank += n;

    printf("Paycheck received!\n");
    printf("*************************\n");
}
