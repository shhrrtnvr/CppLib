#include<bits/stdc++.h>
using namespace std;
#define MX 10000007
int a[MX];
int st[MX][26];   // st[i][j] = min( [i, i+2^j) )

int main() {
    int N, q;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) scanf("%d", &a[i]);
    for (int i = 0; i < N; i++) st[i][0] = a[i];
    int K = log2(N);
    for (int j = 1; j <= K; j++) 
        for (int i = 0; i + (1 << j) <= N; i++) 
            st[i][j] = min(st[i][j-1], st[i + (1<<(j-1))][j-1]);

    for (int l = 0; l < N; l++) {
        for(int r = 0; r < N; r++ ) {
            if (r < l) printf("    ");
            else {
                int k = log2(r-l+1);
                int res = min(st[l][k], st[r-(1<<k)+1][k]);
                printf("%3d ", res);
            }
        }
        printf("\n");
    }
}