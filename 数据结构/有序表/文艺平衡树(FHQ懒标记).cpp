#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e5;
int head = 0, cnt = 0;

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<int>dist(1, INT_MAX);

struct {
    int key;
    int priority;
    int left;
    int right;
    int size;
    bool isRev;
}node[MAXN + 1];

void clear() {
    for (int i = 0;i <= cnt;i++) {
        node[i] = { 0,0,0,0,0,0 };
    }
}

int create(int val) {
    node[++cnt].key = val;
    node[cnt].size = 1;
    node[cnt].isRev = false;
    node[cnt].priority = dist(gen);
    return cnt;
}

void up(int i) {
    node[i].size = node[node[i].left].size + node[node[i].right].size + 1;
}

void down(int i) {
    if (node[i].isRev) {
        swap(node[i].left, node[i].right);
        node[node[i].left].isRev ^= 1;
        node[node[i].right].isRev ^= 1;
        node[i].isRev = false;
    }
}

void split(int l, int r, int i, int rk) {
    if (i == 0) {
        node[l].right = node[r].left = 0;
    }
    else {
        down(i);
        if (node[node[i].left].size + 1 <= rk) {
            node[l].right = i;
            split(i, r, node[i].right, rk - node[node[i].left].size - 1);
        }
        else {
            node[r].left = i;
            split(l, i, node[i].left, rk);
        }
        up(i);
    }
}

int merge(int l, int r) {
    if (l == 0 || r == 0) {
        return l + r;
    }
    if (node[l].priority >= node[r].priority) {
        down(l);
        node[l].right = merge(node[l].right, r);
        up(l);
        return l;
    }
    else {
        down(r);
        node[r].left = merge(l, node[r].left);
        up(r);
        return r;
    }
}

void printTree(int i) {
    if (i != 0) {
        down(i);
        printTree(node[i].left);
        cout << node[i].key << ' ';
        printTree(node[i].right);
    }
}

void reverse(int jobl, int jobr) {
    split(0, 0, head, jobr);
    //    <=jobr             >jobr
    int l = node[0].right, r = node[0].left;
    split(0, 0, l, jobl - 1);
    //    <jobl             jobl<=&&<=jobr
    int lm = node[0].right, rm = node[0].left;
    node[rm].isRev ^= 1;
    l = merge(lm, rm);
    head = merge(l, r);
}

void solve() {
    int n, m;
    cin >> n >> m;
    clear();
    for (int i = 1;i <= n;i++) {
        head = merge(head, create(i));
    }
    while (m--) {
        int l, r;
        cin >> l >> r;
        reverse(l, r);
    }
    printTree(head);
}
