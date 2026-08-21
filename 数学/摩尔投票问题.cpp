#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5;
int a[MAXN + 1];
bool check(int n, int x) {
    for (int i = 1, j = 0;i <= n;i++) {
        j += (a[i] == x);
        if (j > n / 2) {
            return true;
        }
    }
    return false;
}
int waterNumber(int n) {
    int hp = 0;
    int cand = -1;
    for (int i = 1;i <= n;i++) {
        if (cand == -1) {
            cand = a[i];
            hp = 1;
        }
        else {
            if (a[i] == cand) {
                hp++;
            }
            else {
                if (--hp == 0) {
                    cand = -1;
                }
            }
        }
    }
    if (hp == 0)return -1;
    return check(n, cand) ? cand : -1;
}
