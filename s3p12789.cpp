#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int main() {
    int N;
    cin >> N;

    vector<int> main_line(N);
    stack<int> temp_line;
    for (int i = 0; i < N; i++) cin >> main_line[i];

    int current = 1;

    for (int i = 0; i < N; i++) {
        temp_line.push(main_line[i]);

        while (!temp_line.empty() && temp_line.top() == current) {
            temp_line.pop();
            current++;
        }
    }

    if (temp_line.empty()) cout << "Nice";
    else cout << "Sad";

    return 0;
}
