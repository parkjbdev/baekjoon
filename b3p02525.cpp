#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b, c;

    cin >> a >> b;
    cin >> c;

    a += c / 60;
    b += c % 60;
    a += b / 60;
    b %= 60;
    a %= 24;

    cout << a << " " << b;

    return 0;
}
