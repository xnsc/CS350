#include <iostream>
#include <cmath>
using namespace std;


int max_profit_recursive(int n, int prices[]) {
    int profits[n+1];

    profits[0] = 0;

    for (int i = 1; i <= n+1; ++i) {
        int max_profit = -1;
        for (int j = 1; j <= i; ++j) {
            max_profit = max(max_profit, prices[j-1] + profits[i-j]);
        }
        profits[i] = max_profit;
    }

    return profits[n];
}

int main() {
    int table[] = {1, 5, 8, 9, 10};

    int n = 0;
    cout << "\nEnter n: ";
    cin >> n;

    cout << "\nMax profit is " << max_profit_recursive(n, table) << endl << endl;

    return 1;
}

