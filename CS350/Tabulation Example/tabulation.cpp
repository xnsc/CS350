#include <iostream>
#include <math.h>
using namespace std;

int f(int n) {
    int t[n];
    t[0] = 0;
    t[1] = 1;
    t[2] = 2;
    t[3] = 1;

    int min = 0;
    int k = 0;

    if (n == 0 || n == 1 || n == 2 || n == 3)
        return t[n];
    else {
        for (k = 4; k <= n; ++k) {
            min = t[k-1];
            if (t[k-3] < min)
                min = t[k-3];
            if (t[k-4] < min)
                min = t[k-4];
            t[k] = 1 + min;
        }
    }
    return t[n];
}
int main() {

    int n = 0;
    cout << "\nEnter n: ";
    cin >> n;

    cout << "\nf(n) = " << f(n) << endl << endl;

    return 1;
}