#include<bits/stdc++.h>
using namespace std;
using ll = long long;
#define ill __int128_t
const int MAXN = 1e7;
bitset<2 * MAXN + 1>isPrime;//标记质数
vector<ll>Primes;//存储质数
vector<ll>factors[2 * MAXN + 1];//facotrs[i]存储i的质因数

bool is_Prime(ll x) {
    //判断x是否为质数
    //复杂度O(sqrt(n))
    if (x <= 1) {
        return false;
    }
    else if (x == 2) {
        return true;
    }
    else if (x % 2 == 0) {
        return false;
    }
    else {
        for (ll r = 3;r * r <= x;r += 2) {
            if (x % r == 0) {
                return false;
            }
        }
    }
    return true;
}

//快速幂
ll pw(ll a, ll b, ll mod) {
    ll res = 1;
    while (b) {
        if (b & 1) {
            res = ill(res) * ill(a) % mod;
        }
        a = ill(a) * ill(a) % mod;
        b >>= 1;
    }
    return res;
}


//Miller_Rabin算法测质数
//辅助验证函数
bool witness(ll a, ll n) {
    ll u = n - 1;
    int t = 0;
    while ((u & 1) == 0) {
        t++;
        u >>= 1;
    }
    ll x1 = pw(a, u, n), x2;
    for (int i = 1;i <= t;i++) {
        x2 = pw(x1, 2, n);
        if (x2 == 1 && x1 != 1 && x1 != n - 1) {
            return true;
        }
        x1 = x2;
    }
    if (x1 != 1) {
        return true;
    }
    return false;
}
//MR_p测试数组
ll MR_p[] = { 2,3,5,7,11,13,17,19,23,29,31,37 };
bool Miller_Rabin(ll n) {
    //模板例题：https://www.luogu.com.cn/problem/U148828
    //判断x是否为质数
    if (n <= 2) {
        return n == 2;
    }
    if ((n & 1) == 0) {
        return false;
    }
    for (ll p : MR_p) {
        if (p >= n)break;
        if (witness(p, n)) {
            return false;
        }
    }
    return true;
}

void getPrimes_Eratosthenes(ll n) {
    //埃氏筛
    //复杂度O(n*log2(log2n))
    //获取1~n的所有质数
    isPrime.set();
    isPrime[0] = isPrime[1] = 0;
    for (ll i = 2;i <= n;i++) {
        if (isPrime[i]) {
            Primes.push_back(i);
            for (ll j = i * i;j <= n;j += i) {
                isPrime[j] = 0;
            }
        }
    }
}

void getPrimes_Linear(ll n) {
    //欧拉线性筛
    //复杂度O(n)
    //获取1~n的所有质数
    isPrime.set();
    isPrime[0] = isPrime[1] = 0;
    for (ll i = 2;i <= n;i++) {
        if (isPrime[i])Primes.push_back(i);
        for (ll val : Primes) {
            if (val * i > n)break;
            isPrime[i * val] = 0;
            if (i % val == 0)break;
        }
    }
}

void getFactors(ll n) {
    //复杂度O(sqrt(n)/log2(n))
    //分解n的质因数
    ll val = n;
    if (isPrime[n] == 1) {
        factors[n].push_back(n);
        return;
    }
    for (ll p : Primes) {
        if (val == 1)break;
        if ((ll)p * p > (ll)val)break;
        if (val % p != 0)continue;
        factors[n].push_back(p);
        while (val % p == 0)val /= p;
    }
    if (val > 1)factors[n].push_back(val);
}

//获取1~n范围的所有数的质因数
void GetFactors(ll n) {
    for (int p : Primes) {
        for (int i = p;i <= n;i += p) {
            factors[i].push_back(p);
        }
    }
}