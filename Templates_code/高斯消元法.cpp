#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = double;

//逆元的线性递归
ll inv[3000001];
void initial_inv(ll n, ll p) {
    inv[0] = 0;
    inv[1] = 1;
    for (ll i = 2;i <= n;i++) {
        inv[i] = p - inv[p % i] * (p / i) % p;
    }
}

//gcd(a,b)=gcd(b,a%b)
ll gcd(ll a, ll b) {
    while (b) {
        ll tmp = a;
        a = b;
        b = tmp % b;
    }
    return a;
}

class gauss_linear {
private:

    const ld eps = 1e-7;
    ld mat[101][102];

    void gauss(int n) {
        cout << fixed << setprecision(12);
        for (int i = 1;i <= n;i++) {
            int max_idx = i;
            //获取同一列的最大行
            for (int j = 1;j <= n;j++) {
                if (j < i && fabs(mat[j][j]) >= eps) {
                    continue;
                }
                if (fabs(mat[j][i]) > fabs(mat[max_idx][i])) {
                    max_idx = j;
                }
            }
            //交换
            swap(mat[max_idx], mat[i]);
            if (fabs(mat[i][i]) >= eps) {
                ld tmp = mat[i][i];
                //当前主元变1,主元所在行也随着变
                for (int j = 1;j <= n + 1;j++) {
                    mat[i][j] /= tmp;
                }
                //当前列,变0
                for (int j = 1;j <= n;j++) {
                    if (i != j) {
                        ld rate = mat[j][i] / mat[i][i];
                        for (int k = i;k <= n + 1;k++) {
                            mat[j][k] -= mat[i][k] * rate;
                        }
                    }
                }
            }
            else {
                cout << "No Solution" << '\n';
                return;
            }
        }
        cout << fixed << setprecision(2);
        for (int i = 1;i <= n;i++) {
            if (fabs(mat[i][n + 1]) < eps)mat[i][n + 1] = 0;
            cout << mat[i][n + 1] << '\n';
        }
        return;
    }

public:

    void solve(int n) {
        for (int i = 1;i <= n;i++) {
            for (int j = 1;j <= n + 1;j++) {
                cin >> mat[i][j];
            }
        }
        gauss(n);
    }
};

//异或方程组
class gauss_xor {
private:

    int R = 1;
    int need = 0;
    const static int MAXN = 2e3;
    bitset<1> mat[MAXN + 1][MAXN + 2];

    void gauss(int n) {
        need = 1;
        for (int i = 1;i <= n;i++) {
            for (int j = 1;j <= R;j++) {
                if (j < i && mat[j][j] == 1) {
                    //主元跳过
                    //本题实际可以直接j从i开始
                    //若出现自由元可直接输出
                    continue;
                }
                if (mat[j][i] == 1) {
                    need = max(need, j);
                    //为了方程组消元
                    //用到了第j行的记录,所以need取用到的最大行
                    //计算消元用到的最大行即需要的最少信息数
                    swap(mat[j], mat[i]);
                    break;
                }
            }
            if (mat[i][i] == 1) {
                for (int j = 1;j <= R;j++) {
                    if (j != i && mat[j][i] == 1) {
                        for (int k = 1;k <= n + 1;k++) {
                            mat[j][k] ^= mat[i][k];
                        }
                    }
                }
            }
            else {
                cout << "Cannot Determine" << '\n';
                return;
            }
        }
        //是否唯一解
        for (int i = 1;i <= n;i++) {
            if (mat[i][i] == 0) {
                cout << "Cannot Determine" << '\n';
                return;
            }
        }
        cout << need << '\n';
        for (int i = 1;i <= n;i++) {
            if (mat[i][n + 1] == 0) {
                cout << "Earth" << '\n';
            }
            else {
                cout << "?y7M#" << '\n';
            }
        }
    }

    void print(int n) {
        for (int i = 1;i <= R;i++) {
            for (int j = 1;j <= n + 1;j++) {
                cout << mat[i][j] << ' ';
            }
            cout << '\n';
        }
        cout << '\n';
    }

public:

    void solve(int n, int m) {
        R = max(n, m);
        for (int i = 1;i <= m;i++) {//1~m行
            string str;
            int op;
            cin >> str >> op;
            //补元只补列,不补行
            //非补元列,存在输入
            //1~n列
            for (int j = 1;j <= n;j++) {
                if (str[j - 1] == '1') {
                    mat[i][j] = 1;
                }
                else {
                    mat[i][j] = 0;
                }
            }
            if (op == 1) {
                mat[i][n + 1] = 1;
            }
            else {
                mat[i][n + 1] = 0;
            }
        }
        gauss(n);
    }
};


