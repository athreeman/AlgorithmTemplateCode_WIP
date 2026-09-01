#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int MAXN = 1e7;
bitset<MAXN + 1>isPrime;//标记质数
ll Primes[MAXN + 1];
ll minFactor[MAXN + 1];
void getPrimes_Eratosthenes(ll n) {
    //埃氏筛
    //复杂度O(n*log2(log2n))
    //获取1~n的所有质数
    Primes[0] = 0;
    isPrime.set();
    isPrime[0] = isPrime[1] = 0;
    for (ll i = 2;i <= n;i++) {
        if (isPrime[i]) {
            minFactor[i] = i;
            Primes[++Primes[0]] = i;
            for (ll j = i * i;j <= n;j += i) {
                isPrime[j] = 0;
                if (minFactor[j] == 0) {
                    minFactor[j] = i;
                }
            }
        }
    }
}
