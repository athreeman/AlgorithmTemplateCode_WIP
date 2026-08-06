#include<bits/stdc++.h>

using ll=long long;
using std::fill;
const int MAXN=5e5+5;

//模板例题：https://www.luogu.com.cn/problem/P3379
//迭代版本

int ans[MAXN];

//链式前向星
//建图
int cnt=0;
int head[MAXN];
int next[2*MAXN];
int to[2*MAXN];
//查询
int cnt_q=0;
int head_q[MAXN];
int next_q[2*MAXN];
int idx_q[2*MAXN];
int to_q[2*MAXN];

void add_edge(int u,int v){
    next[++cnt]=head[u];
    head[u]=cnt;
    to[cnt]=v;
}

void add_query(int u,int v,int idx){
    //询问lca(u,v),问题编号idx
    next_q[++cnt_q]=head_q[u];
    head_q[u]=cnt_q;
    to_q[cnt_q]=v;
    idx_q[cnt_q]=idx;
}

//并查集
int father[MAXN];
int stack_uf[MAXN];

int find(int u){
    int cnt_uf=0;
    while(u!=father[u]){
        stack_uf[++cnt_uf]=u;
        u=father[u];
    }
    while(cnt_uf>0){
        father[stack_uf[cnt_uf]]=u;
        cnt_uf--;
    }
    return u;
}

//Tarjan算法

bool vis[MAXN];

int stasiz=0;
int ufe[MAXN][3];
int u,f,e;

void push(int p,int fp,int ed){
    stasiz++;//申请空间
    ufe[stasiz][0]=p;
    ufe[stasiz][1]=fp;
    ufe[stasiz][2]=ed;
}

void pop(){
    u=ufe[stasiz][0];
    f=ufe[stasiz][1];
    e=ufe[stasiz][2];
    stasiz--;//撤销空间
}

void Tarjan(int root){
    stasiz=0;
    push(root,0,-1);
    while(stasiz>0){
        pop();
        //未进行遍历
        if(e==-1){
            //初次抵达该节点
            vis[u]=true;
            e=head[u];//获取头边
        }else{//遍历该节点的下一条边
            e=next[e];
        }
        if(e!=0){
            //存在剩余有效边
            push(u,f,e);//把自身入栈,待继续处理
            if(to[e]!=f){//孩子!=父亲,入栈,待处理
                //此时孩子位于父亲上,优先级更高
                push(to[e],u,-1);
            }
        }else{
            //不存在剩余有效边
            //进入回溯,处理查询
            for(int eq=head_q[u];eq>0;eq=next_q[eq]){
                int v=to_q[eq];
                if(vis[v]){
                    //u的问题,看v是否到达过
                    ans[idx_q[eq]]=find(v);
                }
            }
            //回溯标记
            father[u]=f;
        }
    }
}

void build(int n){
    for(int i=0;i<=n;i++){
        father[i]=i;
    }
    cnt_q=cnt=0;
    stasiz=0;
    fill(vis,vis+n+1,false);
    fill(head,head+n+1,0);
    fill(head_q,head_q+n+1,0);
}

int main(){

    using namespace std;

    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n,m,s;
    cin>>n>>m>>s;
    build(n);
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        add_edge(u,v);
        add_edge(v,u);
    }
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        add_query(u,v,i);
        add_query(v,u,i);
    }
    Tarjan(s);
    for(int i=1;i<=m;i++){
        cout<<ans[i]<<'\n';
    }

    return 0;
}
