#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int main () {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    vector<int> P(N);
    for (int i = 0; i < N; ++i) {
        cin >> P[i];
    }

    sort(P.begin(), P.end(), less<>());

    int total_time = 0;
    for (int i = 0;i < N;++i) {
        total_time += (P[i] * (N - i));
    }

    cout << total_time << "\n";

    return 0;
}