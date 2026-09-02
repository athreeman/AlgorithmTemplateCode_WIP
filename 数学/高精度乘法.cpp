#include<bits/stdc++.h>
using namespace std;

// a * b
// 数组逆序存储数位
// 从 1 ~ n 分别是低位到高位

// 高精度乘法, 用数组存储数位, 手动模拟乘法运算
// 对于最终结果, 数位长度不超过a, b数位之和
const int MAXN = 300;
int a[MAXN + 1];
int b[MAXN + 1];
int res[2 * MAXN + 1];

void multiply(string s1, string s2) {
    int n = s1.size();
    int m = s2.size();
    for (int i = 1;i <= n;i++) {
        a[i] = s1[n - i] - '0';
    }
    for (int i = 1;i <= m;i++) {
        b[i] = s2[m - i] - '0';
    }
    fill(res, res + n + m + 1, 0);
    for (int i = 1;i <= n;i++) {
        for (int j = 1;j <= m;j++) {
            res[j + i - 1] += a[i] * b[j];
            if (res[j + i - 1] >= 10) {
                res[j + i] += res[j + i - 1] / 10;
                res[j + i - 1] %= 10;
            }
        }
    }
    bool isZero = true;
    int idx = n + m;
    for (int i = idx;i >= 0;i--) {
        if (res[i] != 0) {
            idx = i;
            isZero = false;
            break;
        }
    }
    if (isZero) {
        cout << 0 << '\n';
        return;
    }
    for (int i = idx;i >= 1;i--) {
        cout << res[i];
    }
    cout << '\n';
}
