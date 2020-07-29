
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Error: Please input a 26 letter key, without spaces.\n");
        return 1;
    }

    int n = strlen(argv[1]);

    //handling invalid key length
    if (n != 26)
    {
        printf("Please input a 26 letter key.\n");
        return 1;
    }

    //to check if there are only letters, and then to check if there are any duplicates
    for (int i = 0; i < n; i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Error: Please only input letters.\n");
            return 1;
        }

        //nested for loop to check if there are duplicates - this works because once you've checked argv[0] has no duplicates,
        //you don't need to go back and check if argv[5] is the same as argv[0], as it cannot be (argv[0] has no duplicates).
        for (int j = i + 1; j < n; j++)
        {
            if (argv[1][i] == argv[1][j])
            {
                printf("Error: Please do not duplicate letters.\n");
                return 1;
            }
        }

    }

    //prompt user for plaintext
    string plaintext = get_string("plaintext: ");

    //length of plaintext
    int ptxt_len = strlen(plaintext);

    int ciphertext[ptxt_len];

    printf("ciphertext: ");

    //for upper case plaintext, convert characters into ciphertext and print as upper case
    for (int i = 0; i < ptxt_len; i++)
    {
        if (isupper(plaintext[i]))
        {
            ciphertext[i] = argv[1][plaintext[i] - 65];
            printf("%c", toupper(ciphertext[i]));
        }

        //for lower case plaintext, convert characters into ciphertext and print as lower case
        else if (islower(plaintext[i]))
        {
            ciphertext[i] = argv[1][plaintext[i] - 97];
            printf("%c", tolower(ciphertext[i]));
        }

        //for non letter characters, print as they are
        else if (!isalpha(plaintext[i]))
        {
            ciphertext[i] = plaintext[i];
            printf("%c", ciphertext[i]);
        }

    }

    printf("\n");

    return 0;
}