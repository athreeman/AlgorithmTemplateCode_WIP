#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 1e5;
array<int, 4>info[2 * MAXN + 5];
int fy[2 * MAXN + 5];
int m, cnt;

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

void build(int l, int r, int i) {
    node[i].len = fy[r + 1] - fy[l];
    node[i].cover = 0;
    node[i].cnt = 0;
    if (l != r) {
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
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
}

int rankk(int* disc, int n, int v) {
    int l = 1, r = n;
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
    if (a[0] == b[0])return a[3] > b[3];//处理坐标相同问题
    return a[0] < b[0];
}
void solve() {
    int n;
    cin >> n;
    m = cnt = 0;
    for (int i = 1;i <= n;i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        info[++cnt] = { x1,y1,y2,1 };
        info[++cnt] = { x2,y1,y2,-1 };
        fy[++m] = y1;
        fy[++m] = y2;
    }
    sort(info + 1, info + cnt + 1, cmp);
    Disc();
    ll ans = 0;
    build(1, m, 1);
    for (int i = 1;i <= cnt;i++) {
        if (i > 1) {
            ans += ll(info[i][0] - info[i - 1][0]) * ll(node[1].cover);
        }
        add(rankk(fy, m, info[i][1]), rankk(fy, m, info[i][2]) - 1, info[i][3], 1, m, 1);
    }
    cout << ans << '\n';
}
