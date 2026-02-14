#include <iostream>
#include <string>
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

    string target_num;
    cin >> target_num;

    unsigned long long target_len = target_num.length();

    unsigned long long cnt = 0;
    int digit_len = 3;

    while (digit_len < target_len) {
        cnt += solve(digit_len - 1, 0) * 8 + solve(digit_len - 1, 1);
        digit_len++;
    }

    int curr_state = 0;
    for (int i = target_len; i >= 1; i--) {
        for (int d = (i == target_len ? 1 : 0); d <= 9; d++) {
            int next_state = (curr_state == 3)
                                 ? 3
                                 : (d == 6 ? curr_state + 1 : 0);
            if (target_num[target_len - i] - '0' > d) {
                cnt += solve(i - 1, next_state);
            }
            if (target_num[target_len - i] - '0' == d) {
                curr_state = next_state;
                break;
            }
        }
    }

    cout << cnt + 1;

    return 0;
}
