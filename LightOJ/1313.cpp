#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>

#define rg register
#define gch getchar

const int MAXN = 105, INF = 0x3f3f3f3f;

struct Point;
typedef Point Vector;
struct Point {
	int x, y;
	Point (int x_ = 0, int y_ = 0) : x(x_), y(y_) {}
	Vector operator+(const Vector & v) const { return Vector(x + v.x, y + v.y); }
	Vector operator-(const Vector & v) const { return Vector(x - v.x, y - v.y); }
	Vector operator*(int k) const { return Vector(x * k, y * k); }
	int operator*(const Vector & v) const { return x * v.y - y * v.x; }
    friend int dot(const Vector & v1, const Vector & v2) { return v1.x * v2.x + v1.y + v2.y; }
	bool operator<(const Point & p) const {
		return x == p.x ? y < p.y : x < p.x;
	}
	bool operator==(const Point & p) const {
		return x == p.x && y == p.y;
	}
    void out() const {
        printf("  (%d, %d)\n", x, y);
    }
    bool in_polygon(const Point poly[], int sz) const;
} H[MAXN], P[MAXN], S[MAXN];

int N, M, GC, PC, totp, D[MAXN][MAXN];

int main() {
    int t;
    scanf("%d", &t);
    for (int cs = 1; cs <= t; cs++) {
        scanf("%d%d%d%d", &N, &M, &GC, &PC);
        for (int i = 0; i < N; i++) scanf("%d%d", &H[i].x, &H[i].y);

        std::sort(H, H + N);
        int top = 0;
        for (int i = 0; i < N; i++) {
            while (top > 1 && (S[top - 1] - S[top - 2]) * (H[i] - S[top - 2]) <= 0) --top;
            S[top++] = H[i];
        }
        for (int i = N - 2, lmt = top; i >= 0; i--) {
            while (top > lmt && (S[top - 1] - S[top - 2]) * (H[i] - S[top - 2]) <= 0) --top;
            S[top++] = H[i];
        }
        if (N > 1) --top;

        Point Pi;
        totp = 0;
        for (int i = 0; i < M; i++) {
            scanf("%d%d", &Pi.x, &Pi.y);
            if (Pi.in_polygon(S, top)) P[totp++] = Pi;
        }

        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++) {
                if (i == j) {
                    D[i][j] = INF;
                    continue;
                }
                int flag = 1;
                for (int k = 0; k < totp && flag; k++)
                    if ((H[j] - H[i]) * (P[k] - H[i]) < 0) flag = 0;
                D[i][j] = flag ? PC : INF;
            }
        for (int k = 0; k < N; k++)
            for (int i = 0; i < N; i++)
                for (int j = 0; j < N; j++)
                    D[i][j] = std::min(D[i][j], D[i][k] + D[k][j]);
        int minh = INF;
        for (int i = 0; i < N; i++) minh = std::min(minh, D[i][i]);
        if (!totp) minh = 0;

        printf("Case %d: %d\n", cs, minh + (M - totp) * GC);
    }

    return 0;
}

bool Point::in_polygon(const Point poly[], int sz) const {
    int wn = 0;
    for (int i = 0; i < sz; i++) {
        int k = (poly[(i + 1) % sz] - poly[i]) * (*this - poly[i]),
            d1 = poly[i].y - y, d2 = poly[(i + 1) % sz].y - y;
        if (k > 0 && d1 <= 0 && d2 > 0) ++wn;
        if (k < 0 && d2 <= 0 && d1 > 0) --wn;
    }
    return wn;
}