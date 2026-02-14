#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int h, m;
    cin >> h >> m;

    h = m < 45 ? (h - 1 < 0 ? h + 23 : h - 1) : h;
    m = m < 45 ? m + 15 : m - 45;

    cout << h << " " << m;

    return 0;
}
