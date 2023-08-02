#include <cs50.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    string name;
    int votes;
}
candidate;

void sort_candidates(candidate arr[], int size);

int main(void)
{
    candidate candidates[] =
{
    {"Alice", 5},
    {"Bob", 2},
    {"Charlie", 7},
    {"Dave", 2},
    {"Eve", 9},
    {"Frank", 1}
};
    sort_candidates(candidates, 6);

    if (candidates[0].votes > candidates[1].votes)
    {
        printf("%s\n", candidates[0].name);
    }
    else if (candidates[0].votes == candidates[1].votes)
    {
        printf("%s\n%s\n", candidates[0].name, candidates[1].name);
    }

// The candidates array should now be:
// {"Charlie", 7}, {"Eve", 7}, {"Alice", 5}, {"Bob", 2}, {"Dave", 2}, {"Frank", 1}}
}

void sort_candidates(candidate arr[], int size)
{
    for (int step = 0; step < size - 1; step++)
    {
        int max_votes = step;
        for (int i = step + 1; i < size; i++)
        {
            if (arr[i].votes > arr[max_votes].votes)
            {
                max_votes = i;
            }
        }

        candidate temp = arr[step];
        arr[step] = arr[max_votes];
        arr[max_votes] = temp;
    }
}
