#include <iostream>
using namespace std;

int main() {
    int N;
    cin >> N;

    for (int i = N / 5; i >= 0; i--) {
        for (int j = N - i; j >= 0; j--) {
            if (5 * i + 3 * j == N) {
                cout << i + j;
                return 0;
            }
        }
    }
    cout << -1;
    return 0;
}
