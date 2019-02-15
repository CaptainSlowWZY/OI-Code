// VJ 283647 A
#include <cstdio>
#include <algorithm>

const int MAXN = 5010;

struct Point;
typedef Point Vector;
struct Point {
	long long x, y;
	Point(long long x_ = 0, long long y_ = 0) : x(x_), y(y_) {}
	Vector operator-(const Point & p) const {
		return Point(x - p.x, y - p.y);
	}
	long long operator*(const Point & p) const {
		return x * p.y - y * p.x;
	}
} L[MAXN][2];

int N, M, x1, y1, x2, y2, cnt[MAXN];

int find(const Point & toy);

int main() {
	while (scanf("%d", &N) == 1 && N) {
		scanf("%d%d%d%d%d", &M, &x1, &y1, &x2, &y2);
		L[0][0] = Point(x1, y1), L[0][1] = Point(x1, y2);
		L[N + 1][0] = Point(x2, y1), L[N + 1][1] = Point(x2, y2);
		for (int i = 1, Ui, Li; i <= N; i++) {
			scanf("%d%d", &Ui, &Li);
			L[i][0] = Point(Ui, y1);
			L[i][1] = Point(Li, y2);
		}
//		puts("lololo");
		for (int i = 0, Xi, Yi; i < M; i++) {
			scanf("%d%d", &Xi, &Yi);
			++cnt[find(Point(Xi, Yi))];
		}

		for (int i = 0; i <= N; i++) {
			printf("%d: %d\n", i, cnt[i]);
			cnt[i] = 0;
		}
		putchar('\n');
	}

	return 0;
}

int find(const Point & toy) {
	int l = 0, r = N + 1;
	for (int m1, m2, step; r - l > 1; ) {
//		printf("[%d, %d]\n", l, r);
		step = std::max(1, (r - l) / 3);
		m1 = l + step, m2 = std::min(m1 + step, r);
		long long x1 = (L[m1][0] - L[m1][1]) * (toy - L[m1][1]), x2 = (L[m2][0] - L[m2][1]) * (toy - L[m2][1]);
		if (x1 > 0) {
			if (x2 > 0) // left, left
				r = m1;
		}
		else {
			if (x2 > 0) // right, left
				l = m1, r = m2;
			else		// right, right
				l = m2;
		}
	}
	return l;
}
