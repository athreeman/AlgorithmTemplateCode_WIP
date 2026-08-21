#include<bits/stdc++.h>
using namespace std;
using ll = long long;
bool is_Prime(ll x) {
    //判断x是否为质数
    //复杂度O(sqrt(n))
    if (x <= 1) {
        return false;
    }
    else if (x == 2) {
        return true;
    }
    else if (x % 2 == 0) {
        return false;
    }
    else {
        for (ll r = 3;r * r <= x;r += 2) {
            if (x % r == 0) {
                return false;
            }
        }
    }
    return true;
}