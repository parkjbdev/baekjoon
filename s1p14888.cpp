#include <iostream>
#include <vector>

using namespace std;

int max_val = -2000000000;
int min_val = 2000000000;

void bt(vector<int> &numbers, int ops[4], int idx, int result) {
    if (idx == numbers.size()) {
        if (result > max_val) max_val = result;
        if (result < min_val) min_val = result;

        return;
    }

    if (ops[0] > 0) {
        ops[0]--;
        bt(numbers, ops, idx + 1, result + numbers[idx]);
        ops[0]++;
    }

    if (ops[1] > 0) {
        ops[1]--;
        bt(numbers, ops, idx + 1, result - numbers[idx]);
        ops[1]++;
    }

    if (ops[2] > 0) {
        ops[2]--;
        bt(numbers, ops, idx + 1, result * numbers[idx]);
        ops[2]++;
    }

    if (ops[3] > 0) {
        ops[3]--;
        bt(numbers, ops, idx + 1, result / numbers[idx]);
        ops[3]++;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> numbers(N);
    for (int i = 0; i < N; ++i) cin >> numbers[i];

    int ops[4] = {0};
    for (int i = 0; i < 4; ++i) cin >> ops[i];

    bt(numbers, ops, 1, numbers[0]);

    cout << max_val << "\n" << min_val;

    return 0;
}
