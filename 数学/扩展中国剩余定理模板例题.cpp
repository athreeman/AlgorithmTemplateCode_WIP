#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ill = __int128_t;
const int MAXN = 1e5;

// https://www.luogu.com.cn/problem/P4774
// 该题核心在于对中国剩余定理过程中a, b, c求解的定制

ll hp[MAXN + 1];// 生命
ll recovery[MAXN + 1];// 恢复
ll attack[MAXN + 1];// 用于攻击第i条龙的剑的伤害
ll reward[MAXN + 1];// 奖励
ll maxCnt = 0;

ll exgcd(ll hp, ll attack, ll& x, ll& y) {
    if (attack == 0) {
        x = 1;
        y = 0;
        return hp;
    }
    else {
        ll g = exgcd(attack, hp % attack, x, y);
        ll tmp = y;
        y = x - y * (hp / attack);
        x = tmp;
        return g;
    }
}

ll excrt(int n) {
    // attack[i] * ans ≡ hp[i](% recovery[i])
    // ans = lcm * x + tail
    // attack[i] * ans = lcm * x * attack[i] + tail * attack[i]
    // attack[i] * ans = recovery[i] * y + hp[i]
    // lcm * attack[i] * x + recovery[i] * y = hp[i] - tail * attack[i]
    ll tail = 0, lcm = 1, tmp, a, b, c, x0;
    for (int i = 1;i <= n;i++) {
        a = ill(lcm * attack[i]) % recovery[i];
        b = recovery[i];
        c = ((hp[i] - tail * attack[i]) % b + b) % b;
        ll x, y;
        ll d = exgcd(a, b, x, y);
        if (c % d != 0) {
            return -1;//无解
        }
        x0 = ((ill)x * (ill)(c / d) % ill(b / d) + ill(b / d)) % ill(b / d);
        tmp = ill(lcm) * ill(b / d);// tmp此时就是新的lcm1
        tail = ill((ill)tail + ill(x0) * ill(lcm) % ill(tmp)) % ill(tmp);
        lcm = tmp;
    }
    // ans = ? * lcm + tail
    if (tail >= maxCnt) {
        return tail;
    }
    return (maxCnt - tail + lcm - 1) / lcm * lcm + tail;
}


void solve() {
    int n, m;
    cin >> n >> m;
    maxCnt = 0;
    for (int i = 1;i <= n;i++) {
        cin >> hp[i];
    }
    for (int i = 1;i <= n;i++) {
        cin >> recovery[i];
    }
    for (int i = 1;i <= n;i++) {
        cin >> reward[i];
    }
    multiset<ll>st;
    for (int i = 1;i <= m;i++) {
        ll x;
        cin >> x;
        st.insert(x);
    }
    for (int i = 1;i <= n;i++) {
        if (!st.size()) {
            cout << -1 << '\n';
            return;
        }
        auto it = st.lower_bound(hp[i]);
        if (it == st.end()) {// 全都小于a[i]
            attack[i] = *prev(st.end());
            st.erase(prev(st.end()));
        }
        else {
            if (it == st.begin()) {
                // 全部>=hp[i]
                attack[i] = *it;
                st.erase(it);
            }
            else {
                if (*it > hp[i]) {
                    it--;
                }
                attack[i] = *it;
                st.erase(it);
            }
        }
        st.insert(reward[i]);
        maxCnt = max(maxCnt, ll(hp[i] + attack[i] - 1) / attack[i]);
        hp[i] %= recovery[i];
    }
    cout << excrt(n) << '\n';

}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
