#include<bits/stdc++.h>
using namespace std;
//树状数组,树状数组的下标必须以1为基底
//功能:主要用于维护可差分信息，如累加和、乘积...
//1、一维数组：单点/范围增加，单点/范围查询
//2、二维数组：单点/范围增加，范围查询
//一维树状数组
//一维数组：单点增加+范围查询

class Single_AND_Range {
private:
    static const int MAXN = 2e5;
    static int tree[MAXN + 1];
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

    //普通求和[1...i]
    int sum(int i) {
        int ans = 0;
        while (i > 0) {
            ans += tree[i];
            i -= lowbit(i);
        }
        return ans;
    }
    //区间查询
    int queryRange(int l, int r) {
        return sumSingle(r) - sumSingle(l - 1);
    }
};

//一维树状数组：范围增加+单点查询
class Range_AND_Single {
    static const int MAXN = 2e5;
    static int treeDiff[MAXN + 1];//范围增加依赖于一维差分数组

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

//一维树状数组：范围增加+范围查询
class Range_AND_Range {
    static const int MAXN = 2e5;
    static int tree1[MAXN + 1];//一维差分数组
    static int tree2[MAXN + 1];//tree2[i]=(i-1)*d[i],辅助数组
    int lowbit(int x) {
        return x & -x;
    }
    //单点增加
    void add(int n, int* tree, int i, int val) {
        while (i <= n) {
            tree[i] += val;
            i += lowbit(i);
        }
    }
    //树tree区间和
    int sum(int* tree, int i) {
        //1...i
        int ans = 0;
        while (i > 0) {
            ans += tree[i];
            i -= lowbit(i);
        }
        return ans;
    }
    //区间增加
    void addRange(int n, int l, int r, int v) {
        add(n, tree1, l, v);
        add(n, tree1, r + 1, -v);
        add(n, tree2, l, (l - 1) * v);
        add(n, tree2, r + 1, -r * v);
    }
    //求原数组区间和
    int queryRange(int l, int r) {
        return sum(tree1, r) * r - sum(tree2, r) - sum(tree1, l - 1) * (l - 1) + sum(tree2, l - 1);
    }
};


class TwoSingleAndRange {
    //单点增加+范围查询
    static const int MAXN = 2000;
    static int tree[MAXN + 1][MAXN + 1];

    int lowbit(int x) {
        return x & -x;
    }
    //(1,1)->(x,y)范围增加
    void add(int x, int y, int v, int n, int m) {
        for (int i = x;i <= n;i += lowbit(i)) {
            for (int j = y;j <= m;j += lowbit(j)) {
                tree[i][j] += v;
            }
        }
    }
    //(1,1)->(x,y)范围求和
    int sum(int x, int y) {
        int ans = 0;
        for (int i = x;i > 0;i -= lowbit(i)) {
            for (int j = y;j > 0;j -= lowbit(j)) {
                ans += tree[i][j];
            }
        }
        return ans;
    }
    //范围求和(l,r)->(x,y)
    int queryRange(int l, int r, int x, int y) {
        return sum(x, y) - sum(x, r - 1) - sum(l - 1, y) + sum(l - 1, r - 1);
    }
};


class TwoRangeAndRange {
    //范围增加+范围查询
    static const int MAXN = 2000;
    //二维差分数组,tree维护四个信息
    //diff[i][j]
    static int tree1[MAXN + 1][MAXN + 1];
    //diff[i][j]*i
    static int tree2[MAXN + 1][MAXN + 1];
    //diff[i][j]*j
    static int tree3[MAXN + 1][MAXN + 1];
    //diff[i][j]*i*j
    static int tree4[MAXN + 1][MAXN + 1];

    int lowbit(int x) {
        return x & -x;
    }

    //位置(x,y)单点增加
    void addSingle(int x, int y, int v, int n, int m) {
        int v1 = v;
        int v2 = v * x;
        int v3 = v * y;
        int v4 = x * y * v;
        for (int i = x;i <= n;i += lowbit(i)) {
            for (int j = y;j <= m;j += lowbit(j)) {
                tree1[i][j] += v1;
                tree2[i][j] += v2;
                tree3[i][j] += v3;
                tree4[i][j] += v4;
            }
        }
    }
    //求和(1,1)->(x,y)
    int sum(int x, int y) {
        int ans = 0;
        for (int i = x;i > 0;i -= lowbit(i)) {
            for (int j = y;j > 0;j -= lowbit(j)) {
                //四个信息 
                ans += (x + 1) * (y + 1) * tree1[i][j]
                    - (y + 1) * tree2[i][j]
                    - (x + 1) * tree3[i][j]
                    + tree4[i][j];
            }
        }
        return ans;
    }
    //范围增加
    void addRange(int a, int b, int c, int d, int v, int n, int m) {
        addSingle(a, b, v, n, m);
        addSingle(a, d + 1, -v, n, m);
        addSingle(c + 1, b, -v, n, m);
        addSingle(c + 1, d + 1, v, n, m);
    }
    //范围查询
    int queryRange(int a, int b, int c, int d, int n, int m) {
        int ans = 0;
        ans = sum(c, d) - sum(a - 1, d) - sum(c, b - 1) + sum(a - 1, b - 1);
        return ans;
    }

};
