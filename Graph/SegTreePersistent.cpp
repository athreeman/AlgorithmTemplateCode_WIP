#include<bits/stdc++.h>
using ll = long long;
using namespace std;

//可持久化线段树(主席树)

//单点修改+单点查询......查询不同版本单点值
//区间修改+范围查询......查询区间第k小
//区间修改+范围查询(懒标记)
//区间修改+区间查询+标记永久化(普通线段树的标记永久化)

//核心：保留原数据,拷贝新节点,范围新编号,获取不同版本
//功能：查询第k小，维护前缀信息，单点和范围查询

class Single_AND_Single {

    // 例题1题解代码：
    // 模板例题1：https://www.luogu.com.cn/problem/P3919 单点修改+单点查询(不同版本单点值)
private:

    const static int MAXN = 1e6;
    const static int MAXT = 3e7;
    //(n+m)*log2(n)

    int n, m;
    int a[MAXN + 1];
    int version_root[MAXT + 1];
    int cnt = 0;
    int idx_ver = -1;

    struct node
    {
        int left;
        int right;
        int val;
    }T[MAXT + 1];

    //节点拷贝
    void copy(int u, int v)
    {
        //拷贝,v->u
        T[u].left = T[v].left;
        T[u].right = T[v].right;
        T[u].val = T[v].val;
    }

    //初始建树
    int build(int l, int r)
    {
        int rt = ++cnt;//当前节点
        if (l == r)
        {
            T[rt].left = T[rt].right = -1;
            T[rt].val = a[l];
            return rt;
        }
        int mid = (l + r) >> 1;
        T[rt].val = -1;
        T[rt].left = build(l, mid);
        T[rt].right = build(mid + 1, r);
        return rt;
    }

    //更新,建新版本树
    //传参：目标位置，修改值，原版编号，当前位置区间
    int update(int pos, int val, int idx, int l, int r)
    {
        int rt = ++cnt;//当前新建点编号
        copy(rt, idx);//idx的值拷贝给rt
        if (l == r)T[rt].val = val;
        else
        {
            int mid = (l + r) >> 1;
            if (pos <= mid)T[rt].left = update(pos, val, T[idx].left, l, mid);
            else T[rt].right = update(pos, val, T[idx].right, mid + 1, r);
        }
        return rt;
    }

    //查询某版本值
    //传参：节点编号，目标位置，当前位置区间
    int query(int idx, int pos, int l, int r)
    {
        if (l == r)return T[idx].val;
        int mid = (l + r) >> 1;
        if (pos <= mid)return query(T[idx].left, pos, l, mid);
        else return query(T[idx].right, pos, mid + 1, r);
        return 0;
    }

public:

    void solve() {
        cin >> n >> m;
        for (int i = 1;i <= n;i++)
        {
            cin >> a[i];
        }
        version_root[++idx_ver] = build(1, n);
        for (int i = 1;i <= m;i++)
        {
            int opt, version;
            cin >> version >> opt;
            if (opt == 1)
            {
                int x, y;
                cin >> x >> y;
                version_root[++idx_ver] = update(x, y, version_root[version], 1, n);
            }
            else
            {
                int x;
                cin >> x;
                version_root[++idx_ver] = version_root[version];
                cout << query(version_root[version], x, 1, n) << '\n';
            }
        }
    }

};

class SarchRankMin {
    // 模板例题2：https://www.luogu.com.cn/problem/P3834 单点修改+范围查询(区间第k小,线段树维护前缀信息)

private:

    const static int MAXN = 2e5;
    const static int MAXT = 5e6;
    int arr[MAXN + 1];
    int n, m, s;


    //版本v表示原数组arr[1~v]的所有数的出现次数 
    //root[v]表示第v版本的树根
    int root[MAXN + 1];//不同版本的根
    int sorted[MAXN + 1];//去重
    int left[MAXT + 1];
    int right[MAXT + 1];
    int siz[MAXT + 1];
    int cnt = 0;//节点编号

    int build(int l, int r)
    {
        int rt = ++cnt;
        left[rt] = right[rt] = -1;
        siz[rt] = 0;
        if (l < r)
        {
            int mid = (l + r) >> 1;
            left[rt] = build(l, mid);
            right[rt] = build(mid + 1, r);
        }
        return rt;
    }

