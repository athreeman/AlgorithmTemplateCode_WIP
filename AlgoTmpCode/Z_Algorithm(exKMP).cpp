#include<bits/stdc++.h>
using namespace std;
//Z算法
//z[i]表示s[i...n]和s[0...n]的最长匹配前缀长度
//r表示已知的最远配对距离
//c表示达到最远配对距离的最早位置
//情况1：i不被r包住,直接从i扩展
//情况2：i被r包住,z[i-c]在扩展区域内,z[i]=z[i-c]
//情况3：i被r包住,z[i-c]在扩展区域外,z[i]=r-i
//情况4：i被r包住,z[i-c]在扩展区域边界,从r开始扩展

//e[i]表示a[i...n]和b[0...n]的最长匹配前缀长度
//e的所有情况类比z的四种情况
class Z {
private:
    static const int MAXN = 2e5;
    static int z[MAXN + 1];
    static int e[MAXN + 1];
public:
    void zArray(string s) {
        z[0] = s.size();
        for (int i = 1, c = 1, r = 1, len;i < s.size();i++) {
            len = r > i ? min(r - i, z[i - c]) : 0;//获取情况1,3否者赋值0
            while (i + len < s.size() && s[i + len] == s[len]) {
                //while循环只有情况1,4会正常执行
                len++;
            }
            if (i + len > r) {
                r = i + len;
                c = i;
            }
            z[i] = len;
        }
    }
    void eArray(string a, string b) {
        int n = a.size();
        int m = b.size();
        zArray(b);//生成a对于b的e数组,依赖于b的z数组
        for (int i = 0, c = 0, r = 0, len;i < n;i++) {
            len = r > i ? min(r - i, z[i - c]) : 0;
            while (i + len < n && len < m && a[i + len] == b[len]) {
                len++;
            }
            if (i + len > r) {
                r = i + len;
                c = i;
            }
            e[i] = len;
        }
    }
};
