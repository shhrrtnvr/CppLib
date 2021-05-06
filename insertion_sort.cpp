#include <bits/stdc++.h>
using namespace std;

void insertion_sort(int *a, int l, int r) {
    for (int i = l+1; i <= r; i++) {
        int j = i;
        while (j > 0 && a[j-1] > a[j]) {
            swap(a[j-1], a[j]);
            j--;
        }
    }
}


int main() {
    mt19937 rng;
    int perm[10];
    for (int i = 0; i < 10; i++) perm[i] = i;
    shuffle(perm, perm+10, rng);
    for (auto v: perm) cout<<v<<" ";cout<<endl;
    insertion_sort(perm, 0, 9);
    for (auto v: perm) cout<<v<<" ";cout<<endl;
}