#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<vector<int> > matrix(N, vector<int>(N, 0));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> matrix[i][j];
        }
    }

    typedef tuple<int, int, int> T;

    priority_queue<T> pq;

    for (int j = 0; j < N; j++)
        pq.emplace(matrix[N - 1][j], N - 1, j);

    for (int i = 0; i < N - 1; i++) {
        auto [v, x, y] = pq.top();
        pq.pop();
        if (x > 0) pq.emplace(matrix[x - 1][y], x - 1, y);
    }

    cout << get<0>(pq.top());

    return 0;
}
