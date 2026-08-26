#include<bits/stdc++.h>
using namespace std;
using ld = long double;
const ld eps = 1e-7;
array<int, 2> cost[501];
ld a[501][501];
int basis[501];

bool insert(int i, int m) {
    for (int j = 1;j <= m;j++) {
        if (fabsl(a[i][j]) >= eps) {
            if (basis[j] == 0) {
                basis[j] = i;
                return true;
            }
            ld rate = a[i][j] / a[basis[j]][j];
            for (int k = j;k <= m;k++) {
                a[i][k] -= rate * a[basis[j]][k];
            }
        }
    }
    return false;
}

bool cmp(array<int, 2>a, array<int, 2>b) {
    return a[0] < b[0];
}

void solve() {
    cout << fixed << setprecision(12);
    int n, m;
    cin >> n >> m;
    for (int i = 1;i <= n;i++) {
        for (int j = 1;j <= m;j++) {
            cin >> a[i][j];
        }
    }
    for (int i = 1;i <= n;i++) {
        cin >> cost[i][0];
        cost[i][1] = i;
    }
    sort(cost + 1, cost + n + 1, cmp);
    int cnt = 0;
    int ans = 0;
    for (int i = 1;i <= n;i++) {
        if (insert(cost[i][1], m)) {
            cnt++;
            ans += cost[i][0];
        }
    }
    cout << cnt << ' ' << ans << '\n';
}