int Mat03[1001][1001];
//同余方程组
class gauss_mod {
    //a ≡ b ≡ c (mod p)
    //即 a % p = b % p = c % p
    //-a % mod=(-a % mod + mod ) % mod = ( mod - a ) % mod
    //即 -a % mod =( mod - a ) % mod 同余方程组需要该转换
    //例, -3 % 7 = ( -3 % 7 + 7 ) % 7 = 4 % 7
private:
    using ll = long long;
    const static int mod = 3;
    int arr[31][31];
    int idx = 0;
    int cnt = 0;
    pair<int, int>dir[4] = { {0,-1},{0,1},{1,0},{-1,0} };

    void gauss(int n) {
        for (int i = 1;i <= n;i++) {
            for (int j = 1;j <= n;j++) {
                if (j < i && Mat03[j][j] != 0) {
                    //主元,跳过
                    continue;
                }
                if (Mat03[j][i] != 0) {
                    swap(Mat03[i], Mat03[j]);
                    break;
                }
            }
            if (Mat03[i][i] != 0) {
                //处理
                for (int j = 1;j <= n;j++) {
                    if (j != i && Mat03[j][i] != 0) {
                        int g = gcd(Mat03[j][i], Mat03[i][i]);
                        int a = Mat03[i][i] / g;
                        int b = Mat03[j][i] / g;
                        if (j < i && Mat03[j][j] != 0) {
                            for (int k = 1;k < i;k++) {
                                Mat03[j][k] = Mat03[j][k] * a % mod;
                            }
                        }
                        for (int k = i;k <= n + 1;k++) {
                            Mat03[j][k] = ((Mat03[j][k] * a - Mat03[i][k] * b) % mod + mod) % mod;
                        }
                    }
                }
            }
        }
        for (int i = 1;i <= n;i++) {
            if (Mat03[i][i] != 0) {
                //主元
                Mat03[i][n + 1] = (Mat03[i][n + 1] * inv[Mat03[i][i]]) % mod;
                cnt += Mat03[i][n + 1];
            }
        }
    }

public:
    void solve(int n, int m) {
        for (int i = 1;i <= n * m;i++) {
            for (int j = 1;j <= n * m + 1;j++) {
                Mat03[i][j] = 0;//方程组初始化
            }
        }
        for (int i = 1;i <= n;i++) {
            for (int j = 1;j <= m;j++) {
                //申请空间,建立映射
                arr[i][j] = ++idx;
                cin >> Mat03[idx][n * m + 1];
                Mat03[idx][n * m + 1] = (3 - Mat03[idx][n * m + 1]) % mod;
            }
        }
        for (int i = 1;i <= n;i++) {
            for (int j = 1;j <= m;j++) {
                //n*m每个点,建立一行
                Mat03[arr[i][j]][arr[i][j]] = 2;
                for (auto& [di, dj] : dir) {
                    int ni = i + di, nj = j + dj;
                    if (ni<1 || ni>n || nj<1 || nj>m) {
                        continue;
                    }
                    Mat03[arr[i][j]][arr[ni][nj]] = 1;
                }
            }
        }
        //n*m行,n*m列的矩阵
        gauss(n * m);
        cout << cnt << '\n';
        for (int i = 1;i <= n;i++) {
            for (int j = 1;j <= m;j++) {
                if (Mat03[arr[i][j]][n * m + 1] == 2) {
                    cout << i << ' ' << j << '\n';
                    cout << i << ' ' << j << '\n';
                }
                else if (Mat03[arr[i][j]][n * m + 1] == 1) {
                    cout << i << ' ' << j << '\n';
                }
            }
        }
    }
};

void solve01() {
    int n;
    cin >> n;
    gauss_linear g1;
    g1.solve(n);
}

void solve02() {
    int n, m;
    cin >> n >> m;
    gauss_xor g2;
    g2.solve(n, m);
}

void solve03() {
    int t;
    cin >> t;
    initial_inv(100, 3);
    while (t--) {
        int n, m;
        cin >> n >> m;
        gauss_mod g3;
        g3.solve(n, m);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    //高斯消元法
    //复杂度O(n^3)
    //重要性质:
    //存在自由元,值!=0矛盾无解
    //存在自由元,值==0多解
    //不存在自由元,全是主元,唯一解
    //主元只可以依赖自由元，自由元不依赖任何其他元
    //线性，异或，同余方程组都是如此

    //线性方程组
    //模板例题:https://www.luogu.com.cn/problem/P3389
    //solve01();

    //异或方程组
    //模板例题:https://www.luogu.com.cn/problem/P2447
    //solve02();

    //同余方程组
    //模板例题:https://acm.hdu.edu.cn/showproblem.php?pid=5755#top
    //solve03();
    return 0;
}
