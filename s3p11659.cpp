#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<int> accumulated_sum(N + 1);
    for (int i = 0; i < N; ++i) {
        cin >> accumulated_sum[i + 1];
        accumulated_sum[i + 1] += accumulated_sum[i];
    }

    for (int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        cout << accumulated_sum[b] - accumulated_sum[a - 1] << "\n";
    }

    return 0;
}
