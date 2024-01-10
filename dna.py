import csv
import sys


def main():
    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python script.py argument")
        sys.exit(1)

    # Read database file into a variable
    rows = []
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        fieldnames = reader.fieldnames
        for row in reader:
            rows.append(row)

    # Read DNA sequence file into a variable
    with open(sys.argv[2]) as file:
        dna_sequence = file.read()

    # Find longest match of each STR in DNA sequence
    ##just call it
    list_for_STR = []
    for STR in fieldnames[1:]:
        list_for_STR.append(longest_match(dna_sequence, STR))

    # Check database for matching profiles
    match_found = False
    for row in rows:
        name_longest_match = []
        for STR in fieldnames[1:]:
            name_longest_match.append(int(row[STR]))
        ##Compare both lists
        ##print(list_for_STR)
        ## print(name_longest_match)
        if list_for_STR == name_longest_match:
            match_found = True
            print(row["name"])

    ##If nothing is found, print "No match"
    if match_found == False:
        print("No match")

    ##Return
    return


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


##completed during office hours on 10/29 at widener library
# verbally communicated with ella galova on ideas in this problem set
