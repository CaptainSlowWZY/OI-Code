#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
  
#define double long double
 
const int kMaxh = 5e5 + 10, kMaxn = 5e5 + 10;
const double kPie = acos(-1), kEPS = 1e-12;
  
inline int sign(double x) {
	return fabs(x) < kEPS ? 0 : (x < 0 ? -1 : 1);
}
inline double Sqr(double x) {
	return x * x;
}
  
struct Point;
typedef Point Vector;
struct Point {
	double x, y;
	Point(double x_ = 0, double y_ = 0) :
		x(x_), y(y_) {}
	double len2() const {
		return Sqr(x) + Sqr(y);
	}
	Vector operator+(const Vector & v) const {
		return Vector(x + v.x, y + v.y);
	}
	Vector operator-(const Vector & v) const {
		return Vector(x - v.x, y - v.y);
	}
	double operator*(const Vector & v) const {
		return x * v.y - y * v.x;
	}
	Vector operator*(double k) const {
		return Vector(x * k, y * k);
	}
	Vector operator/(double k) const {
		return Vector(x / k, y / k);
	}
	Vector rot90() const {
		return Vector(-y, x);
	}
	bool in_circle(const Point & o, double r2) const {
		return sign(r2 - (o - (*this)).len2()) >= 0;
	}
} P[kMaxn];
  
int N, H, R, D, C[kMaxh];
  
Point Circle(const Point & p1, const Point & p2, const Point & p3);
  
int main() {
	scanf("%d%d%d%d", &N, &H, &R, &D);
	for (int i = 0; i <= H; i++) scanf("%d", C + i);
	for (int i = 0; i < N; i++) scanf("%Lf%Lf", &P[i].x, &P[i].y);
  
	srand(time(NULL));
	std::random_shuffle(P, P + N);
	Point O = P[0];
	double r = 0;
	for (int i = 1; i < N; i++) {
		if (P[i].in_circle(O, r)) continue;
		O = (P[0] + P[i]) * 0.5;
		r = (O - P[0]).len2();
		for (int j = 1; j < i; j++)
			if (!P[j].in_circle(O, r)) {
				O = (P[i] + P[j]) * 0.5;
				r = (O - P[i]).len2();
				for (int k = 0; k < j; k++)
					if (!P[k].in_circle(O, r)) {
						O = Circle(P[i], P[j], P[k]);
						r = (O - P[i]).len2();
					}
			}
	}
  
	double ansc = std::max<double>(sqrt(r) - D, R) * C[0];
	int ansh = 0;
	for (int i = 1; i <= H && i <= D; i++) {
		double cost = std::max<double>(sqrt(r) - sqrt(Sqr(D) - Sqr(i)), R) * C[i];
		if (cost < ansc) {
			ansc = cost;
			ansh = i;
		}
	}
	  
	printf("%.10Lf\n%.10Lf %.10Lf %d %.10Lf\n", ansc, O.x, O.y, ansh, std::max<double>(sqrt(r) - sqrt(Sqr(D) - Sqr(ansh)), R));
	return 0;
}
  
Point LineIntersec(const Point & p1, const Vector & v1, const Point & p2, const Vector & v2) {
	return p1 + v1 * ((v2 * (p1 - p2))) / (v1 * v2);
}
  
Point Circle(const Point & p1, const Point & p2, const Point & p3) {
	if (!sign((p1 - p2) * (p3 - p2))) {
		double d = (p1 - p2).len2();
		Point o = (p1 + p2) * 0.5;
		if (sign((p1 - p3).len2() - d) > 0) {
			d = (p1 - p3).len2();
			o = (p1 + p3) * 0.5;
		}
		if (sign((p2 - p3).len2() - d) > 0) {
			d = (p2 - p3).len2();
			o = (p2 + p3) * 0.5;
		}
		return o;
	}
	Point m1 = (p1 + p2) * 0.5, m2 = (p1 + p3) * 0.5;
	Vector v1 = (p2 - p1).rot90(), v2 = (p3 - p1).rot90();
	return LineIntersec(m1, v1, m2, v2);
}