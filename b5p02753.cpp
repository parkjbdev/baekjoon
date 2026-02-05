#include<iostream>

int main() {
    int y;
    std::cin >> y;
    std::cout << ((!(y % 4) && y % 100) || !(y % 400));
}
