#include <bits/stdc++.h>
using namespace std;
#define MX 200005
int n;
long long bit[MX];
void add(int i, long long delta) {
    for (; i < n; i |= (i+1)) bit[i] += delta;
    // following is 1 based indexed implementation
    // for (; i <= n; i += i&-i) bit[i] += delta;
}
long long query(int i) {
    return i < 0 ? 0LL : bit[i] + query((i&(i+1))-1);
    // 1 based indexed implementation
    // return i <= 0? 0LL : bit[i] + query(i - (i & -i));
}

int main() {
    scanf("%d %d", &n);
    long long a[n];
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
        add(i, a[i]);
    }
}