#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 1e18;
const int MAXN = 5e5;
ll a[MAXN + 1];
struct {
    ll sum, max, cnt, cmax;
    ll maxAdd, otherAdd;
    ll maxHistory, maxAddTop;
    ll otherAddTop;
    // sum           总和
    // max           最大值
    // cnt           最大值个数
    // cmax          次最大值
    // maxHistory    历史最大值
    // 以下属于懒信息标记内容：
    // maxAdd        最大值增幅(当前)
    // otherAdd      其他值增幅(当前)
    // maxAddTop     最大值的历史最大增幅
    // otherAddTop   其他值的历史最大增幅
}node[4 * MAXN + 1];

void up(int i) {
    int l = i << 1;
    int r = i << 1 | 1;
    node[i].sum = node[l].sum + node[r].sum;
    node[i].max = max(node[l].max, node[r].max);
    node[i].maxHistory = max(node[l].maxHistory, node[r].maxHistory);
    if (node[l].max > node[r].max) {
        node[i].cnt = node[l].cnt;
        node[i].cmax = max(node[l].cmax, node[r].max);
    }
    else if (node[l].max < node[r].max) {
        node[i].cnt = node[r].cnt;
        node[i].cmax = max(node[r].cmax, node[l].max);
    }
    else {
        node[i].cnt = node[l].cnt + node[r].cnt;
        node[i].cmax = max(node[l].cmax, node[r].cmax);
    }
}
//传参：节点，大小，最大值增幅，其他值增幅，最大值历史最大增幅，其他值历史最大增幅
void lazy(int i, int n, ll maxAddv, ll otherAddv, ll maxUpv, ll otherUpv) {
    node[i].maxHistory = max(node[i].maxHistory, node[i].max + maxUpv);
    node[i].maxAddTop = max(node[i].maxAddTop, node[i].maxAdd + maxUpv);
    node[i].otherAddTop = max(node[i].otherAddTop, node[i].otherAdd + otherUpv);
    node[i].sum += maxAddv * node[i].cnt + otherAddv * (n - node[i].cnt);
    node[i].max += maxAddv;
    node[i].cmax += (node[i].cmax == -INF) ? 0 : otherAddv;
    node[i].maxAdd += maxAddv;
    node[i].otherAdd += otherAddv;
}
void down(int i, int ln, int rn) {
    int l = i << 1;
    int r = i << 1 | 1;
    ll tmp = max(node[l].max, node[r].max);//父节点最大子来自子节点,父节点可能已经发生改变
    if (node[l].max == tmp) {
        lazy(l, ln, node[i].maxAdd, node[i].otherAdd, node[i].maxAddTop, node[i].otherAddTop);
    }
    else {
        lazy(l, ln, node[i].otherAdd, node[i].otherAdd, node[i].otherAddTop, node[i].otherAddTop);
    }
    if (node[r].max == tmp) {
        lazy(r, rn, node[i].maxAdd, node[i].otherAdd, node[i].maxAddTop, node[i].otherAddTop);
    }
    else {
        lazy(r, rn, node[i].otherAdd, node[i].otherAdd, node[i].otherAddTop, node[i].otherAddTop);
    }
    node[i].maxAdd = node[i].otherAdd = node[i].maxAddTop = node[i].otherAddTop = 0;
}
void build(int l, int r, int i) {
    if (l == r) {
        node[i].sum = node[i].max = node[i].maxHistory = a[l];
        node[i].cmax = -INF;
        node[i].cnt = 1;
    }
    else {
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
        up(i);
    }
    //懒信息
    node[i].maxAdd = node[i].otherAdd = node[i].maxAddTop = node[i].otherAddTop = 0;
}
//区间增加
void add(int jobl, int jobr, ll jobv, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        lazy(i, r - l + 1, jobv, jobv, jobv, jobv);
    }
    else {
        int mid = (l + r) >> 1;
        down(i, mid - l + 1, r - mid);
        if (jobl <= mid) {
            add(jobl, jobr, jobv, l, mid, i << 1);
        }
        if (jobr > mid) {
            add(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        }
        up(i);
    }
}
//设置区间最大值
void setMin(int jobl, int jobr, ll jobv, int l, int r, int i) {
    if (jobv >= node[i].max) {
        return;
    }
    if (jobl <= l && r <= jobr && node[i].cmax < jobv) {
        lazy(i, r - l + 1, jobv - node[i].max, 0, jobv - node[i].max, 0);
    }
    else {
        int mid = (l + r) >> 1;
        down(i, mid - l + 1, r - mid);
        if (jobl <= mid) {
            setMin(jobl, jobr, jobv, l, mid, i << 1);
        }
        if (jobr > mid) {
            setMin(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        }
        up(i);
    }
}
//查询区间和
ll querySum(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return node[i].sum;
    }
    else {
        int mid = (l + r) >> 1;
        down(i, mid - l + 1, r - mid);
        ll ans = 0;
        if (jobl <= mid) {
            ans += querySum(jobl, jobr, l, mid, i << 1);
        }
        if (jobr > mid) {
            ans += querySum(jobl, jobr, mid + 1, r, i << 1 | 1);
        }
        return ans;
    }
}
//查询区间最大值
ll queryMax(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return node[i].max;
    }
    else {
        int mid = (l + r) >> 1;
        down(i, mid - l + 1, r - mid);
        ll ans = -INF;
        if (jobl <= mid) {
            ans = max(ans, queryMax(jobl, jobr, l, mid, i << 1));
        }
        if (jobr > mid) {
            ans = max(ans, queryMax(jobl, jobr, mid + 1, r, i << 1 | 1));
        }
        return ans;
    }
}
//查询区间历史最大值
ll queryHistoryMax(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return node[i].maxHistory;
    }
    else {
        int mid = (l + r) >> 1;
        down(i, mid - l + 1, r - mid);
        ll ans = -INF;
        if (jobl <= mid) {
            ans = max(ans, queryHistoryMax(jobl, jobr, l, mid, i << 1));
        }
        if (jobr > mid) {
            ans = max(ans, queryHistoryMax(jobl, jobr, mid + 1, r, i << 1 | 1));
        }
        return ans;
    }
}
