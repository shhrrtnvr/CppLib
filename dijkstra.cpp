#include <bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f
#define MX 1000005

int n, m;
long long dist[MX];
bool processed[MX];
vector < vector<tuple<int, long long> > >  AdjList;

void dijkstra(int u ) {
    priority_queue< 
        tuple<long long, int>, 
        vector<tuple<long long, int> >, 
        greater<tuple<long long, int> > 
    > pq;
    memset(dist, INF, sizeof dist);
    dist[u] = 0;
    pq.push(tuple {0, u});

    while(!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (processed[u]) continue;   //important as push in pq does not replace previous entry
        processed[u] = true;
        for (auto [v, w] : AdjList[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push(tuple {dist[v], v});
            }
        }
    }
}


int main() {
    scanf("%d %d", &n, &m); // number of nodes and edges

    AdjList.resize(n+1, vector<tuple<int, long long> >());
    for (auto [i, u, v, w] = tuple{0, 0, 0, 0LL}; i < m; i++) { //input nodes
        scanf("%d %d %lld", &u, &v, &w);
        AdjList[u].emplace_back(tuple {v, w});
    }

    dijkstra(1);
    //1 based index was used for testing
    for (int i = 1; i <= n; i++) printf("%lld ", dist[i]); printf("\n");

    return 0;
}