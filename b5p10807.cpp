#include <iostream>
#include <algorithm>
using namespace std;
int main () {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    vector<int> arr(N);
    for (int i = 0; i < N; ++i) {
        cin >> arr[i];
    }
    int v;
    cin >> v;

    long cnt = count(arr.begin(), arr.end(), v);

    cout << cnt << "\n";

    return 0;
}