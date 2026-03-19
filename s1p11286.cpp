#include <iostream>
#include <queue>
using namespace std;

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int N;
    cin >> N;

    auto cmp = [](const pair<int, int> &a, const pair<int, int> &b) {
        if (a.first == b.first) return a.second > b.second;
        return a.first > b.first;
    };

    std::priority_queue<pair<int, int>, vector<pair<int, int> >, decltype(cmp)>
            pq(cmp);

    for (int i = 0; i < N; ++i) {
        int input;
        cin >> input;

        if (input == 0) {
            if (pq.empty()) cout << 0 << "\n";
            else {
                cout << pq.top().second << "\n";
                pq.pop();
            }
        } else {
            pair<int, int> p = {abs(input), input};
            pq.push(p);
        }
    }

    return 0;
}
