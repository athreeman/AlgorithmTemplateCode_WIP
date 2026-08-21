#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int MAXN = 1e7;
bitset<2 * MAXN + 1>isPrime;//标记质数
vector<ll>Primes;//存储质数
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