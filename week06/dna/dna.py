import csv
import sys


def main():
    # Ensure correct usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # Read people and strs from database
    people = get_people_from_database(sys.argv[1])
    strs = get_strs_from_database(sys.argv[1])

    # Read sequence from file
    sequence = get_sequence_from_file(sys.argv[2])

    # Analyse sequence for consecutive occurences
    results = {}
    for str in strs:
        results[str] = count_consecutive_occurences_in_string(str, sequence)

    # Compare results with database
    match = search_for_dna_match(people, results, strs)

    # Print result of analysis
    print(match)


def get_people_from_database(file: str) -> list:
    """Gets list of people from .csv file

    Args:
        file (str): The path to the file used to retrieve the data from

    Returns:
        list: List of dicts for each person
    """
    people = []
    with open(file) as file:
        reader = csv.DictReader(file)
        for row in reader:
            people.append(row)
    return people


def get_strs_from_database(file: str) -> list:
    """Gets list of strs from .csv file

    Args:
        file (str): The path to the file used to retrieve the data from

    Returns:
        list: A List of all strs
    """
    with open(file) as file:
        reader = csv.DictReader(file)
        return reader.fieldnames[1:]


def get_sequence_from_file(file: str) -> str:
    """Gets dna-sequence from .txt file

    Args:
        file (str): The path to the file used to retrieve the sequence from

    Returns:
        str: A string representing a dna-sequence
    """
    with open(file) as file:
        return file.read()


def count_consecutive_occurences_in_string(needle: str, haystack: str) -> int:
    """Counts the maximum number of consecutive occurences of string in
    another string

    Args:
        needle (str): The string of which consecutive occurences are looked for
        haystack (str): The string to search occurences in

    Returns:
        int: The maximum number of consecutive occurences
    """
    # Current position of the cursor
    cursor = 0

    # Saved position of cursor when currently counting consecutive occurences
    saved_cursor_position = 0

    # Maximum number of consecutive occurences counted
    consecutive_occurences = 0

    # Size of the cursor
    cursor_size = len(needle)

    # Current count of consecutive occurences
    count = 0

    # Iterate over the haystack
    while cursor in range(0, len(haystack)):
        # Check if chars at the position of the cursor are equal to needle
        if haystack[cursor:cursor + cursor_size] == needle:
            # Increase count
            count += 1
            # Override consecutive occurences if count > prior highest count
            consecutive_occurences = max(count, consecutive_occurences)
            # Move cursor
            cursor += cursor_size
        else:
            # Reset count
            count = 0
            # Update saved cursor position
            saved_cursor_position = saved_cursor_position + 1
            # Move cursor back to saved position
            cursor = saved_cursor_position

    # Return consecutive occurences
    return consecutive_occurences


def search_for_dna_match(people, results, strs):
    """Searches for exact dna matches of a person

    Args:
        people (list): People to use for matching
        results (dict): Result data to use for matching
        strs (list): The strs to use while finding matches

    Returns:
        str: Either the matched persons name or "No match"
    """
    # Iterate over given people
    for person in people:
        found_match = True

        # Iterate over all strs
        for str in strs:
            # Check whether an str does not match
            if not int(person[str]) == results[str]:
                found_match = False

        # Return person name if match is found
        if found_match:
            return person["name"]

    # Return No Match if no match was found
    return "No Match"


main()
