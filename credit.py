from cs50 import get_string
from math import floor

cn_str = get_string("Card Number: ")
n_digits = len(cn_str)

orig_cn = []
mult_numbers = []
cn_int = int(cn_str)
calc = 0

#copy into list (backwards)
for i in range(n_digits):

    orig_cn.append(cn_int % 10)
    cn_int = cn_int / 10

#to multiply every second value by 2, starting at second last value
#and store all new values in 2nd list 'mult_numbers'
for i in range(n_digits):

    x = i
    #if index is even
    if (x % 2 == 0):
        calc += orig_cn[i]
        print(f"{orig_cn[i]}")
    else:
        product = orig_cn[i] * 2
        #will this make product the modulus of product? probs not
        calc += product % 10 + floor(product / 10)
        #calc += orig_cn[i]*2 % 10 + orig_cn[i]*2 /10

print(f"calc: {calc}")
if calc % 10 != 0:
    print("INVALID")
    exit()

#which type of card
if n_digits==13 or n_digits==16 and orig_cn[n_digits - 1]==4:

        print("VISA")

elif n_digits==16 and orig_cn[15]==5 and 1 <= orig_cn <= 5:

        print("MASTERCARD")

elif n_digits==15 and orig_cn[14]==3 and orig_cn[13]==4 or orig_cn[13]==7:

        print("AMEX")

else:
        print("INVALID")


