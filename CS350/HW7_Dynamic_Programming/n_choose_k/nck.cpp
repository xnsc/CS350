#include <iostream>
#include <cmath>
using namespace std;

int f_recursive(int n, int k) {
    if (n == k)
        return 1;

    if (k == 1)
        return n;

    return f_recursive(n-1, k-1) + f_recursive(n-1, k);
}

// memoization?
int f(int n, int k) {
    int chart[n+1][k+1];

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= min(i, k); ++j) {
            if (j == 0 || j == i)
                chart[i][j] = 1;
            else 
                chart[i][j] = chart[i-1][j-1] + chart[i-1][j];
        }
    }
    return chart[n][k];
}

int main() {
    int n = 5;
    int k = 2;

    cout << endl << n << " choose " << k << " = " << f(n, k) << endl << endl;

    return 1;
}