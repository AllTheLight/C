from cs50 import get_string

cn_str = get_string("Card Number: ")
n_digits = len(cn_str)

orig_c_number = []
mult_numbers = []
cn_int = int(cn_str)
calc = 0

#copy into list, index from last number backwards
for i in range(n_digits):

    orig_c_number.append(round(cn_int % 10))
    cn_int = cn_int / 10

#to multiply every second value by 2, starting at second last value
#and store all new values in 2nd list 'mult_numbers'
for i in range(1, n_digits, 2):

    calc += orig_c_number[i]*2 % 10 + orig_c_number[i]*2 /10

#add all the other numbers
for i in range(0, n_digits, 2):

    calc += orig_c_number[i]%10 + orig_c_number[i]/10

print(f"calc: {calc}")
if calc % 10 != 0:
    print("INVALID")
    exit()

#which type of card
if n_digits==13 or n_digits==16 and orig_c_number[n_digits - 1]==4:

        print("VISA")

elif n_digits==16 and orig_c_number[15]==5 and 1 <= orig_c_number <= 5:

        print("MASTERCARD")

elif n_digits==15 and orig_c_number[14]==3 and orig_c_number[13]==4 or orig_c_number[13]==7:

        print("AMEX")

else:
        print("INVALID")


