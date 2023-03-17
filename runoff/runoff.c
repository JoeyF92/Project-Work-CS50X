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

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{

    for (int i = 0; i < candidate_count; i++)
    {
        //checking name matches a votable candidate. If it's !strcmp, it means its false - ie not 0, so they match
        if (!strcmp(name, candidates[i].name))
        {
            //they match, so we update [i(voter)][j(rank)] = rank number
            preferences[voter][rank] = i;
            return true;
        }

    }

    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{

    //looping over the voter table- and adding a vote to the candidate that is the first preference of the voter -that hasnt been eliminated
    for (int i = 0; i < voter_count; i++)
    {
        int j = 0;
        // if the candidate they voted for has been eliminated, i'll move on to their next favourite in the table - so j+1
        while (candidates[preferences[i][j]].eliminated == true)
        {
            j += 1;

        }

        //add the vote to the candidate.votes
        candidates[preferences[i][j]].votes += 1;

        //here i'm printing out who gets a vote, just to check it works
        //printf("candidate %s votes = %i \n", candidates[0].name, candidates[0].votes);
        //printf("candidate %s votes = %i \n", candidates[1].name, candidates[1].votes);
        //printf("candidate %s votes = %i \n", candidates[2].name, candidates[2].votes);
    }


    // TODO
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{

    //creating a variable for the number needed for more than 50% votes
    float winner_count = voter_count / 2;

    //loop over the candidates - if any have more than 50% votes we can print winner
    for (int i = 0; i < voter_count; i++)
    {
        if (candidates[i].votes > winner_count)
        {
            printf(" %s\n", candidates[i].name);
            return true;
        }
    }

    // if no winner
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min = voter_count;

    for (int i = 0; i < candidate_count; i++)
    {
        if ((min > candidates[i].votes) && (!candidates[i].eliminated))
        {
            min = candidates[i].votes;
        }
    }


    // Return minimum vote number
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if ((candidates[i].votes != min) && (!candidates[i].eliminated))
        {
            //if a candidates vote doesnt equal the min, we return false as no tie
            return false;
        }
    }

    // if we get here the election is tied between all candidates
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }

    // TODO
    return;
}