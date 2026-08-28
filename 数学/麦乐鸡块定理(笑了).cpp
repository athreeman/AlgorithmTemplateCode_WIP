#include<bits/stdc++.h>
using namespace std;

// 给定两个互质的正整数a, b
// 无法由ax + by = c得到的最大整数是ab - a - b

void MLJK(int a, int b) {
    if (gcd(a, b) != 1) {
        cout << "No delicious!!!" << '\n';
    }
    else {
        cout << a * b - a - b << '\n';
        cout << "Perfect!!!" << '\n';
    }
}
