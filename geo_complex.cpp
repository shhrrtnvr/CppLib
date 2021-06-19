#include <bits/stdc++.h>
using namespace std;

//datatype definitions
typedef double T;
typedef complex<T> pt;
#define x real()
#define y imag()

//output helpful for debugging
ostream& operator<< (ostream& os, pt p) { return os << "(" << p.x << ", " << p.y << ")"; }

//translation, rotation and transformation
pt translate(pt v, pt p) { return v+p; } //translate p by v
pt scale(pt c, T factor, pt p) { return c + (p-c) * factor; }
pt rotate(pt p, T angle) { return p * polar(T(1), angle); }
pt perp(pt p) { return {-p.y, p.x}; }
pt linearTransform(pt p, pt q, pt r, pt fp, pt fq) { return fp + (r-p) * (fq-fp) / (q-p); }

//dot, cross and derivatives
T dot(pt v, pt w) { return (conj(v)*w).x; }
T cross(pt v, pt w) { return (conj(v)*w).y; }
tuple<T, T> dotcross(pt v, pt w) { pt p = conj(v)*w; return {p.x, p.y}; }

bool isPerp(pt v, pt w) { return dot(v, w) == 0; }
double angle(pt v, pt w) { 
    return acos(clamp(dot(v, w) / abs(v) / abs(w), T(-1), T(1))); 
} 
T orient(pt a, pt b, pt c) { return cross(b-a, c-a); }
bool inAngle(pt a, pt b, pt c, pt p) {
    assert(orient(a, b, c) != 0);
    if (orient(a, b, c) < 0) swap(b, c);
    return orient(a, b, p) >= 0 && orient(a, c, p) <= 0;
}
double orientedAngle(pt a, pt b, pt c) { 
    return orient(a, b, c) >= 0 ? angle(b-a, c-a) : 2*M_PI-angle(b-a, c-a);
}

bool isConvex(vector<pt> p) {
    bool hasPos = false, hasNeg = false;
    for (int i = 0, n=p.size(); i < n; i++) {
        int o = orient(p[i], p[(i+1) % n], p[(i+2) % n]);
        if (o > 0) hasPos = true;
        else if (o < 0) hasNeg = true;
    }
    return !(hasNeg && hasPos);
}

//Polar Sort 
bool half(pt p) {
    assert(p.x != 0 && p.y != 0);
    return p.y > 0 || (p.y == 0 && p.x < 0);
}
void polarSort(vector<pt> &v) {
    sort(v.begin(), v.end(), [](pt v, pt w) {
        return make_tuple(half(v), 0) < make_tuple(half(w), cross(v, w));
    });
}

struct line {
    pt v; T c;
    line (pt v, T c) : v(v), c(c) {}
    line (T a, T b, T c) : v({b, -a}), c(c) {}
    line (pt p, pt q) : v(q-p), c(cross(v, p)) {}

    T side (pt p) { return cross(v, p) - c; }
    double dist (pt p) { return abs(side(p)) / abs(v); }
    double sqDist (pt p) { return side(p) * side(p) / dot(v, v); }
    line perpThrough (pt p) { return {p, p + perp(v)}; }
    bool cmpProj (pt p, pt q) { return dot(v, p) < dot(v, q); }
    line translate (pt t) { return {v, c + cross(v, t)}; }
    line shiftLeft(T dist) { return {v, c + dist * abs(v)}; }
    pt proj(pt p) { return p - perp(v) * side(p) / dot(v, v); }
    pt refl(pt p) { return p - perp(v) * T(2) * side(p) / dot(v, v); }
};

bool intersect(line l1, line l2, pt &out) {
    T d = cross(l1.v, l2.v);
    if (d == 0) return false;
    out = (l2.v * l1.c - l1.v * l2.c) / d;
    return true;
}

//bisector of angle
line bisector(line l1, line l2, bool interior) {  
    assert(cross(l1.v, l2.v) != 0);
    T sign = interior ? T(1) : T(-1);
    return { l2.v / abs(l2.v) + l1.v / abs(l1.v) * sign,
            l2.c / abs(l2.v) + l1.c / abs(l1.v) * sign };
}

// Segment functions
bool inDisk(pt a, pt b, pt p) { return dot(a-p, b-p) <= 0; }
bool onSegment(pt a, pt b, pt p) {
    return orient(a, b, p) == 0 && inDisk(a, b, p);
}

bool properIntersect(pt a, pt b, pt c, pt d, pt &out) {
    T oa = orient(c, d, a);
    T ob = orient(c, d, b);
    T oc = orient(a, b, c);
    T od = orient(a, b, d);
    if (oa * ob < 0 && oc * od < 0) {
        out = (a*ob - b*oa) / (ob - oa);
        return true;
    }
    return false;
}

