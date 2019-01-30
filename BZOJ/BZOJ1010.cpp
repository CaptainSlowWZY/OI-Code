// BZOJ 1010
// HNOI 2008
#include <cstdio>

const int MAXN = 5e4 + 10;

typedef long long LL;

struct Point {
	LL x, y;
	Point(LL x_ = 0, LL y_ = 0) : x(x_), y(y_) {}
	Point operator-(const Point & p) const { return Point(x - p.x, y - p.y); }
	LL operator*(const Point & p) const { return x * p.y - y * p.x; }
	LL dp() const { return y - x * x; }
	friend int better(const Point & p1, const Point & p2, LL ci) {
		return p1.y - p2.y <= 2LL * ci * (p1.x - p2.x);
	}
} Q[MAXN];

int N, L;
LL DP[MAXN], SC[MAXN];

inline LL sqr(LL x) { return x * x; }

int main() {
	scanf("%d%d", &N, &L);
	for (int i = 1, Ci; i <= N; i++) {
		scanf("%d", &Ci);
		SC[i] = SC[i - 1] + Ci;
	}

	int hd = 0, tl = 0;
	Q[tl++] = Point(0, 0);
	for (int i = 1; i <= N; i++) {
		LL Ci = SC[i] + i - L - 1;
		while (hd + 1 < tl && better(Q[hd + 1], Q[hd], Ci)) ++hd;
		Point Pi(SC[i] + i, Q[hd].y - 2LL * Ci * Q[hd].x + sqr(Ci) + sqr(SC[i] + i));
		while (hd + 1 < tl && (Q[tl - 1] - Q[tl - 2]) * (Pi - Q[tl - 2]) <= 0) --tl;
		Q[tl++] = Pi;
	}

	printf("%lld\n", Q[tl - 1].dp());
	return 0;
}
