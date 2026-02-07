#include <iostream>
using namespace std;
int main() {
    int N;
    cin >> N;

    int num = 0;
    int cnt = 0;

    while (cnt < N) {
        num++;
        if (to_string(num).find("666") != string::npos) cnt++;
    }
    cout << num;

    return 0;
}