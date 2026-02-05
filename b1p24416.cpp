#include <iostream>
#define MAX 50

using namespace std;

int recur_call = 0;
int fibo_recur(int n) {
    ++recur_call;
    if (n == 1 || n == 2) return 1;
    return fibo_recur(n - 1) + fibo_recur(n - 2);
}

int memo[MAX] = {0, 1, 1,};

int dp_call = 0;
int fibo_dp(int n) {
    for (int i = 3; i <= n; i++) {
        ++dp_call;
        memo[i] = memo[i - 1] + memo[i - 2];
    }

    return memo[n];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // cout << fibo_recur(n) << " " << recur_call << endl;
    cout << fibo_dp(n) << " " << dp_call << endl;

    return 0;
}
