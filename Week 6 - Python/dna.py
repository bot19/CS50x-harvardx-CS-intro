import csv
import sys

# task: https://cs50.harvard.edu/x/2025/psets/6/dna/
# longest_match() provided, complete main()

# TODO: build this function
def main():

    # TODO: Check for command-line usage; "python dna.py databases/small.csv sequences/1.txt"
    if len(sys.argv) != 3:
        print("Missing command-line argument")
        sys.exit(1)

    # TODO: Read database file into a variable
    persons = []
    with open(sys.argv[1]) as fileDB:
        reader = csv.DictReader(fileDB)

        # set persons data to list of dictionaries
        for row in reader:
            persons.append(row)

        # set STRs into a list
        STRs = reader.fieldnames
        # remove the name fieldname, leaving just STRs in list
        STRs.pop(0)

        # print(f"STRs: {STRs}\nPersons: {persons}")

    # TODO: Read DNA sequence file into a variable "dna"
    with open(sys.argv[2]) as fileDNA:
        dna = fileDNA.read()
        # print(f"DNA: {dna}")

    # TODO: Find longest match of each STR in DNA sequence
    # find the count of each STR and put it in a list of dictionaries
    dnaSTRs = []
    for str in STRs:
        # get count of STR in DNA
        count = longest_match(dna, str)
        # create a dictionary & add to DNA STR list
        dnaSTRs.append({"str_name": str, "count": count})

    # print(f"DNA STRs: {dnaSTRs}")

    # TODO: Check database for matching profiles
    for person in persons:
        # to keep track of how many STR counts matched
        match = 0

        # for each person, check all STRs in DNA STR with theirs
        for dnaSTR in dnaSTRs:
            str = dnaSTR["str_name"]  # "AGATC"
            count = dnaSTR["count"]  # 4

            # if STR matches person's STR, increment
            if count == int(person[str]):
                match += 1

            # print(f"dnaSTR: {str}, {count}, {person[str]}, {count == int(person[str])}, match: {match}")

        # all STRs count match this person's
        if match == len(dnaSTRs):
            print(person["name"])
            sys.exit(0)

    # no persons matched
    print("No match")

    return


# function provided by cs50 staff
def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
