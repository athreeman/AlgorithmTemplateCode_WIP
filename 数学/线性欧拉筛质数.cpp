#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int MAXN = 1e7;
bitset<2 * MAXN + 1>isPrime;//标记质数
vector<ll>Primes;//存储质数

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