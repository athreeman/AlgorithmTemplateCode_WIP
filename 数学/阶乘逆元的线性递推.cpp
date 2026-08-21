#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll mod = 1e9 + 7;


//连续阶乘逆元的线性递推
//即阶乘的逆元
ll invN[200001];
void initial_invN(int n) {
    invN[0] = 1;
    invN[n] = inv_(N[n], mod);
    for (ll i = n - 1;i >= 1;i--) {
        invN[i] = (i + 1) * invN[i + 1] % mod;
    }
}