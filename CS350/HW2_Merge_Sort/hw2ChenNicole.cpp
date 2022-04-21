// Nicole Chen
// CS350 HW2: Merge Sort
// 1/13/2022

#include <iostream>
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
using namespace std;

void populate_array(int x[], int n)
{
    if (n == 0)
        return;

    for (int i = 0; i < n; ++i)
        x[i] = abs(random()) % (n + 1);

    return;
}

void print_array(int x[], int n)
{
    for (int i = 0; i < n; ++i)
        cout << x[i] << " - ";

    cout << "\n";
}

void merge(int lo, int mid, int hi, int x[])
{
    int size = hi - lo + 1; // size of temp array
    int temp[size];         // temp array to organize data
    int lf = lo;            // first of left half
    int rf = mid + 1;       // first of right half

    int i = 0; // counter for temp array

    while (lf <= mid && rf <= hi)
    {
        if (x[lf] > x[rf]) // left is bigger
        {
            temp[i] = x[rf]; // store right because it's smaller
            ++rf;            // increment to move right forward
        }
        else // right is bigger or equal
        {
            temp[i] = x[lf]; // store left because it's smaller
            ++lf;            // move left forward
        }
        ++i; // move temp forward
    }

    // still data in the left half
    while (lf <= mid)
    {
        temp[i] = x[lf];
        ++lf;
        ++i;
    }

    // still data in the right half
    while (rf <= hi)
    {
        temp[i] = x[rf];
        ++rf;
        ++i;
    }

    // update original area with temp's values;
    for (i = 0; i <= size && lo <= hi; ++i, ++lo)
        x[lo] = temp[i];

    return;
}

void merge_sort(int lo, int hi, int x[])
{
    if (lo >= hi)
        return;

    int mid = (lo + hi) / 2;

    // go left
    merge_sort(lo, mid, x); // left half

    // go right
    merge_sort(mid + 1, hi, x); // right half

    // merge two halves
    merge(lo, mid, hi, x);

    return;
}

int main()
{
    int n = 0;

    cout << "\nEnter n: ";
    cin >> n;
    cin.ignore(50, '\n');

    int x[n];
    populate_array(x, n);

    cout << "\nOriginal list: " << endl;
    print_array(x, n);

    merge_sort(0, n - 1, x);
    cout << "\nSorted list: " << endl;
    print_array(x, n);
    return 1;
}
