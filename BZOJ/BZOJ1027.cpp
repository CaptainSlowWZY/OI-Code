#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <utility>

#define x first
#define y second

typedef std::pair<double, double> Point;
typedef Point Vector;

const int MAXN = 505, INF = 0x3f3f3f3f;
const double EPS = 1e-10;

int N, M, D[MAXN][MAXN];
Point O[MAXN], P[MAXN];

inline int sign(double x) {
	return fabs(x) < EPS ? 0 : (x < 0 ? -1 : 1);
}
inline Vector operator-(const Point & p1, const Point & p2) {
	return Vector(p1.x - p2.x, p1.y - p2.y);
}
inline double operator*(const Point & p1, const Point & p2) {
	return p1.x * p2.y - p1.y * p2.x;
}
bool vaild(const Vector & v1, const Vector & v2) {
	double prd = v1 * v2;
	if (prd > 0) return true;
	if (!sign(prd)) return v2.x / v1.x <= 1.0;
	return false;
}

int main() {
	scanf("%d%d", &M, &N);
	for (int i = 0; i < M; i++) scanf("%lf%lf%*lf", &O[i].x, &O[i].y);
	for (int i = 0; i < N; i++) scanf("%lf%lf%*lf", &P[i].x, &P[i].y);

//	SPJ
	int flag = 1;
	for (int i = 0; i < M; i++)
		if (sign(O[i].x - O[0].x) || sign(O[i].y - O[0].y)) {
			flag = 0;
			break;
		}
	for (int i = 0; i < N; i++)
		if (sign(P[i].x - O[0].x) || sign(P[i].y - O[0].y)) {
			flag = 0;
			break;
		}
	if (flag) {
		puts("1");
		return 0;
	}

	memset(D, 0x3f, sizeof D);
	for (int i = 0; i < M; i++)
		for (int j = 0; j < M; j++) {
			if (i == j) continue;
			Vector v = O[i] - O[j];
			int fail = 0;
			for (int k = 0; k < N; k++)
				if (!vaild(v, P[k] - O[j])) {
					fail = 1;
					break;
				}
			if (!fail) D[j][i] = 1;
		}

	for (int k = 0; k < M; k++)
		for (int i = 0; i < M; i++)
			for (int j = 0; j < M; j++)
				D[i][j] = std::min(D[i][j], D[i][k] + D[k][j]);
	int ans = INF;
	for (int i = 0; i < M; i++) ans = std::min(ans, D[i][i]);
	printf("%d\n", ans == INF ? -1 : ans);

	return 0;
}
