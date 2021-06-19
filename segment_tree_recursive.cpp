#include<bits/stdc++.h>
using namespace std;
#define MX 200005
const int INF = 0x3f3f3f3f;
int n, st[4*MX];

int build(int a[], int v, int tl, int tr) {
    if (tl == tr) return st[v] = a[tl];
    int tm = (tl + tr) >> 1;
    return st[v] = min(build(a, v<<1, tl, tm), build(a, (v<<1)+1, tm+1, tr));    
}

int query(int v, int tl, int tr, int l, int r) {
    if (l > r) return INF;
    if (l == tl && r == tr)  return st[v];
    int tm = (tl + tr) >> 1;
    return min(query(v<<1, tl, tm, l, min(r, tm)),
             query((v<<1)+1, tm+1, tr, max(l, tm+1), r));
}

void update(int v, int tl, int tr, int pos, int new_val) {
    if (tl == tr) {
        st[v] = new_val;
        return;
    }
    int tm = (tl + tr) >> 1;
    if (pos <= tm) update(v<<1, tl, tm, pos, new_val);
    else update((v<<1)+1, tm+1, tr, pos, new_val);
    st[v] = min(st[(v<<1)], st[(v<<1)+1]);
}


int main() {
    int q;
    scanf("%d %d", &n, &q);
    int a[n];
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    build(a, 1, 0, n-1);
    for (int i = 0; i < q; i++) {
        int op;
        scanf("%d", &op);
        switch(op){
            case 1:
                int k, u;
                scanf("%d %d", &k, &u);
                update(1, 0, n-1, k-1, u);
                break;
            case 2:
                int a, b;
                scanf("%d %d", &a, &b);
                printf("%d\n", query(1, 0, n-1, a-1, b-1));
                break;
        }
    }
}