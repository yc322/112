#include <cstring>
#include <iostream>
using namespace std;

const int maxn = 105;
const int inf = 0x3f3f3f3f;
int dis[maxn];
bool vis[maxn];
int map_dis[maxn][maxn];
int n,m;//n the number of vertex

int dijkstra(int s, int t) {
    memset(vis, false, sizeof(vis));
    for (int i = 1; i <= n; ++i) {      //��ʼ�����㵽s��ľ���
        dis[i] = map_dis[s][i];
    }
    dis[s] = 0, vis[s] = true;

    for (int i = 0; i < n - 1; ++i) {   //��s������n-1����
        int u, tmin = inf;
        for (int j = 1; j <= n; ++j){   //��min{dis[]}
            if(!vis[j] && dis[j] < tmin){
                tmin = dis[j];
                u = j;
            }
        }
        // if(tmin == inf) return -1;   //�����·
        vis[u] = true;                  //����T����
        for (int v = 1; v <= n; ++v){   //�������ڵ�
            if(!vis[v] && dis[u] + map_dis[u][v] < dis[v]){
                dis[v] = dis[u] + map_dis[u][v];
            }
        }
    }
    return dis[t];
}

int main() {
    int a, b, c;
    while (cin >> n >> m, n || m) {
        memset(map_dis,inf,sizeof(map_dis));
        for (int i = 1; i <= m; ++i) {
            cin >> a >> b >> c;
            map_dis[a][b] = map_dis[b][a] = c;
        }
        cout << dijkstra(1,n) << endl;
    }
    return 0;
}
