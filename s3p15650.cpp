#include <iostream>
#include <vector>

using namespace std;

vector<bool> visit;
vector<int> trace;

void picker(int n, int m) {
    if (m == 0) {
        for (int t: trace) {
            cout << t << " ";
        }
        cout << "\n";
        return;
    }

    int peek = (trace.empty() ? 0 : trace.back()) + 1;
    for (int i = peek; i <= n; i++) {
        if (visit[i - 1]) continue;

        visit[i - 1] = true;
        trace.push_back(i);
        picker(n, m - 1);
        trace.pop_back();
        visit[i - 1] = false;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    visit = vector<bool>(n);
    trace = vector<int>();
    picker(n, m);

    return 0;
}
