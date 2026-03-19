#include <iostream>
#include <queue>
using namespace std;

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int N;
    cin >> N;

    priority_queue<int, vector<int>, greater<>> min_heap;

    for (int i = 0; i < N; ++i) {
        int input;
        cin >> input;

        if (input == 0) {
            if (min_heap.empty()) cout << 0 << "\n";
            else {
                cout << min_heap.top() << "\n";
                min_heap.pop();
            }
        } else {
            min_heap.push(input);
        }
    }

    return 0;
}
