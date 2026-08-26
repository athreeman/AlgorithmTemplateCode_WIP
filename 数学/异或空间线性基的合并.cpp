#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int MAXN = 2e5;
const int bit = 30;

// 把x插入到b里去
void insert(ll x, ll* b) {
    for (int i = bit;i >= 0;i--) {
        if ((x >> i) & 1) {
            if (b[i] == 0) {
                b[i] = x;
                return;
            }
            x ^= b[i];
        }
    }
}

// 把b的基合并到t里
void merge(ll* b, ll* t) {
    for (int i = bit;i >= 0;i--) {
        if (b[i] != 0) {
            insert(b[i], t);
        }
    }
}
