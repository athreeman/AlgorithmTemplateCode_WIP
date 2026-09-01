#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int MAXN = 1e7;
ll minFactor[MAXN + 10];// minFactor[i]表示i的最小质因子(线性欧拉筛维护最小质因子表)
bitset<MAXN + 1>isPrime;//标记质数
ll Primes[MAXN + 1];
void getPrimes_Linear(ll n) {
    isPrime.set();
    isPrime[0] = isPrime[1] = 0;
    Primes[0] = 0;
    for (ll i = 2;i <= n;i++) {
        if (isPrime[i]) Primes[++Primes[0]] = i;
        for (ll j = 1, v;j <= Primes[0];j++) {
            v = Primes[j];
            if (v * i > n)break;
            isPrime[i * v] = 0;
            minFactor[i * v] = v;// 获取最小质因子,必须放在break前
            if (i % v == 0)break;
        }
    }
}
