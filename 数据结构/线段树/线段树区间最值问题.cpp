#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 1e18;
const int MAXN = 1e6;
ll a[MAXN + 1];
ll sum[4 * MAXN + 1];
ll maxval[4 * MAXN + 1];
ll cnt[4 * MAXN + 1];
ll cmaxval[4 * MAXN + 1];

void up(int i) {
    int l = 2 * i, r = l + 1;
    sum[i] = sum[l] + sum[r];
    maxval[i] = max(maxval[l], maxval[r]);
    if (maxval[l] > maxval[r]) {
        cmaxval[i] = max(maxval[r], cmaxval[l]);
        cnt[i] = cnt[l];
    }
    else if (maxval[r] > maxval[l]) {
        cmaxval[i] = max(maxval[l], cmaxval[r]);
        cnt[i] = cnt[r];
    }
    else {
        cmaxval[i] = max(cmaxval[l], cmaxval[r]);
        cnt[i] = cnt[l] + cnt[r];
    }
}
void build(int l, int r, int i) {
    if (l == r) {
        maxval[i] = a[l];
        cmaxval[i] = -INF;
        sum[i] = a[l];
        cnt[i] = 1;
    }
    else {
        int mid = (l + r) >> 1;
        build(l, mid, 2 * i);
        build(mid + 1, r, 2 * i + 1);
        up(i);
    }
}
void lazy(int i, ll jobv) {
    if (jobv < maxval[i]) {
        sum[i] -= (maxval[i] - jobv) * cnt[i];
        maxval[i] = jobv;
    }
}
void down(int i) {
    int l = 2 * i, r = l + 1;
    lazy(l, maxval[i]);
    lazy(r, maxval[i]);
}
void setMin(int jobl, int jobr, ll jobv, int l, int r, int i) {
    if (jobv >= maxval[i]) {
        return;
    }
    if (jobl <= l && r <= jobr && cmaxval[i] < jobv) {
        //cmax<jobv<=max,懒标记
        lazy(i, jobv);
    }
    else {
        //1.任务没有全包
        //2.jobv <= cmax 不得不下传
        int mid = (l + r) >> 1;
        down(i);
        if (jobl <= mid) {
            setMin(jobl, jobr, jobv, l, mid, 2 * i);
        }
        if (jobr > mid) {
            setMin(jobl, jobr, jobv, mid + 1, r, 2 * i + 1);
        }
        up(i);
    }
}
ll querySum(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return sum[i];
    }
    int mid = (l + r) >> 1;
    down(i);
    ll ans = 0;
    if (jobl <= mid) {
        ans += querySum(jobl, jobr, l, mid, 2 * i);
    }
    if (jobr > mid) {
        ans += querySum(jobl, jobr, mid + 1, r, 2 * i + 1);
    }
    up(i);
    return ans;
}

ll queryMax(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return maxval[i];
    }
    int mid = (l + r) >> 1;
    down(i);
    ll ans = -INF;
    if (jobl <= mid) {
        ans = max(ans, queryMax(jobl, jobr, l, mid, 2 * i));
    }
    if (jobr > mid) {
        ans = max(ans, queryMax(jobl, jobr, mid + 1, r, 2 * i + 1));
    }
    up(i);
    return ans;
}
