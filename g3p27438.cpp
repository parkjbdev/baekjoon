#ifdef TRIAL1
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

int main(int argc, char **argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;

    if (argc == 1) cin >> N;
    else N = stoi(argv[1]);

    // partial (digits - k)
    // 9 * 10 ** (k - 1) * k + 10 ** k;

    int prev_acc_cnt = 0, acc_cnt = 0;
    int digits = 3;

    vector<vector<int> > list_all;

    for (digits = 3; acc_cnt < N; digits++) {
        vector<int> list = {0};

        prev_acc_cnt = acc_cnt;

        for (int k = 0; k <= digits - 3; k++) {
            int power = pow(10, k);
            int sub = 0;
            for (int i = list.size() - 1; i >= 0; i--) {
                sub += list[i] * (list.size() + 1 - i);
            }
            acc_cnt += (9 * power / 10 * k + power - sub);
            list.push_back(9 * power / 10 * k + power - sub);
        }

        reverse(list.begin(), list.end());
        list.pop_back();
        list_all.push_back(list);
    }

    digits--;

    int tmp = 0;
    for (int i = 0; i < digits - 4; i++) {
        tmp = tmp * 10 + 9;
    }
    int num = 666 + tmp * 1000;

    num++;

    int six_cnt = prev_acc_cnt;
    while (six_cnt < N) {
        num++;
        if (to_string(num).find("666") != string::npos) six_cnt++;
    }
    cout << num << "\n";

    return 0;
}
#endif

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
