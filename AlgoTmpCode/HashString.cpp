#include<bits/stdc++.h>
using namespace std;
class HashString {
    //字符串哈希
    //入参：字符串  
    //返回结果：特定数值
    //字符串哈希需要选定base进制
    //如：433,499,599,1e9+7,31,131,1313,13131,131313
    //字符的赋值ch->正整数(不要取!0!),可定制
    //模板例题：https://www.luogu.com.cn/problem/P3370
private:
    using ll = long long;
    using ull = unsigned long long;
    static const ull base = 599;
    //数字+大写+小写
    static const int MAXN = 2e6;
    static ull pow[MAXN + 1];
    static ull hash[MAXN + 1];
    ull value(const char& ch) {
        if (ch >= 'a' && ch <= 'z') {
            return ch - 'a' + 37;
        }
        else if (ch >= 'A' && ch <= 'Z') {
            return ch - 'A' + 11;
        }
        else if (ch >= '0' && ch <= '9') {
            return ch - '0' + 1;
        }
        return 0;//非法返回结果
    }
public:
    ull HashAll(const string& s) {
        ull ans = value(s[0]);
        for (ull i = 1;i < s.size();i++) {
            ans = ans * base + value(s[i]);
        }
        return ans;
    }

    void build(const string& s, int n) {
        pow[0] = 1;
        for (int i = 1;i < n;i++) {
            pow[i] = pow[i - 1] * base;
        }
        hash[0] = value(s[0]);
        for (int i = 1;i < n;i++) {
            hash[i] = hash[i - 1] * base + value(s[i]);
        }
    }
    ull HashRange(int l, int r) {
        //计算区间[l,r]的哈希值
        //调用HashRange前先手动调用build函数
        if (l == 0)return hash[r];
        return hash[r] - hash[l - 1] * pow[r - l + 1];
    }
};
