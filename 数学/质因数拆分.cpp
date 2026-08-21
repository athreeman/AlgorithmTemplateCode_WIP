#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int MAXN = 1e7;
bitset<2 * MAXN + 1>isPrime;//标记质数
vector<ll>Primes;//存储质数
vector<ll>factors[2 * MAXN + 1];//facotrs[i]存储i的质因数

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