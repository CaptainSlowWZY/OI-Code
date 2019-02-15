#include <cstdio>
#include <cmath>
#include <algorithm>

typedef double real;
// you should set EPS as required
const real EPS = 1e-8;

struct Point;
typedef Point Vector;
struct Point {
	real x, y;
// constructor
	Point (real x_ = 0, real y_ = 0) : x(x_), y(y_) {}
// operation
	Vector operator+(const Vector & v) const { return Vector(x + v.x, y + v.y); }
	Vector operator-(const Vector & v) const { return Vector(x - v.x, y - v.y); }
	Vector operator*(real k) const { return Vector(x * k, y * k); }
	real operator*(const Vector & v) const { return x * v.y - y * v.x; }
    void in() { scanf("%lf%lf", &x, &y); }
};

inline int sign(real x) {
	return fabs(x) < EPS ? 0 : (x < 0 ? -1 : 1);
}
inline bool seg_intersec(const Point & A1, const Point & A2, const Point & B1, const Point & B2) {
	return std::min(A1.x, A2.x) <= std::max(B1.x, B2.x) && std::min(B1.x, B2.x) <= std::max(A1.x, A2.x) &&
		std::min(A1.y, A2.y) <= std::max(B1.y, B2.y) && std::min(B1.y, B2.y) <= std::max(A1.y, A2.y) &&
		sign((A2 - A1) * (B1 - A1)) * sign((A2 - A1) * (B2 - A1)) <= 0 &&
		sign((B2 - B1) * (A1 - B1)) * sign((B2 - B1) * (A2 - B1)) <= 0;
}

int main() {
    int N;
    scanf("%d", &N);
    for (Point sp, ep; N--; ) {
        sp.in(), ep.in();
        double x1, y1, x2, y2;
        scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
        if (x1 > x2) std::swap(x1, x2);
        if (y1 > y2) std::swap(y1, y2);
        Point lt(x1, y2), lb(x1, y1), rt(x2, y2), rb(x2, y1);
        if (seg_intersec(lt, rt, sp, ep) || seg_intersec(lt, lb, sp, ep) ||
            seg_intersec(lb, rb, sp, ep) || seg_intersec(rt, rb, sp, ep) ||
            x1 <= sp.x && sp.x <= x2 && x1 <= ep.x && ep.x <= x2 &&
            y1 <= sp.y && sp.y <= y2 && y1 <= ep.y && ep.y <= y2) puts("T");
        else puts("F");
    }
    return 0;
}