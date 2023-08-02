// Simulate genetic inheritance of blood type

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Each person has two parents and two alleles
typedef struct person
{
    struct person *parents[2];
    char alleles[2];
}
person;

const int GENERATIONS = 3;
const int INDENT_LENGTH = 4;

person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();

int main(void)
{
    // Seed random number generator
    srand(time(0));

    // Create a new family with three generations
    person *p = create_family(GENERATIONS);

    // Print family tree of blood types
    print_family(p, 0);

    // Free memory
    free_family(p);
}

// Create a new individual with `generations`
person *create_family(int generations)
{
    // TODO: Allocate memory for new person

    person *p = malloc(sizeof(person));

    // If there are still generations left to create
    if (generations > 1)
    {
        // Create two new parents for current person by recursively calling create_family
        person *parent0 = create_family(generations - 1);
        person *parent1 = create_family(generations - 1);

        // TODO: Set parent pointers for current person
        p->parents[0] = parent0;
        p->parents[1] = parent1;


        // TODO: Randomly assign current person's alleles based on the alleles of their parents
        char b = ' ';
        char d = ' ';

        //Generating child's Allele 0 from parent 0
        int a = rand() % 2;
        if (a == 0)
        {
            b = parent0->alleles[0];
        }
        else
        {
            b = parent0->alleles[1];
        }

        //Generating child's Allele 1 from parent 1 
        int c = rand() % 2;
        if (c == 0)
        {
            d = parent1->alleles[0];
        }
        else
        {
            d = parent1->alleles[1];
        }

        //Need to combine b & d to make new person's pair of alleles
        p->alleles[0] = b;
        p->alleles[1] = d;

    }

    // If there are no generations left to create
    else
    {
        // TODO: Set parent pointers to NULL
        p->parents[0] = NULL;
        p->parents[1] = NULL;

        // TODO: Randomly assign alleles
        char b = ' ';
        char d = ' ';

        //Generate Allele one for Child from A, B, O
        int a = rand() % 3;
        if (a == 0)
        {
            b = 'A';
        }
        else if (a == 1)
        {
            b = 'B';
        }
        else
        {
            b = 'O';
        }

        //Generate Allele two for Child from A, B, O
        int c = rand() % 3;
        if (c == 0)
        {
            d = 'A';
        }
        else if (c == 1)
        {
            d = 'B';
        }
        else
        {
            d = 'C';
        }

        //Initialising the randomly generated Alleles to the person array
        p->alleles[0] = b;
        p->alleles[1] = d;

    }

    // TODO: Return newly created person
    return p;


}

// Free `p` and all ancestors of `p`.
void free_family(person *p)
{
    // TODO: Handle base case
    if (p == NULL)
    {
        return;
    }

    // TODO: Free parents recursively
    for (int i = 0; i < 2; i++)
    {
        free_family(p->parents[i]);
    }

    // TODO: Free child
    free(p);
}

// Print each family member and their alleles.
void print_family(person *p, int generation)
{
    // Handle base case
    if (p == NULL)
    {
        return;
    }

    // Print indentation
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    // Print person
    if (generation == 0)
    {
        printf("Child (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    else if (generation == 1)
    {
        printf("Parent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    else
    {
        for (int i = 0; i < generation - 2; i++)
        {
            printf("Great-");
        }
        printf("Grandparent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }

    // Print parents of current generation
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

// Randomly chooses a blood type allele.
char random_allele()
{
    int r = rand() % 3;
    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}
