#include<bits/stdc++.h>
using namespace std;
using ll = long long;

//通过建立映射数组f[val]=i
//获取值val在对内的映射位置i
//如下模板代码维护小根堆，且仅在插入值不存在或更小时执行操作
//若需要普遍性更新，需要在变大时执行siftDown操作
const int MAXN = 2e5;
int f[MAXN + 1];//堆的反向索引表,点i在堆中的位置
pair<ll, int> heap[MAXN + 1];//堆:{值,点}
int siz = 0;//堆的大小

int heapIdx;
ll heapVal;

//上浮
void siftUp(int i) {
    while (i > 0 && heap[i].first < heap[(i - 1) >> 1].first) {
        swap(f[heap[i].second], f[heap[(i - 1) >> 1].second]);
        swap(heap[i], heap[(i - 1) >> 1]);
        i = (i - 1) >> 1;
    }
}

//下沉
void siftDown(int i) {
    int l = 2 * i + 1, r = l + 1;
    while (l < siz) {
        int best = r < siz && heap[r].first < heap[l].first ? r : l;
        if (heap[best].first >= heap[i].first) {
            return;
        }
        swap(f[heap[best].second], f[heap[i].second]);
        swap(heap[i], heap[best]);
        i = best;
        l = 2 * i + 1;
        r = l + 1;
    }
}

//插入新值，该函数同时实现插入、更新、忽略的判断
void HeapInsert(ll val, int idx) {
    if (f[idx] != -1) {
        //已在堆内,执行更新操作
        update(idx, val);
        return;
    }
    int cur = ++siz - 1;
    heap[cur].first = val;
    heap[cur].second = idx;
    f[idx] = cur;
    siftUp(cur);
}

//更新值
void update(int idx, ll val) {
    int i = f[idx];//获取该点在堆内的位置
    if (val < heap[i].first) {
        heap[i].first = val;
        siftUp(i);
    }
}

//弹出堆顶
void pop() {
    if (siz == 0)heapIdx = -1;
    swap(f[heap[0].second], f[heap[--siz].second]);
    swap(heap[0], heap[siz]);
    heapIdx = heap[siz].second;
    heapVal = heap[siz].first;
    f[heap[siz].second] = -1;//删除
    siftDown(0);
}
