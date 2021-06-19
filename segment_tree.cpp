#include <bits/stdc++.h>
using namespace std;
#define MX 200005

long long st[2*MX];
int n;

void build(long long a[]){
    for (int i = n, j = 0; j < n; i++, j++) st[i] = a[j];
    for (int i = n-1; i > 0; i--) st[i] = st[i<<1] + st[(i<<1)+1];
}

void update(int i, long long val) {
    i += n;
    st[i] = val;
    for (i /= 2; i >= 1; i /= 2) st[i] = st[i<<1] + st[(i<<1)+1];
}

long long query(int l, int r){
    long long ans = 0;
    for(l+=n, r+=n; l <= r; l >>= 1, r >>= 1){
        if (l&1) ans += st[l++];
        if (!(r&1)) ans += st[r--];
    }
    return ans;
}


//1648 solution in segment tree
int main() {
    int q;
    scanf("%d %d", &n, &q);
    for (long long i = 0, x; i < n; i++) {
        scanf("%lld", &x);
        update(i, x);
    }
    for (int i = 0, op, k, u; i < q; i++) {
        scanf("%d", &op);
        switch(op) {
            case 1:
                int k, u;
                scanf("%d %d", &k, &u);
                update(k-1, u);
                break;
            case 2:
                int a, b;
                scanf("%d %d", &a, &b);
                printf("%lld\n", query(a-1, b-1));
                break;
        }
    }
    return 0;
}