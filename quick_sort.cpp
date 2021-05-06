#include <bits/stdc++.h>
using namespace std;

int partition(int *a, int l, int r) {
    int j = l-1;
    for (int i = l; i < r; i++) 
        if (a[i] < a[r]) swap(a[i], a[++j]);
    
    swap(a[++j], a[r]);
    return j;
}

void quick_sort(int *a, int l, int r) {
    if (l >= r) return;
    int p = partition(a, l, r);
    quick_sort(a, l, p-1);
    quick_sort(a, p+1, r);
}


int main() {
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    int perm[10];
    for (int i = 0; i < 10; i++) perm[i] = i;
    shuffle(perm, perm+10, rng);
    for (auto v: perm) cout<<v<<" ";cout<<endl;
    quick_sort(perm, 0, 9);
    for (auto v: perm) cout<<v<<" ";cout<<endl;
}