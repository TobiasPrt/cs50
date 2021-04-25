#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; ++i)
    {
        // we get one candidate and rank at a time so
        // if the name matches one in the candidates array
        // update the ranks array at the given rank
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // loop through ranks[], ranks[] has the same length as the candidate count
    for (int i = 0; i < candidate_count; ++i)
    {
        // for each element in the ranks[] loop through it (all candidates) to find the ones
        // that are less preferred and add a count to them
        for (int j = 0; j < candidate_count; ++j)
        {
            // filter out all candidates from ranks[], that are already looped over
            // so only the pair with the less preferred gets a count
            if (i < j)
            {
                ++preferences[ranks[i]][ranks[j]];
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // candidates[i]: main candidat
    for (int i = 0; i < candidate_count; ++i)
    {
        // candidates[i]: other candidat
        for (int j = 0; j < candidate_count; ++j)
        {
            // We dont have to check for each main candidat if he/she is compared to itself,
            // because we check if there are more preferences for the main candidate compared to the
            // other candidat than the other way around. If the main candidat would be compared
            // to himself/herself both directions would equal 0 preferences, since we should assume
            // that no voter ranks the same candidate twice
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;

                // we need to keep track of the pair count, so we dont override anything
                ++pair_count;
            }
            // we dont have to care about the other way around since we loop
            // through each candidate anyway
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // loop through all pairs
    for (int j = 0; j < pair_count; ++j)
    {
        // we loop through all pairs starting at the back
        // Since we are starting from the back we can assume that
        // j pairs starting from the front are already sorted, because
        // we already moved the biggest one to the front within the given range
        // every round/lap
        for (int i = pair_count; i > j; --i)
        {
            // we can go -1 here because i will never fall to 0, since we define i needs
            // to be bigger than j and j starts at 0
            int victory_strength_current = preferences[pairs[i].winner][pairs[i].loser];
            int victory_strength_before = preferences[pairs[i-1].winner][pairs[i-1].loser];

            // we compare the victory strength of the pair before our current one to the
            // current one. If it is lower, we move the current one on to the left and the one
            // before moves at our current position
            if (victory_strength_current > victory_strength_before)
            {
                pair tmp_pair = pairs[i-1];
                pairs[i-1] = pairs[i];
                pairs[i] = tmp_pair;
            }
        }
    }
}

bool is_circle(int locker, int locked_candidate, int locked_pairs_count)
{
    // check if the current locked candidate points to the locker,
    // which would create a circle
    if (locked[locked_candidate][locker])
    {
        return true;
    }
    // loop through all already locked pairs
    // i: are all the candidates the currently to be locked candidate already points to
    for (int i = 0; i < locked_pairs_count; ++i)
    {
        // check if the currently to be locked/pointed candidate
        // already points to any other candidate in locked[]
        if (locked[locked_candidate][i])
        {
            // when the candidate does already point to someone, check
            // if this would create circle, by checking if this candidate which is
            // pointed to or any other canidates that candidate is pointing
            // towards are pointing to the locker
            if (is_circle(locker, i, locked_pairs_count))
            {
                // return true and break the function if locked candidate points to locker
                // and therefore creates a circle
                return true;
            }
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // keep track of all edges (pairs that are locked)
    int locked_pairs_count = 0;
    // loop through all pairs
    for (int i = 0; i < pair_count; ++i)
    {
        // divide pair into parts
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;
        // check for each pair if adding it as an edge would close a circle
        if (!is_circle(winner, loser, locked_pairs_count))
        {
            // if no circle is closed add the edge to the locked array
            locked[winner][loser] = true;
            // add 1 to the locked pairs count, since we've added one
            ++locked_pairs_count;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // loop through all candidates
    for (int i = 0; i < candidate_count; ++i)
    {
        // assume the current candidate is the winner
        bool is_winner = true;
        // question the current candidate as the winner by
        // going through all candidates and verifying that no other
        // candidate points at the current candidate
        for (int j = 0; j < candidate_count; ++j)
        {
            // if one other candidate points at the current candidate
            // overwrite the assumption of winning
            if (locked[j][i])
            {
                is_winner = false;
            }
        }

        // if we could not prove that the candidate is not the winner
        // he/she must be the winner and his/her name is printed
        if (is_winner)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}
