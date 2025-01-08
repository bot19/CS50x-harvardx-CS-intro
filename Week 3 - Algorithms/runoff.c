#include <cs50.h>
#include <stdio.h>
#include <string.h>

/*
 - only concepts learnt are utilised
 - parts pre-written, only complete TODO parts
 - task: https://cs50.harvard.edu/x/2025/psets/3/runoff/
 */

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid (TODO)
bool vote(int voter, int rank, string name)
{
    // loop through cand. arr. to find name
    for (int i = 0; i < candidate_count; i++)
    {
        // str compare func. > Y = accum. vote + return true
        if (strcmp(candidates[i].name, name) == 0)
        {
            // optional (beyond scope of assignment)
            // check duplicate vote; same candidate, multiple ranks

            // add voter's preference: candidate's index at voter's rank
            preferences[voter][rank] = i;

            return true;
        }
    }

    // no early return = candidate not found
    return false;
}

// Tabulate votes for non-eliminated candidates (TODO)
// preferences[MAX_VOTERS][MAX_CANDIDATES]
void tabulate(void)
{
    // loop through each voter
    for (int i = 0; i < voter_count; i++)
    {
        // loop through each of their candidate preferences, 1st to last
        for (int j = 0; j < candidate_count; j++)
        {
            // is candidate still in the running?
            int candidate_i_at_rank = preferences[i][j];

            // cast vote for highest rank candidate not eliminated
            if (!candidates[candidate_i_at_rank].eliminated)
            {
                candidates[candidate_i_at_rank].votes += 1;

                // this voter's vote has been cast, proceed to next voter
                break;
            }
        }
    }

    return;
}

// Print the winner of the election, if there is one (TODO)
bool print_winner(void)
{
    // loop through candidates, check if anyone has >50% votes
    for (int i = 0; i < candidate_count; i++)
    {
        // print and return true to end runoff while loop
        if (candidates[i].votes > (voter_count / 2))
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }

    // no winner found, keep loop going.
    return false;
}

// Return the minimum number of votes any remaining candidate has (TODO)
int find_min(void)
{
    int min_votes = voter_count; // start at max vote count possible

    // loop through all candidates to see their vote
    for (int i = 0; i < candidate_count; i++)
    {
        // if a candidate's vote < min_votes, assign new min_votes
        // additionally, only care if they aren't already eliminated
        if (!candidates[i].eliminated && candidates[i].votes < min_votes)
        {
            min_votes = candidates[i].votes;
        }
    }

    return min_votes;
}

// Return true if the election is tied between all candidates, false otherwise (TODO)
bool is_tie(int min)
{
    // count remaining candidates & candidates with min votes
    int remaining_candidates = 0;
    int min_votes_candidates = 0;

    // if ALL non-eliminated candidates have the same min no. of votes = tied
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated)
        {
            remaining_candidates += 1;

            if (candidates[i].votes == min)
            {
                min_votes_candidates += 1;
            }
        }
    }

    if (remaining_candidates == min_votes_candidates)
    {
        return true;
    }

    return false;
}

// Eliminate the candidate (or candidates) in last place (TODO)
void eliminate(int min)
{
    // loop through candidates & set eliminated true if votes == min
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }

    return;
}
