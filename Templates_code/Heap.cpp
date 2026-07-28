#include<bits/stdc++.h>

using namespace std;
using ll = long long;
const int MAXN = 2e5;



class MinHeap_n {
public:
    //小根堆
    //自底向顶建堆
    //复杂度O(n)
    int heap[MAXN + 1];
    int siz = 0;

    void getArr(vector<int>& nums) {
        for (int i = 0;i < nums.size();i++) {
            heap[i] = nums[i];
        }
        siz = nums.size();
    }

    void siftDown(int i) {
        int l = 2 * i + 1;
        while (l < siz) {
            int best = l + 1 < siz && heap[l + 1] < heap[l] ? l + 1 : l;
            if (heap[best] >= heap[i])return;
            swap(heap[i], heap[best]);
            i = best;
            l = 2 * i + 1;
        }
    }

    void heapInsert() {
        for (int i = (siz - 2) / 2;i >= 0;i--) {
            siftDown(i);
        }
    }

    int pop() {
        if (siz == 0)return -1;
        //头部0和末尾交换位置,丢弃末尾
        swap(heap[0], heap[--siz]);
        siftDown(0);
        //siz现在就是原先的丢弃位置
        return heap[siz];
    }

};



class MaxHeap_nlogn {
public:
    //自顶向底建堆
    //复杂度O(nlogn)
    int heap[MAXN + 1];
    int siz = 0;

    //大根堆
    void heapInsert(int val) {
        int cur = ++siz - 1;
        heap[cur] = val;
        while (cur > 0 && heap[cur] > heap[(cur - 1) >> 1]) {
            //小根堆,只需修改符号
            //while(cur>0&&heap[cur]<heap[(cur-1)>>1])
            swap(heap[cur], heap[(cur - 1) >> 1]);
            cur = (cur - 1) >> 1;
        }
    }

    void siftDown(int i) {
        int l = 2 * i + 1;
        while (l < siz) {
            //大根堆,和左右孩子数值最大的交换,且必须大于当前节点值
            //小根堆修改符号即可
            int best = l + 1 < siz && heap[l + 1] > heap[l] ? l + 1 : l;
            if (heap[best] <= heap[i])return;
            swap(heap[i], heap[best]);
            i = best;
            l = 2 * i + 1;
        }
    }

    void siftUp(int i) {
        while (i > 0 && heap[(i - 1) / 2] < heap[i]) {
            //小根堆修改符号即可
            swap(heap[i], heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    int pop() {
        if (siz == 0)return -1;
        //头部0和末尾交换位置,丢弃末尾
        swap(heap[0], heap[--siz]);
        siftDown(0);
        //siz现在就是原先的丢弃位置
        return heap[siz];
    }

    int top() {
        if (siz == 0)return -1;
        return heap[0];
    }

};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    vector<int>nums;
    int n;
    cin >> n;
    while (n--) {
        int in;
        cin >> in;
        nums.push_back(in);
    }
    MinHeap_n q;
    q.getArr(nums);
    q.heapInsert();
    while (q.siz > 0) {
        cout << q.pop() << ' ';
    }
    cout << '\n';
    return 0;
}
