#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int dice[3];
    for (int i = 0; i < 3; i++) {
        cin >> dice[i];
    }

    if (dice[0] == dice[1] && dice[1] == dice[2]) cout << 10000 + *dice * 1000;
    else if (dice[0] != dice[1] && dice[1] != dice[2] && dice[2] != dice[0]) cout << *max_element(dice, dice + 3) * 100;
    else cout << 1000 + (dice[0] + dice[1] + dice[2] - (dice[0] ^ dice[1] ^ dice[2])) / 2 * 100;
}
