#include <iostream>
#include <cmath>
using namespace std;

const int row = 4;
const int col = 4;

void copy_array(int source[], int dest[]) {
    for (int i = 0; i < col; ++i)
        dest[i] = source[i]; 
}

int minimum_sum(int matrix[row][col]) {
    int sums[col]; // to keep track of sums
    copy_array(matrix[row-1], sums);

    // start at second to last row
    for (int i = row-2; i >= 0; --i) {
        for (int j = 0; j <= i; ++j) {
            sums[j] = matrix[i][j] + min(sums[j], sums[j+1]);
        }
    }

    return sums[0]; // minimum sum
}

int main() {
    int matrix[row][col] = {
        {2},
        {5, 4},
        {1, 4, 7},
        {8, 6, 9, 6}
    };

    int sum = minimum_sum(matrix);
    cout << "\nMinimum sum: " << sum << endl << endl;

    return 1;
}