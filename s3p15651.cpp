#include <iostream>
#include <vector>

using namespace std;

vector<int> trace;

void picker(int n, int m) {
    if (m == 0) {
        for (int t: trace) {
            cout << t << " ";
        }
        cout << "\n";
        return;
    }

    for (int i = 1; i <= n; i++) {
        trace.push_back(i);
        picker(n, m - 1);
        trace.pop_back();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    trace = vector<int>();
    picker(n, m);

    return 0;
}
