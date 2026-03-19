#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    priority_queue<int, vector<int>, greater<> > min_heap;
    for (int i = 0; i < N * N; i++) {
        int input;
        cin >> input;
        if (min_heap.size() == N) {
            if (min_heap.top() > input) continue;
            else min_heap.pop();
        }
        min_heap.push(input);
    }

    cout << min_heap.top();

    return 0;
}
