#include <iostream>
#include <vector>
using namespace std;
#define N 9

int sudoku[N][N] = {0,};
int col_mask[9] = {0,};
int row_mask[9] = {0,};
int sqr_mask[9] = {0,};

int sqr_idx(const int x, const int y) {
    return (int) (x / 3) * 3 + (int) (y / 3);
}

void fill_sudoku(const int x, const int y, const int num) {
    sudoku[x][y] = num;
    row_mask[x] |= 0b1 << num;
    col_mask[y] |= 0b1 << num;
    sqr_mask[(int) (x / 3) * 3 + (int) (y / 3)] |= 0b1 << num;
}

void clear_sudoku(const int x, const int y) {
    row_mask[x] &= ~(0b1 << sudoku[x][y]);
    col_mask[y] &= ~(0b1 << sudoku[x][y]);
    sqr_mask[sqr_idx(x, y)] &= ~(0b1 << sudoku[x][y]);
    sudoku[x][y] = 0;
}

bool exists(const int mask, const int num) {
    return (mask & (0b1 << num)) == (0b1 << num);
}

bool solve_sudoku(vector<pair<int, int> > &blanks,
                  int blank_idx) {
    if (blank_idx == blanks.size()) return true;
    for (int i = 1; i <= 9; ++i) {
        const int x = blanks[blank_idx].first;
        const int y = blanks[blank_idx].second;
        const int s = sqr_idx(x, y);
        if (exists(row_mask[x], i) ||
            exists(col_mask[y], i) ||
            exists(sqr_mask[s], i))
            continue;

        fill_sudoku(x, y, i);
        if (solve_sudoku(blanks, blank_idx + 1)) return true;
        clear_sudoku(x, y);
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<pair<int, int> > blanks;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> sudoku[i][j];
            if (sudoku[i][j] == 0) blanks.emplace_back(i, j);
            else fill_sudoku(i, j, sudoku[i][j]);
        }
    }

    solve_sudoku(blanks, 0);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << sudoku[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}
