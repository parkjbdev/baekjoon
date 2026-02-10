#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<pair<int, int> > spec;

    for (int i = 0; i < N; ++i) {
        int x, y;
        cin >> x >> y;
        spec.emplace_back(x, y);
    }

    for (int i = 0; i < N; i++) {
        int rank = 1;
        auto me = spec[i];
        for (int j = 0; j < N; j++) {
            if (i == j) continue;
            auto notme = spec[j];
            rank += (me.first < notme.first && me.second < notme.second);
        }
        cout << rank << " ";
    }

    return 0;
}
