#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    unsigned long long answer = 0;

    int N;
    cin >> N;

    vector<int> dist(N - 1);
    for (int i = 0; i < N - 1; ++i) {
        cin >> dist[i];
    }

    int min_cost = 1000000000;
    for (int i = 0; i < N; ++i) {
        int cost;
        cin >> cost;
        if (cost < min_cost) min_cost = cost;
        answer += (static_cast<unsigned long long>(min_cost) * static_cast<
                       unsigned long long>(dist[i]));
    }

    cout << answer;

    return 0;
}
