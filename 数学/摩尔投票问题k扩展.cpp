#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5;
const int MAXK = 10;
//摩尔投票问题扩展,寻找数组中出现次数>n/k的元素
//维护大小为k-1的候选表
//一次删除k个元素
//k不能太大,时间复杂度会成为瓶颈,或问题本身变得无意义
int a[MAXN + 1];
int cands[MAXK + 1][2];//候选表
void update(int k, int val) {
    //已在候选表
    for (int i = 0;i < k;i++) {
        if (cands[i][0] == val && cands[i][1] > 0) {
            cands[i][1]++;
            return;
        }
    }
    //存在空位
    for (int i = 0;i < k;i++) {
        if (cands[i][1] == 0) {
            cands[i][0] = val;
            cands[i][1] = 1;
            return;
        }
    }
    //进行攻击
    for (int i = 0;i < k;i++) {
        if (cands[i][1] > 0) {
            cands[i][1]--;
        }
    }
}
void collect(int k, int n, vector<int>& ans) {
    for (int i = 0, cur, real;i < k;i++) {
        if (cands[i][1] > 0) {
            cur = cands[i][0];
            real = 0;
            for (int j = 1;j <= n;j++) {
                if (cur == a[j]) {
                    real++;
                }
            }
            if (real > n / (k + 1)) {
                ans.push_back(cur);
            }
        }
    }
}
vector<int> waterNumber(int n, int k) {
    k = k - 1;//维护的候选表大小是k-1,此步必须有！！！
    for (int i = 1;i <= n;i++) {
        update(k, a[i]);
    }
    vector<int>ans;
    collect(k, n, ans);
    return ans;
}
