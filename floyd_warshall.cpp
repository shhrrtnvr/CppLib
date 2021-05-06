#include <bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f
#define MX 1000

int n, m;
long long AdjMat[MX][MX];

void floydWarshall () {
    scanf("%d %d", &n, &m);

    //Matrix initailization
    //1 based indexing
    for (int i = 1; i <= n; i++) {
        memset(AdjMat[i], INF, sizeof AdjMat[i]); //All distance set to INF
        AdjMat[i][i] = 0LL;  //except distance to the node itself
    }

    //Input distaces
    long long w;
    for (int i = 0, u, v; i < m; i++) {
        scanf("%d %d %lld", &u, &v, &w); 
        AdjMat[u][v] = min(AdjMat[u][v], w); //storing minimum distance is important if multiple edges exits between two nodes
        //AdjMat[v][u] = min(AdjMat[v][u], w); //if bidirectional use this, but be careful of negative edge
    }

    //Algorithm 
    for (int k = 1; k <= n; k++) {   //k is the intermidiate node
        for (int i = 1; i <= n; i++) { 
            for (int j = 1; j <= n; j++) {
                AdjMat[i][j] = min(AdjMat[i][j], AdjMat[i][k] + AdjMat[k][j]);
            }
        }
    }
}

int main () {
    //test code
    floydWarshall();
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++)
            printf("%lld ", AdjMat[i][j]); 
        printf("\n");
    }
    return 0;
}