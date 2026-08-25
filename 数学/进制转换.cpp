#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const string DIGIT =
"0123456789"
"abcdefghijklmnopqrstuvwxyz"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";

//该DIGIT字符最多支持94进制的转换
//如果仅限数字和字母最多支持62进制的转换


//把x转换为base进制
string toBase(ll x, int base) {
    if (x == 0) {
        return "0";
    }
    string ans;
    while (x) {
        ans += DIGIT[x % base];
        x /= base;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

ll pw(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) {
            res = res * a;
        }
        a = a * a;
        b >>= 1;
    }
    return res;
}

//获取x在base进制下的第i位
ll getDigit(ll x, int base, int i) {
    return x / pw(base, i) % base;
}

//basej进制下的第i位设置为v
ll setDigit(ll s, int base, int i, int v) {
    ll p = pw(base, i);
    ll old = s / p % base;
    return s + (v - old) * p;
}
