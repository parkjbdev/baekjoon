#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Sched {
    unsigned int start;
    unsigned int end;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    vector<Sched> scheds(N);
    for (int i = 0; i < N; i++) {
        cin >> scheds[i].start >> scheds[i].end;
    }

    sort(scheds.begin(), scheds.end(), [](const Sched &a, const Sched &b) {
        if (a.end == b.end) return a.start < b.start;
        return a.end < b.end;
    });

    unsigned int last_time = 0;
    int cnt = 0;

    for (int i = 0; i < N; i++) {
        if (scheds[i].start >= last_time) {
            last_time = scheds[i].end;
            cnt++;
        }
    }

    cout << cnt << "\n";

    return 0;
}
