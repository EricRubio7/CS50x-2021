#include <cs50.h>
#include <stdio.h>
#include <string.h>


//Got a lot of help on this one from: CS50 PSet3: Tideman: https://joseph28robinson.medium.com/cs50-pset3-tideman-87f22f0f0bc3
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
bool cycle(int end, int cycle_start);


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
        
        //printf("Voter %i - ranks[0]: %i\n", i, ranks[0]);
        //printf("Voter %i - ranks[1]: %i\n", i, ranks[1]);
        //printf("Voter %i - ranks[2]: %i\n", i, ranks[2]);
        
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
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0) //Check given name is that of a candidate
        {
            ranks[rank] = i; //Assign the "rank" preference to the appropiate candidate index
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    //Battles rank[i] vs rank[j] = i + 1 and stores the winner in preferences
    for (int i = 0; i < candidate_count; i++) 
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
  
  
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++) 
    {
        for (int j = i + 1; j < candidate_count; j++) 
        {
            if (preferences[i][j] > preferences[j][i]) //Records winner and loser per each pair
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
        
    }
    // TODO
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    
    //Implement bubble sort
    for (int i = pair_count - 1; i >= 0; i--) //Loop trough every pair
    {
        for (int j = 0; j <= i - 1; j++) //Loop through preferences to compare strength of victory
        {
            if ((preferences[pairs[j].winner][pairs[j].loser]) <  
                (preferences[pairs[j + 1].winner][pairs[j + 1].loser])) 
            {
                pair temp = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temp;
            }
        }
    }
    return;
}


//Test for cycle by checking arrow coming into each canditate
bool cycle(int end, int cycle_start)
{
    //Return true if there is a cycle created (Recursion base case)
    if (end == cycle_start)
    {
        return true;
    }
    
    //Loop through candidates (Recursive case)
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[end][i])
        {
            if (cycle(i, cycle_start))
            {
                return true;
            }
        }
    }
    return false; 
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    
    //Loop through pairs
    for (int i = 0; i < pair_count; i++)
    {
        //If ctcle functions returns false, lock the pair
        if (!cycle(pairs[i].loser, pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    
    return;
}

// Print the winner of the election
void print_winner(void)
{
    
    //Winner is the candidate with no arrows pointing to them
    
    for (int i = 0; i < candidate_count; i++)
    {
        int false_count = 0;
        
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == false)
            {
                false_count++;
                if (false_count == candidate_count)
                {
                    printf("%s\n", candidates[i]);
                }
            }
        }
    }
    
    // TODO
    return;
}
