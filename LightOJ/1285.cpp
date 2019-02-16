#include <cstdio>
#include <cctype>
#include <cmath>
#include <cstring>
#include <algorithm>

#define rg register
#define gch getchar

const int MAXN = 2010;

struct Point;
typedef Point Vector;
struct Point {
	int x, y, id;
	Point (int x_ = 0, int y_ = 0) : x(x_), y(y_), id(0) {}
	Vector operator+(const Vector & v) const { return Vector(x + v.x, y + v.y); }
	Vector operator-(const Vector & v) const { return Vector(x - v.x, y - v.y); }
	Vector operator*(int k) const { return Vector(x * k, y * k); }
	int operator*(const Vector & v) const { return x * v.y - y * v.x; }
	bool operator<(const Point & p) const {
		return x == p.x ? y < p.y : x < p.x;
	}
	bool operator==(const Point & p) const {
		return x == p.x && y == p.y;
	}
} P[MAXN], S[MAXN];

int N, used[MAXN], ans[MAXN];

namespace FastIO {
    template <typename T>
        void read(T & x) {
            rg char ch = gch(); rg int f = 0;
            for (; !isdigit(ch); ch = gch()) f |= ch == '-';
            for (x = 0; isdigit(ch); ch = gch()) x = (x << 3) + (x << 1) + (ch ^ '0');
            f ? x = -x : 0;
        }
}
inline bool cmp(const Point & p1, const Point & p2) {
	return p1.x == p2.x ? p1.y > p2.y : p1.x > p2.x;
}

int main() {
    using FastIO::read;

    int t;
    read(t);
    for (int cs = 1; cs <= t; cs++) {
        read(N);
        for (int i = 0; i < N; i++) {
            read(P[i].x), read(P[i].y);
            P[i].id = i;
        }
		printf("Case %d:\n", cs);

		int top = 0;
		std::sort(P, P + N);
		int n = std::unique(P, P + N) - P;
		for (int i = 0; i < n; i++) {
			while (top > 1 && (S[top - 1] - S[top - 2]) * (P[i] - S[top - 2]) <= 0) --top;
			S[top++] = P[i];
		}
		int lmt = top;
		for (int i = n - 2; i >= 0; i--) {
			while (top > lmt && (S[top - 1] - S[top - 2]) * (P[i] - S[top - 2]) <= 0) --top;
			S[top++] = P[i];
		}
		if (n > 1) --top;
		if (top < 3) {
			puts("Impossible");
			continue;
		}

		top = 0;
		int aback = 0;
		for (int i = 0; i < N; i++) {
			while (top > 1 && (S[top - 1] - S[top - 2]) * (P[i] - S[top - 2]) < 0) --top;
			S[top++] = P[i];
		}
		memset(used, 0, sizeof used);
		for (int i = 0; i < top; i++) {
			ans[aback++] = S[i].id;
			used[S[i].id] = 1;
		}
		std::sort(P, P + N, cmp);
		for (int i = 0; i < N; i++)
			if (!used[P[i].id]) ans[aback++] = P[i].id;

		for (int i = 0; i < N; i++) printf("%d%c", ans[i], i + 1 == N ? '\n' : ' ');
    }
	return 0;
}