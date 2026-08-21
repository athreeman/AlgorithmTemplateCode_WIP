#include<bits/stdc++.h>
using namespace std;
using ll = long long;
//容斥原理

//核心:
//+C(k,1)的和-C(k,2)的交集+C(k,3)的和-C(k,4)的交集+......
//奇数个+,偶数个-
//例题:https://codeforces.com/problemset/problem/803/F
//例题:https://www.luogu.com.cn/problem/P1450



class Inclusion_Exclusion {//容斥原理
private:
    const static int mod = 1e9 + 7;
    int cnt[100001];
    ll dp[100001];
    //dp[i]表示以i为最小公约数的子序列个数
    ll pow2[100001];
    void initial() {
        pow2[0] = 1;
        for (ll i = 1;i <= 100000;i++) {
            cnt[i] = 0;
            pow2[i] = pow2[i - 1] * 2LL % mod;
        }
    }

    ll dp02[100001];

public:
    void solve01() {
        initial();
        int n;
        cin >> n;
        ll max_val = 1;
        for (int i = 1;i <= n;i++) {
            int x;
            cin >> x;
            cnt[x]++;
            max_val = max(max_val, (ll)x);
        }
        //数组中,包含i本身的gcd=i的子序列,需要满足所有其他元素都是i的倍数
        for (int i = max_val;i >= 1;i--) {
            ll count = 0;
            for (int j = i;j <= max_val;j += i) {
                count += cnt[j];
            }
            dp[i] = (pow2[count] - 1 + mod) % mod;
            for (int j = i + i;j <= max_val;j += i) {
                dp[i] = (dp[i] - dp[j] + mod) % mod;
            }
        }
        cout << dp[1] << '\n';
    }

    void solve02() {
        //假定无个数限制,dp[s]完全背包表示1~i凑到s元的所有方案数
        //dp[s-(di+1)*ci]表示第i枚硬币花费超出di个的方案数
        //根据容斥原理求1~4都花费超出的方案数
        ll value[4];
        ll cnt[4];
        int n;
        cin >> value[0] >> value[1] >> value[2] >> value[3] >> n;
        dp[0] = 1;
        //完全背包问题
        for (int i = 0;i <= 3;i++) {
            for (int j = value[i];j <= 100000;j++) {
                dp[j] += dp[j - value[i]];
            }
        }
        for (int i = 0;i < n;i++) {
            ll s;
            for (int i = 0;i < 4;i++) {
                cin >> cnt[i];
            }
            cin >> s;
            //0001->1111(1->15)
            //用位状态表示第1~i枚硬币的违规状态的方案数
            ll illegal = 0;//非法
            for (int i = 1;i <= ((1 << 4) - 1);i++) {
                ll tmp = s;//总值
                int flg = 0;//标记加/减
                for (int j = 0;j <= 3;j++) {
                    //查看各位的状态
                    if ((i >> j) & 1) {
                        tmp -= value[j] * (cnt[j] + 1);
                        flg ^= 1;
                    }
                }
                if (tmp >= 0) {
                    illegal += flg ? dp[tmp] : -dp[tmp];
                }
            }
            cout << dp[s] - illegal << '\n';
        }
    }

};