    int insert(int jobi, int l, int r, int i)
    {
        int rt = ++cnt;
        left[rt] = left[i];
        right[rt] = right[i];
        siz[rt] = siz[i] + 1;
        if (l < r)
        {
            int mid = (l + r) >> 1;
            if (jobi <= mid)left[rt] = insert(jobi, l, mid, left[i]);
            else right[rt] = insert(jobi, mid + 1, r, right[i]);
        }
        return rt;
    }

    int query(int jobk, int l, int r, int u, int v)
    {
        //u<v
        if (l == r)return l;
        int lsiz = siz[left[v]] - siz[left[u]];
        int mid = (l + r) >> 1;
        if (lsiz >= jobk)return query(jobk, l, mid, left[u], left[v]);
        else return query(jobk - lsiz, mid + 1, r, right[u], right[v]);
    }

    void prepare()
    {
        std::sort(sorted + 1, sorted + n + 1);
        s = 1;
        for (int i = 2;i <= n;i++)
        {
            if (sorted[s] != sorted[i])
            {
                sorted[++s] = sorted[i];
            }
        }
        root[0] = build(1, s);
    }

    int get_id(int val)
    {
        int l = 1, r = s;
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            if (sorted[mid] == val)return mid;
            else if (sorted[mid] > val)r = mid - 1;
            else l = mid + 1;
        }
        return l - 1;
    }

public:

    void solve()
    {
        cin >> n >> m;
        for (int i = 1;i <= n;i++)
        {
            cin >> arr[i];
            sorted[i] = arr[i];
        }
        prepare();
        for (int i = 1;i <= n;i++)
        {
            int jobi = get_id(arr[i]);
            root[i] = insert(jobi, 1, s, root[i - 1]);
        }
        while (m--)
        {
            int l, r, k;
            cin >> l >> r >> k;
            int rank = query(k, 1, s, root[l - 1], root[r]);
            cout << sorted[rank] << '\n';
        }
        return;
    }

};

class Range_AND_Lazy {

    // 模板例题3：https://www.luogu.com.cn/problem/SP11470 区间修改+范围查询(懒标记)
private:

    const static int MAXN = 1e5;
    const static int MAXT = MAXN * 22;
    int n, m, t;
    int arr[MAXN + 1];
    int root[MAXN + 1];
    int left[MAXT + 1];
    int right[MAXT + 1];
    ll add[MAXT + 1];
    ll sum[MAXT + 1];
    int cnt = 0;

    int clone(int i) {
        int rt = ++cnt;
        left[rt] = left[i];
        right[rt] = right[i];
        sum[rt] = sum[i];
        add[rt] = add[i];
        return rt;
    }

    void up(int i) {
        sum[i] = sum[left[i]] + sum[right[i]];
    }

    //lazy标记
    void lazy(int i, ll val, int siz) {
        sum[i] += val * (ll)siz;
        add[i] += val;
    }

    //懒标记下发
    void down(int i, int ln, int rn) {
        if (add[i] == 0)return;
        left[i] = clone(left[i]);
        right[i] = clone(right[i]);
        lazy(left[i], add[i], ln);
        lazy(right[i], add[i], rn);
        add[i] = 0;
    }

    int build(int l, int r) {
        int rt = ++cnt;
        left[rt] = right[rt] = -1;
        add[rt] = sum[rt] = 0;
        if (l == r) {
            sum[rt] = arr[l];
        }
        else {
            int mid = (l + r) >> 1;
            left[rt] = build(l, mid);
            right[rt] = build(mid + 1, r);
            up(rt);
        }
        return rt;
    }

    //范围增加
    int add_func(int jobl, int jobr, ll jobv, int l, int r, int i)
    {
        //克隆
        int rt = clone(i);
        if (l >= jobl && r <= jobr) {
            //标记
            lazy(rt, jobv, r - l + 1);
        }
        else {
            int mid = (l + r) >> 1;
            down(rt, mid - l + 1, r - mid);
            if (jobl <= mid) {
                left[rt] = add_func(jobl, jobr, jobv, l, mid, left[rt]);
            }
            if (jobr > mid) {
                right[rt] = add_func(jobl, jobr, jobv, mid + 1, r, right[rt]);
            }
            up(rt);
        }
        return rt;
    }

