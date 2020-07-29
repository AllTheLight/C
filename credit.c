#include <stdio.h>
#include <cs50.h>
#include <stdarg.h>

//introduction to ord_mag and add functions (see bottom)
int ord_mag(long x);
int main(void)
{
    //introducing sum, i, n_digits and c_number
int sum=0;
int i;
int n_digits;
long long c_number;
//Prompt user for number  
    c_number = get_long_long("Number\n");
    n_digits = ord_mag(c_number);

//introducing the first array orig_numbers
int orig_numbers[n_digits];
//To store the long long value as an array called orig_numbers
for (i=0; i < n_digits; i++)
{
    orig_numbers[i] = c_number%10;
    c_number /= 10;
}
//to introduce mult_numbers
int mult_numbers[n_digits];
//to multiply every second value by 2 and store all new values in 2nd array 'mult_numbers'
for(i=1; i<n_digits; i+=2)
{
    mult_numbers[i] = orig_numbers[i]*2;
    sum+= (mult_numbers[i] %10) +  (mult_numbers[i] /10);
}
//to use the original numbers and add each second value (starting from LAST) to sum
for(i=0;i<n_digits; i+=2)
{
    mult_numbers[i]=orig_numbers[i];
    sum+= (mult_numbers[i]%10)+(mult_numbers[i] /10);
}
//for validating a visa
if((n_digits==13|| n_digits==16) && sum%10==0 && orig_numbers[n_digits-1]==4)
{
    printf("VISA\n");
}
//to validate a mastercard
else if (n_digits==16 && orig_numbers[15]==5 && sum%10==0 && (orig_numbers[14]==1 || orig_numbers[14]==2 ||orig_numbers[14]==3 || orig_numbers[14]==4 || orig_numbers[14] ==5))
{
    printf("MASTERCARD\n");
}
//to validate an american express
else if(n_digits==15 && sum%10==0 && orig_numbers[14]==3 && (orig_numbers[13]==4 || orig_numbers[13]==7))
{
    printf("AMEX\n");
}
//otherwise print invalid - all other numbers bar 13,15 & 16 digit ones should have been weeded out by the first process of the ord_mag function
else 
{
    printf("INVALID\n");
}
}

//New outside function to check the number of digits
int ord_mag(long x)
{
    int n_digits = 0;
    for (long i=x; i>=1; n_digits++)
{
    i=i/10;
}
return n_digits;
}
