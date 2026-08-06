//时间复杂度O(n^3),n是节点个数
//枚举bridge跳板一定要在最外侧！！！
const int MAXN=100;
const int INF=1e9;
int dist[MAXN+1][MAXN+1];
for(int bridge=1;bridge<=n;bridge++){
  for(int i=1;i<=n;i++){
    for(int j=1;j<=n;j++){
      dist[i][j]=min(dist[i][j],dist[i][bridge]+dist[bridge][j]);
    }
  }
}
