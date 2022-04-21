// Nicole Chen
// HW1: Linear and Binary Search

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <sys/time.h>

#define M 100000000
// 100 million

int x[M];
int N;

void print_array(int lo, int hi)
{
  int i;
  for (i = lo; i <= hi; i++)
  {
    printf("(%d %d) ", i, x[i]);
  }
  printf("\n");
}

void create_array_gap_at_least_two()
{
  int i;
  int d;
  srandom(300); // nothing special about 300
  x[0] = abs(random()) % 100;
  for (i = 1; i < N; i++)
  {
    //      d = abs(random()) % 10 ; // non-decreasing
    //      d = 1 + abs(random()) % 10 ; // strictly increasing
    d = 2 + abs(random()) % 10; // strictly increasing and gap of at least 2
    x[i] = x[i - 1] + d;
  }
}

int linear_search(int lo, int hi, int key)
// if key is found in the global integer array, x ,
// then return the integer location, otherwise return -1
{
  for (int i = lo; i < hi; ++i)
  {
    if (x[i] == key)
      return i;
  }
  return -1;
}

int binary_search(int lo, int hi, int key)
// if key is found in the global integer array, x ,
// then return the integer location, otherwise return -1
{
  if (lo > hi)
    return -1;

  int mid = floor((lo + hi) / 2);

  if (key == x[mid]) // match
    return mid;
  else if (key > x[mid]) // key is higher
    return binary_search(mid + 1, hi, key);
  else if (key < x[mid]) // key is lower
    return binary_search(lo, mid - 1, key);
  else // end of search
    return -1;
}

int non_recursive_binary_search(int lo, int hi, int key)
// if key is found in the global integer array, x ,
// then return the integer location, otherwise return -1
{
  int mid = 0;
  while (key != x[mid])
  {
    mid = floor((lo + hi) / 2);
    if (lo > hi)
      return -1;

    if (key > x[mid]) // key is higher
      lo = mid + 1;
    else if (key < x[mid]) // key is lower
      hi = mid - 1;
    else // found
      return mid;
  }
  return -1;
}

// begin TIMING variables
int signal;
struct timeval Tp;
struct timezone Tzp;
long sec, usec;
double dsec1, dsec2;
// end TIMING variables

void begin_timing()
{
  signal = gettimeofday(&Tp, &Tzp);
  usec = Tp.tv_usec;
  sec = Tp.tv_sec;
  dsec1 = sec + usec / 1000000.0;
}

void end_timing()
{
  signal = gettimeofday(&Tp, &Tzp);
  usec = Tp.tv_usec;
  sec = Tp.tv_sec;
  dsec2 = sec + usec / 1000000.0;
}

int test01(int size)
{
  int res, key, i;
  unsigned long a;
  int numdisagreements;

  if (size > M)
  {
    printf("size request of %d is too big\n", size);
  }

  N = size;
  create_array_gap_at_least_two();
  //  print_array(0,100) ;

  int numreps = 100;
  int keyA[1000], locA[1000];
  int keyB[1000], locB[1000];
  int keyC[1000], locC[1000];

  printf("numreps = %d\n", numreps);

  //$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

  //======================================================================
  printf("Testing searches for items that DO exist :\n");
  //======================================================================

  begin_timing();
  srandom(100);
  for (i = 0; i < numreps; i++)
  {
    a = random() % N;
    // printf("{%lu}",a) ;
    key = x[a]; // so these items WILL be found
    keyA[i] = key;
    locA[i] = linear_search(0, N - 1, key);
  }
  end_timing();
  printf("Average Linear search of %d items took %18lf seconds.\n",
         N, (dsec2 - dsec1) / numreps);

  //======================================================================

  begin_timing();
  srandom(100);
  for (i = 0; i < numreps; i++)
  {
    a = random() % N;
    key = x[a]; // so these items WILL be found
    keyB[i] = key;
    locB[i] = binary_search(0, N - 1, key);
  }
  end_timing();
  printf("Average Binary search of %d items took %18lf seconds.\n",
         N, (dsec2 - dsec1) / numreps);

  //======================================================================

  begin_timing();
  srandom(100);
  for (i = 0; i < numreps; i++)
  {
    a = random() % N;
    key = x[a]; // so these items WILL be found
    keyC[i] = key;
    locC[i] = non_recursive_binary_search(0, N - 1, key);
  }
  end_timing();
  printf("Average Non-Recursive Binary search of %d items took %18lf seconds.\n",
         N, (dsec2 - dsec1) / numreps);

  //======================================================================

  numdisagreements = 0;
  for (i = 0; i < numreps; i++)
  {
    if (locA[i] != locB[i])
    {
      printf("[%d,%d]   [%d,%d]\n", locA[i], keyA[i], locB[i], keyB[i]);
      numdisagreements++;
    }
  }
  printf("numdisagreements between linear and binary search = %d\n",
         numdisagreements);

  numdisagreements = 0;
  for (i = 0; i < numreps; i++)
  {
    if (locA[i] != locC[i])
    {
      printf("[%d,%d]   [%d,%d]\n", locA[i], keyA[i], locC[i], keyC[i]);
      numdisagreements++;
    }
  }
  printf("numdisagreements between linear and non-recursive binary search = %d\n",
         numdisagreements);

  //$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

  //======================================================================
  printf("Testing searches for items that do NOT exist :\n");
  //======================================================================

  begin_timing();
  srandom(100);
  for (i = 0; i < numreps; i++)
  {
    a = random() % N;
    // printf("{%lu}",a) ;
    key = x[a] + 1;
    // so these items will NOT be found given a gapping >= 2
    keyA[i] = key;
    locA[i] = linear_search(0, N - 1, key);
  }
  end_timing();
  printf("Average Linear search of %d items took %18lf seconds.\n",
         N, (dsec2 - dsec1) / numreps);

  //======================================================================

  begin_timing();
  srandom(100);
  for (i = 0; i < numreps; i++)
  {
    a = random() % N;
    key = x[a] + 1;
    // so these items will NOT be found given a gapping >= 2
    keyB[i] = key;
    locB[i] = binary_search(0, N - 1, key);
  }
  end_timing();
  printf("Average Binary search of %d items took %18lf seconds.\n",
         N, (dsec2 - dsec1) / numreps);

  //======================================================================

  begin_timing();
  srandom(100);
  for (i = 0; i < numreps; i++)
  {
    a = random() % N;
    key = x[a] + 1;
    // so these items will NOT be found given a gapping >= 2
    keyC[i] = key;
    locC[i] = non_recursive_binary_search(0, N - 1, key);
  }
  end_timing();
  printf("Average Non-Recursive Binary search of %d items took %18lf seconds.\n",
         N, (dsec2 - dsec1) / numreps);

  //======================================================================

  numdisagreements = 0;
  for (i = 0; i < numreps; i++)
  {
    if (locA[i] != locB[i])
    {
      printf("[%d,%d]   [%d,%d]\n", locA[i], keyA[i], locB[i], keyB[i]);
      numdisagreements++;
    }
  }
  printf("numdisagreements between linear and binary search = %d\n",
         numdisagreements);

  numdisagreements = 0;
  for (i = 0; i < numreps; i++)
  {
    if (locA[i] != locC[i])
    {
      printf("[%d,%d]   [%d,%d]\n", locA[i], keyA[i], locC[i], keyC[i]);
      numdisagreements++;
    }
  }
  printf("numdisagreements between linear and non-recursive binary search = %d\n",
         numdisagreements);
}

int main()
{
  test01(M);
}
