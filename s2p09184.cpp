#include <iostream>
using namespace std;
#define MAX 21

int memo[MAX][MAX][MAX] = {0,};

int w(int a, int b, int c);

int w_wrapper(int a, int b, int c) {
    if (a <= 0 || b <= 0 || c <= 0 || a > 20 || b > 20 || c > 20) {
        return w(a, b, c);
    }

    if (memo[a][b][c] != 0) return memo[a][b][c];
    return memo[a][b][c] = w(a, b, c);
}

int w(int a, int b, int c) {
    if (a <= 0 || b <= 0 || c <= 0) return 1;
    if (a > 20 || b > 20 || c > 20) return w_wrapper(20, 20, 20);

    if (a < b && b < c) {
        return w_wrapper(a, b, c - 1) +
               w_wrapper(a, b - 1, c - 1) -
               w_wrapper(a, b - 1, c);
    }

    return w_wrapper(a - 1, b, c) +
           w_wrapper(a - 1, b - 1, c) +
           w_wrapper(a - 1, b, c - 1) -
           w_wrapper(a - 1, b - 1, c - 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (true) {
        int a, b, c;
        cin >> a >> b >> c;
        if (a == -1 && b == -1 && c == -1) break;

        cout << "w(" << a << ", " << b << ", " << c << ") = " <<
                w_wrapper(a, b, c) << endl;
    }

    return 0;
}
