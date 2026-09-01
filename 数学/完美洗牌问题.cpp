#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// 完美洗牌问题：
// 给定区间[l...r], 长度偶数
// mid = (l + r) >> 1, 记[l, mid]为数组{ l1,l2,l3,... }
// 记[mid+1, r]为数组{ r1,r2,r3,... }
// 把[l, r]交换为{ r1,l1,r2,l2,r3,l3,.. }的形式

// 核心：
// 若i <= mid, go(i) = i + (i - l + r)
// 若i > mid, go(i) = i - (r - i + 1)
// 存在若干个下标的循环交换
// 当长度k = 3 ^ k - 1时
// 所有循环起点是{ 3 ^ 0,3 ^ 1,3 ^ 2,...,3 ^ (k - 1) }
// 通过三进制拆分的方法, 解决该问题

// 使用辅助数组help,可以在时间复杂度O(n),空间O(n)解决
// 使用三进制拆分,可以在时间O(n),空间O(1)解决

const int MAXN = 2e5;
int a[MAXN + 1];
int b[MAXN + 1];
int start[21];
ll split[21];//三进制拆分数组
// 3的20次幂是3486784401, 足够大了

int prepare(int n) {
    int siz = 0;
    for (ll s = 1, p = 2;p <= n;s *= 3, p = s * 3 - 1) {
        start[++siz] = s;// 起点是3的幂
        split[siz] = p;// 分割点是3的幂-1
    }
    return siz;
}

int go(int l, int r, int i) {
    int mid = (l + r) >> 1;
    if (i <= mid)return i + (i - l + 1);
    return i - (r - i + 1);
}

// 翻转区间[l, r]
void rev(int l, int r, int* arr) {
    while (l < r) {
        swap(arr[l], arr[r]);
        l++, r--;
    }
}

//[l, k], [k + 1, r]交换
void rotate(int l, int k, int r, int* arr) {
    rev(l, k, arr);
    rev(k + 1, r, arr);
    rev(l, r, arr);
}

void circle(int l, int r, int i, int* arr) {
    for (int j = i;j >= 1;j--) {
        int cur = l + start[j] - 1, next;
        next = go(l, r, cur);
        int curv = arr[cur];
        while (next != l + start[j] - 1) {
            int tmp = arr[next];
            arr[next] = curv;
            curv = tmp;
            cur = next, next = go(l, r, next);
        }
        arr[next] = curv;
    }
}

void shuffle(int l, int r, int* arr) {
    int n = r - l + 1;
    int siz = prepare(n);
    for (int i = siz, mid;n > 0;) {
        if (split[i] <= n) {
            mid = (l + r) >> 1;
            // 处理长度为split[i]的段
            // 分别由左侧和右侧的部分拼接而成
            rotate(l + split[i] / 2, mid, mid + split[i] / 2, arr);
            circle(l, l + split[i] - 1, i, arr);
            l += split[i];
            n -= split[i];
        }
        else {
            i--;
        }
    }
}

void shuffleHelp(int l, int r, int* arr) {
    int n = r - l + 1;
    vector<int>help(n + 1, 0);
    int mid = (l + r) >> 1;
    for (int i = 1, j = mid + 1;j <= r;i += 2, j++) {
        help[i] = arr[j];
    }
    for (int i = 2, j = l;j <= mid;i += 2, j++) {
        help[i] = arr[j];
    }
    for (int i = 1, j = l;j <= r;j++, i++) {
        arr[j] = help[i];
    }
}
