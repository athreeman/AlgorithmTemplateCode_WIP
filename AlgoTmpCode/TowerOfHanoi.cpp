#include<bits/stdc++.h>
using namespace std;
class TOH {
public:
    //经典汉诺塔问题：
    //把A堆的所有盘子移动到C,B作为工具堆
    //要求每个盘子都必须严格大于他下面的盘子
    using ll = long long;
    ll f(ll n, char cur, char tool, char goal) {
        //当前cur移动到goal,tool是工具盘
        if (n == 0) {
            return 0;
        }
        //递归
        ll ans = 0;
        ans = ans + f(n - 1, cur, goal, tool); //[1, n - 1] 移动到tool堆, goal堆作为实际工具堆

        ans = ans + 1;//+1表示最后第n个移动到goal堆
        cout << cur << "->" << goal << '\n';//输出第n个盘移动方式

        ans = ans + f(n - 1, tool, cur, goal);//最后tool作为新的cur堆,把上面的n-1个移动到goal

        return ans;
    }
};
