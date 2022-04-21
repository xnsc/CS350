#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Find the location of the first occurrence of pattern in text
// or say that it does not occur if that is the case.
// If you find the pattern in the text, output the index of the
// first letter in text where the pattern first occurs.

// You must also print the total number of character compairsons that
// the program made.

// If the number of unchecked characters in the text is ever less than
// the length of the pattern the algorithm must stop.

// NOTE:  All test texts and patterns should not contain any white space
//        (e.g. blank space character, newline, tab, etc.) as scanf
//        will stop on such an input character.

int main()
{
  char text[10000];
  char pattern[200];
  int m, n;

  printf("enter text : ");
  scanf("%s", text);
  printf("enter pattern you are searching for : ");
  scanf("%s", pattern);

  m = strlen(pattern);
  n = strlen(text);
  printf("The pattern has %d characters and the text has %d characters.\n", m, n);

  // HORSPOOL'S ALGORITHM
  int table[128];
  for (int i = 0; i < 128; ++i) // plug m into each element in ASCII table
    table[i] = m;

  // sets shifting values
  table[pattern[m - 1]] = m; // set the value of the very last element
  for (int i = 0; i < m - 1; ++i)
    table[pattern[i]] = m - (i + 1); // ex. 6 - (0+1) = 5

  int first = 0;
  int comparisons = 0;
  while (first + m <= n) // don't go out of text bounds
  {
    ++comparisons;
    if (pattern[m - 1] == text[first + (m - 1)])
    {
      if (m == 1)
      {
        printf("\nStarting index: %d", first);
        printf("\nComparisons: %d\n\n", comparisons);
        return 1;
      }
      else
      {
        // for loop here to compare the rest
        // go until second to last character in pattern b/c we already
        // compared the last one
        for (int i = 0; i < (m - 1); ++i)
        {
          ++comparisons;
          if (text[first + i] != pattern[i])
            break;
          // there is a match
          if (i == (m - 2))
          {
            printf("\nStarting index: %d", first);
            printf("\nComparisons: %d\n\n", comparisons);
            return 1;
          }
        }
      }
    }
    first += table[text[first + (m - 1)]];
  }

  printf("\nPattern not found.");
  printf("\nComparisons: %d\n\n", comparisons);
  return -1;
}