    ll query(int jobl, int jobr, int l, int r, int i)
    {
        if (l >= jobl && r <= jobr) {
            return sum[i];
        }
        int mid = (l + r) >> 1;
        down(i, mid - l + 1, r - mid);
        ll ans = 0;
        if (jobl <= mid) {
            ans += query(jobl, jobr, l, mid, left[i]);
        }
        if (jobr > mid) {
            ans += query(jobl, jobr, mid + 1, r, right[i]);
        }
        return ans;
    }

    void prepare() {
        t = 0;
        cnt = 0;
        root[0] = build(1, n);
    }

public:

    void solve() {
        cin >> n >> m;
        for (int i = 1;i <= n;i++) {
            cin >> arr[i];
        }
        prepare();
        while (m--) {
            char opt;
            cin >> opt;
            if (opt == 'C') {
                int l, r;
                ll d;
                cin >> l >> r >> d;
                root[t + 1] = add_func(l, r, d, 1, n, root[t]);
                t++;
            }
            else if (opt == 'Q') {
                int l, r;
                cin >> l >> r;
                cout << query(l, r, 1, n, root[t]) << '\n';
            }
            else if (opt == 'H') {
                int l, r, jobt;
                cin >> l >> r >> jobt;
                cout << query(l, r, 1, n, root[jobt]) << '\n';
            }
            else {
                cin >> t;
            }
        }
        return;
    }

};

class Range_AND_Persistent {

    // 模板例题4：https://www.luogu.com.cn/problem/P3372 区间修改+区间查询+标记永久化(普通线段树的标记永久化)

private:

    const static int MAXN = 1e5;
    ll n, m;
    ll sum[4 * MAXN + 5];
    ll addTag[4 * MAXN + 5];
    ll arr[MAXN + 5];

    void build(int l, int r, int i) {
        if (l == r) {
            sum[i] = arr[l];
        }
        else {
            int mid = (l + r) >> 1;
            build(l, mid, 2 * i);
            build(mid + 1, r, 2 * i + 1);
            sum[i] = sum[2 * i] + sum[2 * i + 1];
        }
        addTag[i] = 0;
    }

    void add(int jobl, int jobr, ll jobv, int l, int r, int i) {
        ll a = max(l, jobl), b = min(r, jobr);
        sum[i] += (b - a + 1LL) * jobv;
        if (jobl <= l && jobr >= r) {
            addTag[i] += jobv;
        }
        else {
            int mid = (l + r) >> 1;
            if (jobl <= mid) {
                add(jobl, jobr, jobv, l, mid, 2 * i);
            }
            if (jobr > mid) {
                add(jobl, jobr, jobv, mid + 1, r, 2 * i + 1);
            }
        }
    }

    ll query(int jobl, int jobr, ll addHistory, int l, int r, int i) {
        if (jobl <= l && jobr >= r) {
            return sum[i] + addHistory * ll(r - l + 1);
        }
        int mid = (l + r) >> 1;
        ll ans = 0;
        if (jobl <= mid) {
            ans += query(jobl, jobr, addHistory + addTag[i], l, mid, 2 * i);
        }
        if (jobr > mid) {
            ans += query(jobl, jobr, addHistory + addTag[i], mid + 1, r, 2 * i + 1);
        }
        return ans;
    }

public:

    void solve()
    {
        cin >> n >> m;
        fill(arr, arr + n + 1, 0);
        for (int i = 1;i <= n;i++) {
            cin >> arr[i];
        }
        build(1, n, 1);
        while (m--) {
            int opt;
            cin >> opt;
            if (opt == 1) {
                ll x, y, k;
                cin >> x >> y >> k;
                add(x, y, k, 1, n, 1);
            }
            else {
                ll x, y;
                cin >> x >> y;
                cout << query(x, y, 0, 1, n, 1) << '\n';
            }
        }
        return;
    }

};