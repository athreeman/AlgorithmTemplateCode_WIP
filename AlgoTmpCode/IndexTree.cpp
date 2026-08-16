#include<bits/stdc++.h>
using namespace std;
//树状数组
//功能:主要用于维护可差分信息，如累加和、乘积...
//1、一维数组：单点/范围增加，单点/范围查询
//2、二维数组：单点/范围增加，范围查询
//一维树状数组
//一维数组：单点增加+范围查询
class Single_AND_Range {
private:
    static const int MAXN = 2e5;
    int tree[MAXN + 1];
    //获取最低位1
    int lowbit(int x) {
        return x & -x;
    }
    //单点增加
    void addSingle(int n, int i, int val) {
        while (i <= n) {//n是右边界
            tree[i] += val;
            i += lowbit(i);
        }
    }

    //普通求和
    int sumSingle(int i) {
        int ans = 0;
        while (i > 0) {
            ans += tree[i];
            i -= lowbit(i);
        }
        return ans;
    }
    //区间查询
    int query(int l, int r) {
        return sumSingle(r) - sumSingle(l - 1);
    }
};
//一维树状数组：范围增加+单点查询
class Range_AND_Single {
    static const int MAXN = 2e5;
    int treeDiff[MAXN + 1];//范围增加依赖于一维差分数组
    //获取最低位1
    int lowbit(int x) {
        return x & -x;
    }
    //单点增加,基于差分数组
    void addSingle(int n, int i, int val) {
        while (i <= n) {//n是右边界
            treeDiff[i] += val;
            i += lowbit(i);
        }
    }
    //范围增加
    void addRange(int n, int l, int r, int val) {
        addSingle(n, l, val);
        addSingle(n, r + 1, -val);
    }
    //单点查询
    int querySingle(int i) {
        int ans = 0;
        while (i > 0) {
            ans += treeDiff[i];
            i -= lowbit(i);
        }
        return ans;
    }
};
