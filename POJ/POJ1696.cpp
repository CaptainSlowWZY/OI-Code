#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <vector>

typedef double real;

const int MAXN = 55;
const real EPS = 1e-8;

inline int sign(real x) {
	return fabs(x) < EPS ? 0 : (x < 0 ? -1 : 1);
}

struct Point;
typedef Point Vector;
struct Point {
	real x, y, ang;
	int id;
	Point (real x_ = 0, real y_ = 0, int id_ = 0) : x(x_), y(y_), id(id_) {}
	Vector operator+(const Vector & v) const { return Vector(x + v.x, y + v.y); }
	Vector operator-(const Vector & v) const { return Vector(x - v.x, y - v.y); }
	Vector operator*(real k) const { return Vector(x * k, y * k); }
	real operator*(const Vector & v) const { return x * v.y - y * v.x; }
 	bool operator<(const Point & p) const {
		return ang < p.ang;
	}
} P[MAXN], S[MAXN];

int used[MAXN];

int main() {
	int t, n;
	for (scanf("%d", &t); t--; ) {
		scanf("%d", &n);
		int r = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d%lf%lf", &P[i].id, &P[i].x, &P[i].y);
			if (P[i].y < P[r].y || !sign(P[i].y - P[r].y) && P[i].x > P[r].x) r = i;
		}

		std::swap(P[r], P[0]);
		for (int i = 1; i < n; i++) P[i].ang = atan2(P[i].y - P[0].y, P[i].x - P[0].x);
		std::sort(P + 1, P + n);
		
		memset(used, 0, sizeof used);
		std::vector<int> V;
		for (int top = 0; n > 0; ) {
			for (int i = 0; i < n; i++) {
				while (top > 1 && sign((S[top - 1] - S[top - 2]) * (P[i] - S[top - 2])) < 0)--top;
				S[top++] = P[i];
			}
			for (int i = 0; i < top; i++) {
				V.push_back(S[i].id);
				used[S[i].id] = 1;
			}
			S[0] = S[top - 1];
			top = 1;
			int n1 = 0;
			for (int i = 0; i < n; i++)
				if (!used[P[i].id]) {
					P[i].ang = atan2(P[i].y - S[0].y, P[i].x - S[0].x);
					P[n1++] = P[i];
				}
			n = n1;
			std::sort(P, P + n);
		}
		V.erase(std::unique(V.begin(), V.end()), V.end());
		printf("%d ", (int)V.size());
		for (int i = 0; i < (int)V.size(); i++) printf("%d ", V[i]);
		putchar('\n');
	}
	return 0;
}
