#include<bits/stdc++.h>
using namespace std;
using ll=long long;

//例题：https://www.luogu.com.cn/problem/P8779
//例题2：https://ac.nowcoder.com/acm/contest/133876/C

class solution_question01{
    
    private:

    const ll INF=1e18;
    const static int MAXN=1e5;
    int n,m,q;

    //带权并查集
    int father[MAXN+1];
    ll dist[MAXN+1];//dist[u]表示u->ru的距离,ru=father[u]
    int road[MAXN+1];//辅助路径压缩

    void initial()
    {
        for(int i=1;i<=n;i++)
        {
            father[i]=i;
            dist[i]=0;
        }
    }

    int find(int u)
    {
        int cnt=-1;
        while(u!=father[u])
        {
            road[++cnt]=u;
            u=father[u];
        }
        //路径压缩+dist修正
        while(cnt>=0)
        {
            dist[road[cnt]]=dist[father[road[cnt]]]+dist[road[cnt]];
            father[road[cnt--]]=u;
        }
        return u;
    }

    ll query(int u,int v)
    {
        if(find(u)==find(v))return dist[u]-dist[v];
        return -INF;
    }

    void merge(int u,int v,ll d)
    {
        int ru=find(u),rv=find(v);
        if(ru==rv)return;
        father[ru]=rv;
        //dist=dist[后]-dist[前]+d
        dist[ru]=dist[v]-dist[u]+d;
    }

    public:
    void solve()
    {
        ios::sync_with_stdio(false);
        cin.tie(0);
        cout.tie(0);
        cin>>n>>m>>q;
        initial();
        while(m--)
        {
            int l,r;
            ll d;
            cin>>l>>r>>d;
            merge(l-1,r,d);
        }
        while(q--)
        {
            int l,r;
            cin>>l>>r;
            ll res=query(l-1,r);
            if(res==-INF)cout<<"UNKNOWN"<<'\n';
            else cout<<res<<'\n';
        }
        return;
    }
};

class solution_question02{

    private:
    
    const static int MAXN=5e5;
    int father[MAXN+1];
    int road[MAXN+1];
    ll siz[MAXN+1];
    int idx=0;
    ll weight[MAXN+1];//每条鱼的大小
    ll need[MAXN+1];
    ll maxNeed[MAXN+1];

    const pair<int,int>dir[4]={{0,1},{0,-1},{1,0},{-1,0}};

    int find(int u){
        int cnt=-1;
        while(u!=father[u]){
            road[++cnt]=u;
            u=father[u];
        }
        while(cnt>=0){
            int p=road[cnt],fp=father[road[cnt]];
            maxNeed[p]=max(maxNeed[p],maxNeed[fp]);
            father[road[cnt]]=u;
            cnt--;
        }
        return u;
    }

    void merge(int u,int v){
        //有指向的并查集,u->v
        int ru=find(u),rv=find(v);
        if(ru==rv)return;
        siz[rv]+=siz[ru];
        father[ru]=rv;
        need[ru]=max(0LL,weight[rv]-siz[ru]+1);
        maxNeed[ru]=need[ru];
    }

    void build(int n){
        idx=0;
        for(int i=1;i<=n;i++){
            siz[i]=1;
            father[i]=i;
            need[i]=0;
            maxNeed[i]=0;
        }
    }

    public:

    void solve(){
        int n,m,q;
        cin>>n>>m>>q;
        build(n*m+1);
        //graph存鱼的编号
        vector<vector<int>>graph(n+1,vector<int>(m+1,-1));
        ll lst=0;
        while(q--){
            int opt;
            cin>>opt;
            int x,y,v;
            if(opt==1){
                cin>>x>>y>>v;
                x^=lst,y^=lst;
                graph[x][y]=++idx;
                weight[idx]=v;
                for(auto&[i,j]:dir){
                    int nx=x+i,ny=y+j;
                    if(nx<1||nx>n||ny<1||ny>m||
                        graph[nx][ny]==-1)continue;
                    int u=find(graph[nx][ny]);
                    merge(u,graph[x][y]);
                }
                lst=siz[find(graph[x][y])]-1;
                cout<<lst<<'\n';
            }else{
                cin>>x>>y;
                x^=lst,y^=lst;
                int cur=graph[x][y];
                find(cur);//获取正确的cost
                lst=max(0LL,maxNeed[cur]-weight[cur]);
                cout<<lst<<'\n';
            }
        }
        return;
    }

};



int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solution_question01 q1;
    solution_question02 q2;
    q1.solve();
    //q2.solve();
    return 0;
}
