#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    //prompt user for text
    string text = get_string("Input a text:\n");
    int n;

    //to get length of string
    int string_len = strlen(text);

    //to count the number of spaces, which is the no. of words-1
    int sum_space=0;
    for(int i=0; i<string_len; i++)
    {
        if(text[i] == ' ')
        {
            sum_space++;
        }

    }
    int sum_words=sum_space+1;
    printf ("words, %i ,", sum_words);
    
    //to get the no. of letters
    int sum_letters =0;
    for(int i =0; i <string_len; i++)
    {
        if(isalpha (text[i]))
        {
            sum_letters++;
        }
    }
    //no. of letters per 100 words and print out letters section
    float ind_lett = ((float)sum_letters*(100.0/(float)sum_words));
    printf ("letters %i, index_lett %f\n",sum_letters, ind_lett);
    //to get the no. of sentences

    int sum_sent=0;
    for (int i=0; i<string_len; i++)
    {
        if(text[i] ==46 || text[i]==33 ||text[i]==63)
        {
            sum_sent++;
        }
    }
    //no. of sentences per 100 words and print out sentences section
    float ind_sent = ((float)sum_sent*(100.0/(float)sum_words));
    printf("sent %i, index_sent, %f\n", sum_sent, ind_sent);
    
    //final part to get the index number and print it
    float index = round(0.0588 * ind_lett - 0.296 * ind_sent - 15.8);

    //to include under grade 1 and above grade 16
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index>=16)
    {
        printf("Grade 16+\n");
    }
    else
    {
    printf("Grade %.0f\n", index);
    }
}
