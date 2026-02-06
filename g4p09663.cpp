#include <iostream>
using namespace std;

bool col[15];
bool diag1[30];
bool diag2[30];

int sol_cnt = 0;

void nqueen(int N, int row) {
    if (row == N) {
        sol_cnt++;
        return;
    }

    for (int c = 0; c < N; c++) {
        if (!(!col[c] && !diag1[row + c] && !diag2[row - c + N])) continue;
        col[c] = diag1[row + c] = diag2[row - c + N] = true;
        nqueen(N, row + 1);
        col[c] = diag1[row + c] = diag2[row - c + N] = false;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    nqueen(N, 0);
    cout << sol_cnt << endl;

    return 0;
}
