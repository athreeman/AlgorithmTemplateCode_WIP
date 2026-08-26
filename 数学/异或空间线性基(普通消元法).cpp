#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int MAXN = 2e5;
const int bit = 60;
ll basis[bit + 1];
ll a[MAXN + 1];
bool zero = false;

// 基：可以表示原空间所有元素的一组极小线性无关组(不唯一)
// 普通消元法或高斯消元法

// 普通消元法求解异或线性基
// 时间复杂度O(nlogV), V是最大值
// 普通消元法

// 若线性基大小 = m，则原始异或和共有2 ^ m - 1种
// 最大异或和：从高位开始贪心，异或和可以变大则异或，否则不异或
// 第k小异或和，需要用高斯消元法

// 若插入失败，意味着被其他线性基消除，原始异或和存在0
bool insert(ll x) {
    for (int i = bit;i >= 0;i--) {
        if ((x >> i) & 1) {
            if (basis[i] == 0) {
                basis[i] = x;
                return true;
            }
            x ^= basis[i];
        }
    }
    return false;
}

void buildBasis(ll* arr, int n) {
    zero = false;
    fill(basis, basis + bit + 1, 0);
    for (int i = 1;i <= n;i++) {
        if (!insert(arr[i])) {
            zero = true;
        }
    }
}

// 最大异或和
ll GetXorMax() {
    ll res = 0;
    for (int i = bit;i >= 0;i--) {
        res = max(res, res ^ basis[i]);
    }
    return res;
}
