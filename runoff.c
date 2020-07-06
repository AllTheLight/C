#include <cs50.h>
#include <stdio.h>
#include <string.h>

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
}
candidate;

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
int n_cand_elim(void);

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
            int rank = j;
            int voter = i;

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
            else
            {
                vote(i, j, name);
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


/// my code
// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    for (int i = 0; i < candidate_count; i++) //this is done for each voter in the main function's loop
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            //if matches a name, store index of that candidate as as j preference for candidate i
            preferences[voter][rank] = i;
            return true;
        }
    }

    return false; //is this going to return false even if true is returned?
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    //to go through each voter
    for (int i = 0; i < voter_count; i++)
    {
        int j = 0;

        //int x = preferences[i][j]; //if x doesn't work we can take it out
        //to go through each preference - until one is not eliminated

        while (candidates[preferences[i][j]].eliminated == true)
        {
            j++;
        }

        candidates[preferences[i][j]].votes ++;
    }
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        //this has to be a float, because otherwise it makes uneven voter counts whole integers - eg. 2.5 to 2,
        //and then every candidate could be over that
        if ((float)candidates[i].votes > (float)voter_count / 2.0)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false; //exits the whole function when true is printed, won't print both
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min = voter_count;

    //to determine the minimum number of votes that any candidate has
    for (int i = 0; i < candidate_count; i++)
    {

        if (candidates[i].votes < min && candidates[i].eliminated == false)
        {
            min = candidates[i].votes;
        }
    }
    return min; // returns the minimum to the other functions,
    //so it is not confined to this function, but can be used for others ie. eliminate and tie
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int tie_counter = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            tie_counter++;
        }

    }

    if (tie_counter == candidate_count - n_cand_elim())
    {
        return true;
    }

    else
    {
        return false;

    }
}

// Eliminate the candidate (or candidiates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }

    return;
}
int n_cand_elim(void)
{
    int count = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == true)
        {
            count ++;
        }
    }

    return count;
}
