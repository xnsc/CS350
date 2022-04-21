// Nicole Chen
// HW4: Implement heap sort
// 1/27/2022

#include <iostream>
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include <sys/time.h>
using namespace std;

void createArray(int n, int heap[])
{
    srand(time(0));
    for (int i = 0; i < n; ++i)
        heap[i] = abs(random()) % (n + 1);

    return;
}

void printHeap(int n, int heap[])
{
    for (int i = 0; i < n; ++i)
        cout << heap[i] << " -- ";

    cout << endl;
    return;
}

void swap(int heap[], int a, int b)
{
    int temp = heap[a];
    heap[a] = heap[b];
    heap[b] = temp;
    return;
}

// n is the number of nodes
// i is the index of the root of the subtree we want to heapify
void heapify(int n, int i, int heap[])
{
    int left = (2 * i) + 1;  // left child index of heap[i]
    int right = (2 * i) + 2; // right child index of heap[i]
    int largest = i;

    // find the largest in the subtree
    if (heap[left] > heap[largest] && left < n)
        largest = left;

    // find the largest in the subtree
    if (heap[right] > heap[largest] && right < n)
        largest = right;

    // if heap[i] (root) is not the largest in the subtree,
    // swap with the largest
    if (i != largest)
    {
        swap(heap, i, largest);
        heapify(n, largest, heap);
    }

    return;
}

void heapSort(int n, int heap[])
{
    int start = (n / 2) - 1; // last non-leaf nodes

    // heapify each node starting from the last non-leaf node
    // creating the max heap
    for (int i = start; i >= 0; --i)
        heapify(n, i, heap);

    // prune one value each time
    for (int i = n - 1; i > 0; --i)
    {
        swap(heap, 0, i);    // swap first and last nodes
        heapify(i, 0, heap); // heapify the smaller heap
    }
}

int main()
{
    int n = 0;
    cout << "\nEnter n: ";
    cin >> n;
    cin.ignore(10, '\n');

    int heap[n];

    createArray(n, heap);

    cout << "\nOriginal array:" << endl;
    printHeap(n, heap);

    heapSort(n, heap);

    cout << "\nSorted array:" << endl;
    printHeap(n, heap);

    return 1;
}