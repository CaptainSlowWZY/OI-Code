#include <cstdio>
#include <cmath>
#include <algorithm>

const int MAXN = 25;
const double EPS = 1e-8, INF = 1e10;

struct Point;
typedef Point Vector;
struct Point {
	double x, y;

	Point(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
	Vector operator+(const Point & p) const { return Vector(x + p.x, y + p.y); }
	Vector operator-(const Point & p) const { return Vector(x - p.x, y - p.y); }
	Vector operator*(double k) const { return Vector(x * k, y * k); }
	double operator*(const Point & p) const { return x * p.y - y * p.x; }
	void in() {
		scanf("%lf%lf", &x, &y);
	}
	void out() const {
		printf(" (%.2f, %.2f)\n", x, y);
	}
} P[MAXN << 1];
struct Line {
	Point p;
	Vector drc;

	Line() {}
	Line(const Point & p_, const Vector & v_) : p(p_), drc(v_) {}

	friend Point intersec(const Line & l1, const Line & l2) {
		return l1.p + l1.drc * ((l2.drc * (l1.p - l2.p)) / (l1.drc * l2.drc));
	}
};

inline int sign(double x) {
	return fabs(x) < EPS ? 0 : (x < 0 ? -1 : 1);
}
inline bool seg_proper_intersec(const Point & A1, const Point & A2, const Point & B1, const Point & B2) {
	using std::min;
	using std::max;
	return min(A1.x, A2.x) < max(B1.x, B2.x) && min(B1.x, B2.x) < max(A1.x, A2.x) &&
			min(A1.y, A2.y) < max(B1.y, B2.y) && min(B1.y, B2.y) < max(A1.y, A2.y) &&
			sign((A2 - A1) * (B1 - A1)) * sign((A2 - A1) * (B2 - A1)) < 0 &&
			sign((B2 - B1) * (A1 - B1)) * sign((B2 - B1) * (A2 - B1)) < 0;
}

int main() {
	for (int N; scanf("%d", &N) == 1 && N; ) {
		for (int i = 0; i < N; i++) {
			P[i].in();
			P[i + N] = Point(P[i].x, P[i].y - 1);
		}

		Line le(P[N - 1], Vector(0, -1)), ls(P[0], Vector(0, -1));
		int flag = 1;
		double ans = P[0].x;
//		printf(" N = %d\n", N);
		for (int i = 0; i < N * 2 && flag; i++)
			for (int j = i + 1; j < N * 2; j++) {
				if (i + N == j) continue;
				Point s = P[i], e = P[j];
				if (s.x > e.x) std::swap(s, e);
				Point sx = intersec(ls, Line(s, e - s));
				if (!sign(sx.y - P[0].y) || !sign(sx.y + 1.0 - P[0].y)) {
				}
				else if (sx.y > P[0].y || sx.y + 1.0 < P[0].y) continue;
				s = sx;
				e = intersec(le, Line(s, e - s));
#ifdef DEBUG				
				printf("##### i = %d, j = %d #####\n", i, j);
				printf(" start : ");
				s.out();
				printf(" end   : ");
				e.out();
#endif
				flag = 0;
				for (int k = 1; k < N; k++) {
#ifdef DEBUG					
					printf(" pre-checking %d\n", k);
					printf("  CHECK with:\n");
					P[k - 1].out();
					P[k].out();
#endif					
					if (seg_proper_intersec(P[k - 1], P[k], s, e)) {
#ifdef DEBUG						
						printf("  find! (upper)\n  e   : ");
#endif						
						e = intersec(Line(P[k - 1], P[k] - P[k - 1]), Line(s, e - s));
#ifdef DEBUG						
						e.out();
#endif						
						flag = 1;
					}
#ifdef DEBUG						
					printf("  CHECK with:\n");
					P[N + k - 1].out();
					P[N + k].out();
#endif					
					if (seg_proper_intersec(P[N + k - 1], P[N + k], s, e)) {
#ifdef DEBUG						
						printf("  find! (bottem)\n  e   : ");
#endif						
						e = intersec(Line(P[N + k - 1], P[N + k] - P[N + k - 1]), Line(s, e - s));
#ifdef DEBUG						
						e.out();
#endif						
						flag = 1;
					}
				}
#ifdef DEBUG				
				printf("After check:\n start : ");
				s.out();
				printf(" end   : ");
				e.out();
#endif				
				for (int k = 1; k + 1 < N && e.x >= P[k].x; k++) {
					Point q = intersec(Line(s, Vector(e - s)), Line(P[k], Vector(0, -1)));
#ifdef DEBUG
					printf(" checking %d\n q    : ", k);
					q.out();
					printf("  CHECK with:\n");
					P[k].out();
#endif
					if (!sign(q.y - P[k].y) || !sign(q.y + 1.0 - P[k].y)) {
						// e.x = std::min(e.x, P[k].x), flag = 1;
						continue;
					}
					if (q.y > P[k].y || q.y + 1.0 < P[k].y) {
						e.x = P[k - 1].x, flag = 1;
						break;
					}
				}
				if (!flag) {
					Point ex = intersec(Line(s, Vector(e - s)), le);
					if (!sign(ex.y - P[N - 1].y) || !sign(ex.y + 1.0 - P[N - 1].y)) {
#ifdef DEBUG
						puts("***** LOLOLO *****");
#endif
						break;
					}
					if (ex.y > P[N - 1].y || ex.y + 1.0 < P[N - 1].y) {
						for (int k = N - 2; k >= 0; k--) {
							ex = intersec(Line(s, Vector(e - s)), Line(P[k], Vector(0, -1)));
							if (!sign(ex.y - P[k].y) || !sign(ex.y + 1.0 - P[k].y)) {
								e = ex, flag = 1;
								break;
							}
							if (e.y > P[k].y || ex.y + 1.0 < P[k].y) continue;
							else {
								e = ex, flag = 1;
								break;
							}
						}
					}
					else  {
						break;
#ifdef DEBUG
						puts("***** LOLOLO *****");
#endif
					}
				}
#ifdef DEBUG
				printf(" e.x = %.2lf, ans = %.2lf\n\n", e.x, ans);
#endif			
				ans = std::max(ans, e.x);
#ifdef DEBUG
				printf(" UPD ans = %.2lf\n\n", ans);
#endif				
			}
		if (!flag) puts("Through all the pipe.");
		else printf("%.2f\n", ans);
	}
}