//segment - point distance
double segPoint(pt a, pt b, pt p) {
    if (a != b) {
        line l(a, b);
        if (l.cmpProj(a, p) && l.cmpProj(p, b)) return l.dist(p);
    }
    return min(abs(p-a), abs(p-b));
}
//segment - segment distance
double segSeg(pt a, pt b, pt c, pt d) {
    pt dummy;
    if (properIntersect(a, b, c, d, dummy)) return 0;
    return min({segPoint(a, b, c), segPoint(a, b, d), segPoint(c, d, a), segPoint(c, d, b)}) ;
}

//Polygons
double areaTriangle(pt a, pt b, pt c) { return abs(cross(b-a, c-a)) / 2.0;}

double areaPolygon(vector<pt> p) {
    double area = 0.0;
    for (int i = 0, n = p.size(); i < n; i++) area += cross(p[i], p[(i+1)%n]);
    return area;
}

bool above(pt a, pt p) { return p.y >= a.y; }
bool crossesRay(pt a, pt p, pt q) {return (above(a, q) - above(a, p) ) * orient(a, p, q) > 0;}
bool inPolygon(vector<pt> p, pt a, bool strict = true) {
    int numOfCrossings = 0;
    for (int i = 0, n = p.size(); i < n; i++) {
        if (onSegment(p[i], p[(i+1)%n], a)) return !strict;
        numOfCrossings += crossesRay(a, p[i], p[(i+1)%n]);
    }
    return numOfCrossings & 1;
}

// Winding number
double angleTravelled(pt a, pt p, pt q) {
    double amplitude = angle(p-a, p-q);
    return orient(a, p, q) > 0 ? amplitude : - amplitude;
}
int windingNumber (vector<pt> p, pt a) {
    // undefined if a is on the polygon
    double amplitude = 0;
    for (int i = 0, n = p.size(); i < n; i++) amplitude += angleTravelled(a, p[i], p[(i+1) % n]);
    return round(amplitude / (2*M_PI));
}

// Circle
pt circumCenter(pt a, pt b, pt c) {
    b -= a, c -= a; assert(cross(b, c) != 0); //no cirumcircle if A, B, C aligned
    return a + perp(b * abs(c * c) - c * abs(b * b)) / cross(b, c) / T(2);
}
int circleLine(pt o, double r, line l, pair<pt, pt> &out) {
    double h2 = r*r - l.sqDist(o);
    if (h2 >= 0) {
        pt p = l.proj(o);
        pt h = l.v * sqrt(h2) / abs(l.v);
        out = {p-h, p+h};
    }
    int sgn = (double(0) < h2) - (h2 < double(0));
    return 1+sgn;
}
int circleCircle(pt o1, double r1, pt o2, double r2, pair<pt, pt> &out) {
    pt d = o2-o1; double d2 = abs(d*d);
    if (d2 == 0) {assert(r1 != r2); return 0;}
    double pd = (d2 + r1*r1 - r2*r2)/2;
    double h2 = r1*r1 - pd*pd/d2;
    if (h2 >= 0) {
        pt p = o1 + d*pd/d2, h = perp(d) * sqrt(h2 / d2);
        out = {p-h, p+h};
    }
    int sgn = (double(0) < h2) - (h2 < double(0));
    return 1+sgn;
}
int tangents(pt o1, double r1, pt o2, double r2, bool inner, vector<pair<pt, pt> > &out) {
    if (inner) r2 = -r2;
    pt d = o2-o1;
    double dr = r1-r2, d2 = abs(d*d), h2 = d2-dr*dr;
    if (d2 == 0 || h2 < 0) {assert(h2 != 0); return 0;}
    for (double sign : {-1, 1}) {
        pt v = (d*dr + perp(d) * sqrt(h2) * sign) / d2;
        out.push_back({o1 + v*r1, o2 + v*r2});
    }
    return 1 + (h2 > 0);
}


int main() {
    pt a{1, 2}, b{-3, 1}, e{0, 0};
    cout << a+b << ", " << a*T(-1)<<endl;
    cout << abs(a) << ", " << arg(a)<<endl;
    cout << polar(2.0, -M_PI/4) << endl;

    auto [d, c] = dotcross(a, b);
    cout << d << " " << c <<endl;

    cout << dot(a, b) << " " << cross(a, b) << endl;

    cout << angle(a, b) << " " << isPerp(a, b) << endl;
    
    cout<<"Circum center: "<< circumCenter(a, b, e)<<endl;

    return 0;
}