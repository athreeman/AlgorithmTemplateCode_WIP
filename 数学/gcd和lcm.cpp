#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll mod = 1e9 + 7;

//最大公约数
//辗转相除法
//gcd(a,b)=gcd(b,a%b)
ll gcd(ll a, ll b) {
    while (b) {
        ll tmp = a;
        a = b;
        b = tmp % b;
    }
    return a;
}

//最小公倍数
ll lcm(ll a, ll b) {
    if (a == 0 || b == 0) {
        return 0;
    }
    return a / gcd(a, b) * b;
}