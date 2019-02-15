#include <cstdio>
#include <cmath>
#include <algorithm>

const int MAXN = 105;
const double EPS = 1e-8;

struct Point;
typedef Point Vector;
struct Point {
	double x, y;
	Point(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
	Vector operator-(const Point & p) const {
		return Vector(x - p.x, y - p.y);
	}
	double operator*(const Point & p) const {
		return x * p.y - y * p.x;
	}
} S[MAXN][2];

int N;

inline int sign(double x) {
	return fabs(x) < EPS ? 0 : (x < 0 ? -1 : 1);
}
inline bool seg_intersec(const Point & L1, const Point & L2, const Point & S1, const Point & S2) {
	return sign((L1 - S1) * (L2 - S1)) * sign((L1 - S2) * (L2 - S2)) <= 0;
}
void solve();

int main() {
	int t;
	for (scanf("%d", &t); t--; ) solve();

	return 0;
}

bool judge(const Point & p1, const Point & p2) {
	if (!sign(p1.x - p2.x) && !sign(p1.y - p2.y)) return false;
	for (int i = 0; i < N; i++)
		if (!seg_intersec(p1, p2, S[i][0], S[i][1])) return false;
	return true;
}

void solve() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < 2; j++) scanf("%lf%lf", &S[i][j].x, &S[i][j].y);
	
	for (int i = 0; i < N; i++)
		for (int j = i; j < N; j++)
			if (judge(S[i][0], S[j][0]) || judge(S[i][0], S[j][1]) ||
				judge(S[i][1], S[j][0]) || judge(S[i][1], S[j][1])) {
				puts("Yes!");
				return;
			}
	puts("No!");
}
