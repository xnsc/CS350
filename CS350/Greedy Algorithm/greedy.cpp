#include <iostream>
#include <cstring>
using namespace std;

int f(int n) {
    if (n == 4)
        return 1;
    if (n == 3)
        return 1;
    if (n == 1)
        return 1;
    if (n == 2)
        return 2;
    
    int a = f(n-4);
    int b = f(n-3);
    int c = f(n-1);

    int min = a;
    if (b < min) 
        min = b;
    if (c < min)
        min = c;
    
    return min+1;
}

int main() {
    int n = 0;
    cout << "\nEnter a number: ";
    cin >> n;
    cin.ignore(10, '\n');

    cout << "\nCoins: " << f(n) << endl << endl;
    return 1;
}