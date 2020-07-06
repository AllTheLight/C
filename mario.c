#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //Prompting/ reprompting the user to input a number between 1 and 8
    int h, r, x, d;
    do   
{   
    h  = get_int("Choose a number from 1 to 8\n");
  
}   while (h < 1 || h > 8);
    
    //For the overall loop of the number of rows
    for (r = 0; r < h; r++)
    //For getting the correct number of spaces, according to the number of rows
{
    for (d = 0; d < h-r-1; d++)
{   printf(" ");
}
    //For getting the number of #, according to the number of spaces
    for (x = 0; x <= r ; x++)
{   
    printf("#");
}
    printf("\n");
}

}
