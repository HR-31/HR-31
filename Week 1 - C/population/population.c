#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int s;
  do
  {
      s = get_int("Start size? ");
  }
  while (s < 9);


    // TODO: Prompt for end size
    int e;
  do
  {
      e = get_int("End size? ");
  }
  while (e < s);

    // TODO: Calculate number of years until we reach threshold
    int y = 0;

    // Update population size
    while (s < e)
    {
        s = s + (s / 3) - (s / 4);  // Start no. of llamas + the added llamas - the removed llamas
        y++;                        // Updating the no. of years tracker by adding 1 to Y
    }

    // TODO: Print number of years
    printf("Years: %i\n", y);




}
