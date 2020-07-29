import csv
from sys import argv, exit
from collections import OrderedDict

if len(argv) != 3:
    print("Please input one database and one sequence.")
    exit(1)

#database is a sequence of lists
database = csv.reader(open(f"{argv[1]}", newline = ''))

#STORE TANDEM NAMES
row1 = next(database)
row1.pop(0)

#STORE THE FULL DNA SEQUENCE TO BE ANALYSED
seq = open(f"{argv[2]}")
str_seq = seq.read()

#COUNT MAX NO. OF REPEATS IN DNA SEQUENCE
index = 0
tmp_index = 0
inner_index = 0
max_counters = OrderedDict() #this will store the max no. of repeats for each tandem

#outer loop - for each tandem
for tandem in row1:

    counter = 0

    print(tandem)
    #new space in dict for current tandem
    max_counters[f"tandem{index}"] = 0

    #middle loop - for each location of current tandem
    #BUG: this can't find some of the strings in str_seq, even though they are there
    while(str_seq.find(tandem, tmp_index + len(tandem)*counter) != -1):
        #old version: while(str_seq[(tmp_index + len(tandem)*counter):len(str_seq)].find(tandem) != -1):

        #store the starting index of this location
        tmp_index = str_seq.find(tandem, tmp_index + len(tandem)*counter)

        #reset counter to 0 for each location, after slicing the string to not repeat search locations
        counter = 0

        inner_index = tmp_index
        #inner loop - counts no. of repeats at this location
        #print(str_seq[inner_index:(inner_index + len(tandem))])
        while (str_seq[inner_index:(inner_index + len(tandem))] == tandem):
            counter += 1
            inner_index += len(tandem)

        #after each middle loop (for each location of the tandem), check if this location had the most repeats
        if max_counters[f"tandem{index}"] < counter:
            max_counters[f"tandem{index}"] = counter

    print(f"max tandem{index}:", max_counters[f"tandem{index}"])
    index += 1


#COMPARE THE MAX NO. OF REPEATS FOR EACH TANDEM TO THE DATABASE
for row in database:

    tandem_no = 0
    matched = 0

    #start at 1, to avoid including the names in the comparison
    for i in range(1, len(row)):
        #print("row[i]:", row[i])
        #print(tandem_no)
        #print("max_counter:", max_counters[f"tandem{tandem_no}"])

        if int(row[i]) == max_counters[f"tandem{tandem_no}"]:
            matched += 1
            print("matched:", matched)
            tandem_no += 1

        else:
            break

    if matched == (len(row) - 1):
        print(f"Match found: {row[0]}")
        exit()
print("No match")