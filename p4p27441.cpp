#include <iostream>
#define MAX 20

using namespace std;

unsigned long long dp[MAX][4] = {0};

unsigned long long upow10(int n) {
    unsigned long long ret = 1;
    for (int i = 0; i < n; i++)
        ret *= 10;

    return ret;
}

unsigned long long solve(int len, int state) {
    if (state == 3) return dp[len][state] = upow10(len);
    if (len == 0) return 0;
    if (dp[len][state] != 0) return dp[len][state];

    return dp[len][state] = solve(len - 1, state + 1) + solve(len - 1, 0) * 9;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    unsigned long long N;
    cin >> N;

    int target_len = 3;

    while (true) {
        unsigned long long cnt = solve(target_len - 1, 0) * 8
                                 + solve(target_len - 1, 1);
        if (N <= cnt) break;

        N -= cnt;
        target_len++;
    }

    int curr_state = 0;
    for (int i = target_len; i >= 1; i--) {
        for (int d = (i == target_len ? 1 : 0); d <= 9; d++) {
            int next_state = (curr_state == 3)
                                 ? 3
                                 : (d == 6 ? curr_state + 1 : 0);
            unsigned long long cnt = solve(i - 1, next_state);

            if (N <= cnt) {
                cout << d;
                curr_state = next_state;
                break;
            } else N -= cnt;
        }
    }

    return 0;
}
