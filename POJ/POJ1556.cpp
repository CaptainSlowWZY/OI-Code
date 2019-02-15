#include <cstdio>
#include <cmath>
#include <algorithm>

const int MAXP = 80, MAXS = 70;
const double EPS = 1e-8, INF = 1e9;

inline double sqr(double x) { return x * x; }

struct Point;
typedef Point Vector;
struct Point {
	double x, y;
	Point (double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
	Vector operator+(const Vector & v) const { return Vector(x + v.x, y + v.y); }
	Vector operator-(const Vector & v) const { return Vector(x - v.x, y - v.y); }
	Vector operator*(double k) const { return Vector(x * k, y * k); }
	double operator*(const Vector & v) const { return x * v.y - y * v.x; }
	friend double dist(const Point & p1, const Point & p2) {
		return sqrt(sqr(p1.x - p2.x) + sqr(p1.y - p2.y));
	}
} P[MAXP];
struct Segmt {
	Point ep[2];
	Segmt() {}
	Segmt(const Point & p1, const Point & p2) {
		ep[0] = p1, ep[1] = p2;
	}
} S[MAXS];

int N, tots, totp;
double D[80][80];

inline int sign(double x) {
	return fabs(x) < EPS ? 0 : (x < 0 ? -1 : 1);
}
inline bool seg_proper_intersec(const Point & A1, const Point & A2, const Point & B1, const Point & B2) {
	return std::min(A1.x, A2.x) < std::max(B1.x, B2.x) && std::min(B1.x, B2.x) < std::max(A1.x, A2.x) &&
		std::min(A1.y, A2.y) < std::max(B1.y, B2.y) && std::min(B1.y, B2.y) < std::max(A1.y, A2.y) &&
		sign((A2 - A1) * (B1 - A1)) * sign((A2 - A1) * (B2 - A1)) < 0 &&
		sign((B2 - B1) * (A1 - B1)) * sign((B2 - B1) * (A2 - B1)) < 0;
}
void solve();

int main() {
	while (scanf("%d", &N) == 1 && ~N) solve();

	return 0;
}



bool dirct(const Point & p1, const Point & p2) {
	for (int i = 0; i < tots; i++)
		if (seg_proper_intersec(S[i].ep[0], S[i].ep[1], p1, p2)) return false;
	return true;
}

void solve() {
	totp = tots = 0;
	P[totp++] = Point(0, 5);
	for (int i = 0; i < N; i++) {
		double xi, yi, prey = 0;
		scanf("%lf", &xi);
		for (int j = 0; j < 4; j++) {
			scanf("%lf", &yi);
			P[totp++] = Point(xi, yi);
			if (j & 1 ^ 1) S[tots++] = Segmt(Point(xi, prey), Point(xi, yi));
			prey = yi;
		}
		S[tots++] = Segmt(Point(xi, yi), Point(xi, 10));
	}
	P[totp++] = Point(10, 5);

	for (int i = 0; i < totp; i++) {
		D[i][i] = 0;
		for (int j = i + 1; j < totp; j++)
			if (dirct(P[i], P[j])) D[i][j] = D[j][i] = dist(P[i], P[j]);
			else D[i][j] = D[j][i] = INF;
	}
	for (int k = 0; k < totp; k++)
		for (int i = 0; i < totp; i++)
			for (int j = 0; j < totp; j++)
				D[i][j] = std::min(D[i][j], D[i][k] + D[k][j]);
	printf("%.2lf\n", D[0][totp - 1]);
}
