#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 5e3;
array<int, 4>infox[2 * MAXN + 5];
array<int, 4>infoy[2 * MAXN + 5];
int fx[2 * MAXN + 5];
int fy[2 * MAXN + 5];
int n, m, cntx, cnty;

struct {
    ll len;
    ll cover;
    int cnt;
}node[8 * MAXN + 5];

void up(int i, int l, int r) {
    if (l == r) {
        node[i].cover = node[i].cnt > 0 ? node[i].len : 0;
    }
    else {
        node[i].cover = node[i].cnt > 0 ? node[i].len : node[i << 1].cover + node[i << 1 | 1].cover;
    }
}

void build(int l, int r, int i, int* f) {
    node[i].len = f[r + 1] - f[l];
    node[i].cover = 0;
    node[i].cnt = 0;
    if (l != r) {
        int mid = (l + r) >> 1;
        build(l, mid, i << 1, f);
        build(mid + 1, r, i << 1 | 1, f);
        up(i, l, r);
    }
}

void add(int jobl, int jobr, int jobv, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        node[i].cnt += jobv;
    }
    else {
        int mid = (l + r) >> 1;
        if (jobl <= mid) {
            add(jobl, jobr, jobv, l, mid, i << 1);
        }
        if (jobr > mid) {
            add(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        }
    }
    up(i, l, r);
}

void Disc() {
    sort(fy + 1, fy + m + 1);
    fy[0] = -1;
    int k = m;m = 0;
    for (int i = 1;i <= k;i++) {
        if (fy[i] != fy[m]) {
            fy[++m] = fy[i];
        }
    }
    fy[m + 1] = fy[m];

    sort(fx + 1, fx + n + 1);
    fx[0] = -1;
    k = n;n = 0;
    for (int i = 1;i <= k;i++) {
        if (fx[i] != fx[n]) {
            fx[++n] = fx[i];
        }
    }
    fx[n + 1] = fx[n];
}

int rankk(int* disc, int R, int v) {
    int l = 1, r = R;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (disc[mid] == v) {
            return mid;
        }
        else if (disc[mid] > v) {
            r = mid - 1;
        }
        else {
            l = mid + 1;
        }
    }
    return l;
}

bool cmp(array<int, 4>a, array<int, 4>b) {
    if (a[0] == b[0]) {
        return a[3] > b[3];
    }
    return a[0] < b[0];
}
void solve() {
    int N;
    cin >> N;
    m = n = cntx = cnty = 0;
    for (int i = 1;i <= N;i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1 += 1e5, x2 += 1e5, y1 += 1e5, y2 += 1e5;
        infoy[++cnty] = { x1,y1,y2,1 };
        infoy[++cnty] = { x2,y1,y2,-1 };
        fy[++m] = y1;
        fy[++m] = y2;

        infox[++cntx] = { y1,x1,x2,1 };
        infox[++cntx] = { y2,x1,x2,-1 };
        fx[++n] = x1;
        fx[++n] = x2;

    }
    sort(infox + 1, infox + cntx + 1, cmp);
    sort(infoy + 1, infoy + cnty + 1, cmp);
    Disc();
    ll ans = 0;
    //处理y
    build(1, m, 1, fy);
    for (int i = 1, pre = 0;i <= cnty;i++) {
        pre = node[1].cover;
        add(rankk(fy, m, infoy[i][1]), rankk(fy, m, infoy[i][2]) - 1, infoy[i][3], 1, m, 1);
        ans += llabs(node[1].cover - pre);
    }
    //处理x
    build(1, n, 1, fx);
    for (int i = 1, pre = 0;i <= cntx;i++) {
        pre = node[1].cover;
        add(rankk(fx, n, infox[i][1]), rankk(fx, n, infox[i][2]) - 1, infox[i][3], 1, n, 1);
        ans += llabs(node[1].cover - pre);
    }
    cout << ans << '\n';
}
