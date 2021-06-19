#include <bits/stdc++.h>
using namespace std;

template <typename T> int sgn (T x) { return ( T(0) < x ) - ( x < T(0) ); }

typedef double T;
struct pt{
    T x, y;
    pt operator+ (pt p) { return {x + p.x, y + p.y}; }
    pt operator- (pt p) { return {x - p.x, y - p.y}; }
    pt operator* (T d) { return {x * d, y * d}; }
    pt operator/ (T d) { return {x / d, y / d}; }
};
ostream& operator<< (ostream& os, pt p) { return os << "(" << p.x << ", " << p.y << ")"; }

T sq (pt p) { return p.x * p.x + p.y * p.y; }
double abs (pt p) { return sqrt(sq(p)); }


pt translate(pt v, pt p) { return v+p; } //translate p by v



int main() {
    pt a{1, 2}, b{3, 4};
    cout << a+b << ", " << a*-1<<endl;
    cout << a << " = " << abs(a)<<endl;
    return 0;
}
