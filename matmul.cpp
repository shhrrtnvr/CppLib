#include <bits/stdc++.h>
using namespace std;
#define MOD 1000000007

struct matrix {
    int row, col, sz;
    long long *A;
    matrix(int n) : matrix(n,n) {}
    matrix(int n, int m) {
        row = n;
        col = m;
        sz = row*col;
        A = new long long int[sz];
    }
    matrix(matrix& m) {
        row = m.row;
        col = m.col;
        sz = row*col;
        A = new long long int[sz];
        for (int i = 0; i < sz; i++) A[i] = m.A[i];
    }
    void operator*= (matrix b) {
        assert(col == b.row);
        matrix a(row, col);
        for (int i = 0; i < sz; i++) a.A[i] = A[i];
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                A[i*col + j] = 0LL;
                for (int k = 0; k < col; k++) {
                    A[i*col + j]  += (1LL * a.A[i*a.col + k] * b.A[k*b.col + j])%MOD;
                    A[i*col + j] %= MOD;
                }
            }
        }
    }

    void make_eye() {
        assert(col == row);
        for (int i = 0; i < row; i++)
                A[i*row+i] = 1;
    }
    void print() {
        for (int r = 0; r < row; r++) {
            for (int c = 0; c < col; c++) {
                if (c) printf(" ");
                printf("%d", A[r*col + c]);
            }
            printf("\n");
        }
        printf("\n");
    }
    
};

 matrix pow(matrix a, int b) {
    matrix res(a.row, a.col);
    res.make_eye();
    while (b) {
        if (b & 1) res *= a;
        a *= a;
        b >>= 1;
    }
    return res;
}

int main() {
    matrix m1(6);
    for (int i = 0; i < 6; i++) m1.A[i] = 1;
    for (int i = 1; i < 6; i++) m1.A[i*m1.col + i - 1] = 1;

    matrix m2(m1.row); 
    int n;
    scanf("%d", &n); 
    m2 = pow(m1, n);  
    printf("%lld\n", m2.A[0]);
}