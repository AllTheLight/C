#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    if (argc != 2 || argv[1] < 0)
    {
        printf("Error: invalid key\n");
        return 1;
    }
    int n = strlen(argv[1]);

    for (int i = 0; i < n; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    //prompt user for plaintext
    string plaintext = get_string("plaintext: ");

    //length of plaintext
    int ptxt_len = strlen(plaintext);

    int ciphertext[ptxt_len];

    //converting key to integer from string
    int key = atoi(argv[1]) % 26;

    //creating ciphertext
    printf("ciphertext: ");
    for (int i = 0; i < ptxt_len; i++)

        //weed out non-letter characters
    {
        if (isalpha(plaintext[i]))

        {
            ciphertext[i] = plaintext[i] + key;
        }

        else
        {
            ciphertext[i] = plaintext[i];
        }

        //to stop it going over z for lower case letters
        if (islower(plaintext[i]) && ciphertext[i] > 122)
        {
            ciphertext[i] -= 26;
        }

        //to stop it going over Z for upper case letters
        else if (isupper(plaintext [i]) && ciphertext [i] > 90)
        {
            ciphertext[i] -= 26;
        }
        
        //to print the individual characters each time
        printf("%c", ciphertext[i]);
    }
    printf("\n");
    return 0;
}