#include <cstdio>
#include <cmath>
#include <algorithm>

const double EPS = 1e-8;

struct Point;
typedef Point Vector;
struct Point {
	double x, y;
	Point(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
	Vector operator+(const Point & p) const {
		return Vector(x + p.x, y + p.y);
	}
	Vector operator-(const Point & p) const {
		return Vector(x - p.x, y - p.y);
	}
	double operator*(const Vector & v) const {
		return x * v.y - y * v.x;
	}
	Vector operator*(double k) const {
		return Vector(x * k, y * k);
	}
};
struct Line {
	Point p;
	Vector drc;
	Line() {}
	Line(const Point & p_, const Vector & d_) : p(p_), drc(d_) {}
	friend Point intersec(const Line & l1, const Line & l2) {
		Vector u = l1.p - l2.p;
		return l1.p + l1.drc * ((l2.drc * u) / (l1.drc * l2.drc));
	}
};

int N;

inline int sign(double x) {
	return fabs(x) < EPS ? 0 : (x < 0 ? -1 : 1);
}

int main() {
	for (int x1, y1, x2, y2, x3, y3, x4, y4; scanf("%d", &N) == 1; ) {
		puts("INTERSECTING LINES OUTPUT");
		for (int i = 0; i < N; i++) {
			scanf("%d%d%d%d%d%d%d%d", &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4);
			if (x1 > x2) std::swap(x1, x2), std::swap(y1, y2);
			if (x3 > x4) std::swap(x3, x4), std::swap(y3, y4);
			Vector v1(x2 - x1, y2 - y1), v2(x4 - x3, y4 - y3);
			if (!sign(v1 * v2)) {
				puts(sign(Vector(x3 - x2, y3 - y2) * Vector(x4 - x1, y4 - y1)) ? "NONE" : "LINE");
			}
			else {
				Point p = intersec(Line(Point(x1, y1), v1), Line(Point(x3, y3), v2));
				printf("POINT %.2lf %.2lf\n", p.x, p.y);
			}
		}
		puts("END OF OUTPUT");
	}

	return 0;
}
