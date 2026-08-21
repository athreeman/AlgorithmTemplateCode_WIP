#include<bits/stdc++.h>
using namespace std;
using ll = long long;
class KMP {
private:
    /*
    整体时间复杂度O(n + m)
    kmp : O(n)
    nextArr : O(m)

    kmp返回字符串t作为s的子串的开头位置
    如若是返回第一个符合要求的子串的开头位置, 修改如下
    while (i < n && j < m) {
        ......
        (不需要if:j == m的特判)
        return j == m ? i - j : -1;
    }

    nxt数组中nxt[0]作为哨兵位置,nxt[m]需要用来表示字符t整体
    nxt[i]表示(不包含当前位置i)最长前后缀相同字符长度
    例如aaavfvdfaaad, nxt[12] = 3, "aaa" = "aaa"
    生成目标字符t的nxt数组
    */
    static const int MAXN = 1e6;
    int nxt[MAXN + 2];

    vector<int> kmp(string s, string t) {
        vector<int>res;
        int x = 0, y = 0;// x是s的指针,y是t的指针
        int n = s.size(), m = t.size();
        while (x < n) {
            if (s[x] == t[y]) {
                x++, y++;// 配对成功
            }
            else if (y == 0) {
                x++;// y指向t开头
            }
            else {// j跳跃
                y = nxt[y];
            }
            if (y == m) {// 满足
                res.push_back(x - y);
                y = nxt[y];
            }
        }
        return res;
    }

    void nextArr(string s) {
        int n = s.size();
        nxt[0] = -1;
        nxt[1] = 0;
        if (n == 1) {
            return;
        }
        int i = 2;
        int cn = 0;// 左侧字符匹配位置
        while (i <= n) {
            // 配对时不包含当前位置
            if (s[i - 1] == s[cn]) {
                nxt[i++] = ++cn;
            }
            else if (cn > 0) {
                cn = nxt[cn];// 跳跃
            }
            else {// cn == 0
                nxt[i++] = 0;
            }
        }
    }
};
