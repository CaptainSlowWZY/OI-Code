// Codeforces 886 F
#pragma GCC diagnostic error "-std=c++11"
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>

#ifdef DEBUG_MD
	#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define debug(format, ...) 0
#endif
#define pb push_back

struct Point;
typedef double real;
typedef Point Vector;

const real EPS = 1e-7;
const real INF = 1e14;
const int MAXN = 2005;

inline bool eql(real a, real b) { return fabs(a - b) < EPS; }
inline real sqr(real x) { return x * x; }

struct Point {
	real x, y;

	Point(real x_ = 0, real y_ = 0) : x(x_), y(y_) {}
	Vector operator+(const Vector & v) const { return Vector(x + v.x, y + v.y); }
	Vector operator*(real k) const { return Vector(x * k, y * k); }
	Vector operator/(real k) const { return Vector(x / k, y / k); }
	bool operator==(const Point & p) const { return eql(x, p.x) && eql(y, p.y); }
	real prjc(double k) const { return (x + k * y) / (1 + sqr(k)); }
	friend void scan(Point & p) { scanf("%lf%lf", &p.x, &p.y); }
	friend bool symmetric(const Point & p1, const Point & p2, const Point & m) {
		return p1 + p2 == m * 2;
	}
} cntr, A[MAXN], B[MAXN];

int N, totp, ans, flag[MAXN];
double X[MAXN];
std::vector<double> L;

void check_y();
void check_line(real k);

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scan(A[i]);
		cntr = cntr + A[i];
	}

	cntr = cntr / N;
	for (int i = 0; i < N; i++)
		for (int j = i + 1; j < N; j++)
			if (symmetric(A[i], A[j], cntr)) flag[i] = flag[j] = 1;
	for (int i = 0; i < N; i++) if (!flag[i]) B[totp++] = A[i];
	if (totp <= 2) return puts("-1"), 0;

	debug("totp=%d\n", totp);
	check_y();
	for (int i = 0; i < totp; i++)
		for (int j = i + 1; j < totp; j++) {
			if (eql(2 * cntr.y - B[i].y - B[j].y, 0)) continue;
			L.pb((B[i].x + B[j].x - 2 * cntr.x) / (2 * cntr.y - B[i].y - B[j].y));
		}
	std::sort(L.begin(), L.end());
	L.pb(INF);
#ifdef DEBUG_MD
	for (auto k : L) debug(" y=%.2fx\n", k);
#endif
	real now = INF;
	int cnt = 0;
	for (auto k : L) {
		if (eql(k, now)) { ++cnt; continue; }
		if (cnt && cnt * 2 + 1 >= totp) check_line(now);
		now = k, cnt = 1;
	}

	printf("%d\n", ans);
	return 0;
}

void check_y() {
	for (int i = 0; i < totp; i++) X[i] = B[i].y;
	std::sort(X, X + totp);
	real mid = cntr.y * 2;
	for (int i = 0; i + i < totp; i++)
		if (!eql(X[i] + X[totp - i - 1], mid)) return;
	++ans;
}

void check_line(real k) {
	debug(" line : y = %.2fx\n", k);

	for (int i = 0; i < totp; i++) X[i] = B[i].prjc(k);
	std::sort(X, X + totp);
	real mid = cntr.prjc(k) * 2;
	for (int i = 0; i + i < totp; i++)
		if (!eql(X[i] + X[totp - i - 1], mid)) return;
	++ans;
}
