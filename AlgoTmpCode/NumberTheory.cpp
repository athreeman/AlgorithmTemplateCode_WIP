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

//乘法快速幂
ll pw(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1)res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

//费马小定理,求逆元
ll inv_(ll a, ll p) {
    return pw(a, p - 2);
}

//暴力求逆元
//只需满足gcd(a,mod)=1即可
ll inv02_(ll a, ll mod) {
    a %= mod;
    for (ll t = 1; t < mod; t++) {
        if ((a * t) % mod == 1) return t;
    }
    return 1;
}

//逆元的线性递归
//例题：https://www.luogu.com.cn/problem/P3811
ll inv[3000001];
void initial_inv(ll n, ll p) {
    inv[1] = 1;
    for (ll i = 2;i <= n;i++) {
        inv[i] = p - inv[p % i] * (p / i) % p;
    }
}

//阶乘
ll N[200001];
void initial_N(int n) {
    N[0] = 1;
    for (ll i = 1;i <= n;i++) {
        N[i] = N[i - 1] * i % mod;
    }
}

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

//排列组合
ll C(ll n, ll m) {
    if (m == 0 || m == n)return 1;
    else if (m<0 || m>n)return 0;
    ll ans = N[n] % mod * inv_(N[m] * N[n - m], mod) % mod;
    return ans;
}

//同余原理
void Properties_of_Congruence() {
    ll a, b;
    cin >> a >> b;

    //加法
    //(a%m+b%m)%m=(a+b)%m
    cout << (a % mod + b % mod) % mod << ' ';
    cout << (a + b) % mod << '\n';

    //乘法
    //(a%m*b%m)%m=(a*b)%mod
    //-a%mod=(-a%mod+mod)%mod=(mod-a)%mod
    //例,-3%7=(-3%7+7)%7=4%7
    cout << (a % mod * b % mod) % mod << ' ';
    cout << (a * b) % mod << '\n';

    //减法
    //(a-b)%mod=(a%mod-b%mod+mod)%mod
    //+mod解决负数的问题
    cout << (a - b + mod) % mod << ' ';
    cout << (a % mod - b % mod + mod) % mod << '\n';

    //除法,逆元
    //a/b%mod应该写为a*inv(b)%mod的形式
    cout << a * inv_(b, mod) % mod << '\n';

    //若(a+b)%mod=0
    //给定a,则b%mod=(mod-a%mod)%mod
    //(x+y)%17=0
    int x=3;
    int mod=17;
    int ymod=(mod-x%mod)%mod;

    //(a+b)%mod==j
    //给定a,b%mod=((j-a)%mod+mod)%mod
    //(c+d)%17=11
    int c=5;
    int r=11;
    mod=17;
    int dmod=((r-c)%mod+mod)%mod;
}

//2的幂快速判断
void isPw2(int n) {
    //若x>0,x&(~x+1)==x则x是2的幂
    //~x+1=-x
    if (n == 0) {
        cout << 'F' << '\n';
        return;
    }
    if ((n & (-n)) == n) {
        cout << 'T' << '\n';
    }
    else {
        cout << 'F' << '\n';
    }
}

//Raney引理:若整数序列(下标1~m)每一项不超过1(a[i]<=1),总和为正整数n,
//则它的m个循环移位中恰有n个移位的所有非空前缀和为正
void Raney() {
    cout << "Raney:" << '\n';
    const int m = 22;
    int arr[m + 1] = { 0,1,1,1,-2,1,-1,1,1,-3,1,1,
        -2,1,1,1,1,1,1,-1,-2,1,1 };
    int n = 0;
    for (int i = 1;i <= m;i++) {
        n += arr[i];
    }
    cout << n << ' ' << m << '\n';
    int cnt = 0;
    for (int i = 1;i <= m;i++) {
        int sum = 0;
        int flg = 1;
        for (int j = i;j <= i + m - 1;j++) {
            sum += arr[(j - 1) % m + 1];
            if (sum <= 0)flg = 0;
        }
        if (flg)cnt++;
    }
    cout << "n: " << n << '\n';
    cout << "cnt: " << cnt << '\n';
}


//中国剩余定理
void Chinese_Remainder_Theorem() {
}

//裴蜀定理
void Bézout_theorem() {
}

//找到最小的非负整数k,使得a+k的最低位1>=minV
int calCost(int a, int minV) {
    int v = GetLowBitOne(a);
    if (v >= minV) return 0;
    int pow2 = 1 << minV;
    int m = (a + pow2 - 1) >> minV;
    int b = m << minV;
    return b - a;
}


//小结论
ll ff(ll n, ll l, ll k) {
    //n个元素(数量不限),要求用n个元素凑出长度=l的数组
    //两个相同元素之间的间隔要>=k
    //0<=k<n<=l
    //可能的方案数=n!*(n-k)^(l-k)/(n-k)!
    //n-k的l-k次幂
    return N[n] * pw(n - k, l - k) % mod * inv_(N[n - k], mod);
}

//用给定位状态status的1位组成的集合(即status位状态的所有子集)
//循环遍历
//for(int i=status;i>0;i=(i-1)&status){cout<<i;...};


//强哥德巴赫猜想:任意大于2的偶数都可以表示成两个质数之和,该猜想对于[1,1e9]内的整数已证明满足

//弱哥德巴赫猜想(此猜想已被彻底证明成立):任一大于5的奇数都可以表示成三个质数之和
//其中若n&1且n-2是质数则最少可以拆为2个

// 函数f(n),n>=1
// 积性函数：f(1)=1且对于gcd(m,n)=1,存在f(m*n)=f(n)*f(m)
// 完全积性函数：f(1)=1且对于n>=1,m>=1,存在f(m*n)=f(n)*f(m)
// 完全积性函数
// 除了f(n*m)=f(n)*f(m)
// 也可以是f(n*m*....*k)=f(n)*f(m)*...f(k)多个



//加法运算的位本质
//对于任意整数a, b
//都满足a + b = a ^ b + 2(a & b)


//快速提取x最右侧的1(x!=0)
//ll lowBitOne=x&(-x)
