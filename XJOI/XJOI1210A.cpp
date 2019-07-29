#include <algorithm>
#include <cstdio>
#include <cmath>

typedef double DB;

const int kMaxn = 1e5 + 10;
const DB kEps = 1e-8;

DB A, B, D;
DB dis[kMaxn];
int n;

inline bool IsZero(double x) {
	return fabs(x) <= kEps;
}
inline DB Calc(DB a, DB b, DB x, DB y) {
	return a * x + b * y;
}
inline DB Dist(DB x, DB y, DB a, DB b) {
	return fabs(a * x + b * y) / sqrt(a * a + b * b);
}

int main() {
	scanf("%lf%lf%lf%d", &A, &B, &D, &n);
	double xi, yi;
	for (int i = 0; i < n; i++) {
		scanf("%lf%lf", &xi, &yi);
		if (Calc(A, B, xi, yi) >= 0)
			dis[i] = Dist(xi, yi, A, B);
		else
			dis[i] = -Dist(xi, yi, A, B);
	}

	std::sort(dis, dis + n);
	int l = 0, r = 0, ans = 0;
	for (D *= 2.0; r < n && dis[r] - dis[l] <= D; ++r);
	if (r == n) ans = n;
	for (; r < n; ) {
		for (; l + 1 < r && IsZero(dis[l] - dis[l + 1]); l++);
		for (++l; r < n && dis[r] - dis[l] <= D; ++r);
		ans = std::max(ans, r - l);
	}
	
	printf("%d\n", ans);
}
