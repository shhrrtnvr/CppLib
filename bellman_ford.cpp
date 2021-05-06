#include <bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f
#define MX 100005

vector<tuple<int, int, long long > > EdgeList;
long long dist[MX];
int n, m;

bool bellman(int u) {
    memset(dist, INF, sizeof dist);
    const long long LLINF = dist[0];

    dist[u] = 0LL;
    for (int i = 1, updated = true; i < n && updated; i++) {
        updated = false;
        for (auto [u, v, w] : EdgeList) {
            if (dist[u] == LLINF) continue;  // u is still not reachable, so correct implementation **requires** to skip it
            if (dist[u]+w < dist[v]) { 
                dist[v] = min(LLINF, dist[u]+w); //necessary to limit distance to INF to avoid possible overflow
                updated = true;
            }
        }
    }

    // following code is needed only to check negative cycle
    for (auto [u, v, w] : EdgeList) {
        if (dist[u] == LLINF) continue;
        if (dist[u] + w < dist[v]) return false;
    }
    return true;
}

int main() {
    scanf("%d %d", &n, &m); // number of nodes and edges

    for (auto [i, u, v, w] = tuple{0, 0, 0, 0LL}; i < m; i++) { //input nodes
        scanf("%d %d %lld", &u, &v, &w);
        EdgeList.emplace_back(tuple{u, v, w});
    }

    bellman(1);
    //1 based index was used for testing
    for (int i = 1; i <= n; i++) printf("%lld ", dist[i]); printf("\n");

    return 0;
}