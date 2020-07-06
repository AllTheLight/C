#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
   float d_owed;
   //Get input in dollars & re-prompting if necessary
    do    
    {   
        d_owed = get_float("How much change do you need?\n");
    }
    while (d_owed < 0);
    
    //Convert input to cents (float to int)
    int c_owed, n_coins, x, t_coins;
    c_owed = round(d_owed *100);
   
    t_coins=0;
    //How many 25c coins to use
    for (n_coins = 1; c_owed>=25; t_coins++)
    {   
        c_owed = c_owed - 25;
    }

    //How many 10c coins to use
    for (n_coins = 1; c_owed >= 10; t_coins++)
    {   
        c_owed = c_owed - 10;
    }

    //How many 5c coins to use
    for (n_coins = 1; c_owed>=5; t_coins++)
    {   
        c_owed = c_owed - 5;
    }

    //How many 1c coins to use
    for (n_coins = 1; c_owed>=1; t_coins++)
    {   
        c_owed = c_owed - 1;
    }
    printf("%i\n", t_coins);
}


