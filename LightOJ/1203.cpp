// VJ 283647 K
#include <cstdio>
#include <cmath>
#include <cctype>
#include <algorithm>

#define rg register
#define gch getchar

const double EPS = 1e-8;
const double Pie = acos(-1);

typedef long long LL;

struct Point;
typedef Point Vector;
struct Point {
	LL x, y;
	Point (LL x_ = 0, LL y_ = 0) : x(x_), y(y_) {}
	Vector operator+(const Vector & v) const { return Vector(x + v.x, y + v.y); }
	Vector operator-(const Vector & v) const { return Vector(x - v.x, y - v.y); }
	Vector operator*(LL k) const { return Vector(x * k, y * k); }
	LL operator*(const Vector & v) const { return x * v.y - y * v.x; }
	bool operator<(const Point & p) const {
		return x == p.x ? y < p.y : x < p.x;
	}
    friend LL dot(const Vector & v1, const Vector & v2) {
        return v1.x * v2.x + v1.y * v2.y;
    }
    friend double angle(const Vector & v1, const Vector & v2) {
        return atan2(v1 * v2, dot(v1, v2));
    }
} P[100010], S[100010];

int N;

namespace FastIO {
    template <typename T>
        void read(T & x) {
            rg char ch = gch(); rg int f = 0;
            for (; !isdigit(ch); ch = gch()) f |= ch == '-';
            for (x = 0; isdigit(ch); ch = gch()) x = (x << 3) + (x << 1) + (ch ^ '0');
            f ? x = -x : 0;
        }
}

int main() {
    using FastIO::read;

    int t;
    read(t);
    for (int cs = 1; cs <= t; cs++) {
        read(N);
        for (int i = 0; i < N; i++) read(P[i].x), read(P[i].y);

        printf("Case %d: ", cs);
        if (N <= 2) {
            puts("0");
            continue;
        }

        std::sort(P, P + N);
        int top = 0;
        for (int i = 0; i < N; i++) {
            while (top > 1 && (S[top - 1] - S[top - 2]) * (P[i] - S[top - 2]) <= 0) --top;
            S[top++] = P[i];
        }
        int lmt = top;
        for (int i = N - 2; i >= 0; i--) {
            while (top > lmt && (S[top - 1] - S[top - 2]) * (P[i] - S[top - 2]) <= 0) --top;
            S[top++] = P[i];
        }
        if (N > 1) --top;

        double ans = fabs(angle(S[top - 1] - S[0], S[1] - S[0]));
        for (int i = 1; i + 1 < top; i++) ans = std::min(ans, fabs(angle(S[i + 1] - S[i], S[i - 1] - S[i])));
        ans = std::min(ans, fabs(angle(S[top - 2] - S[top - 1], S[0] - S[top - 1])));
        
        printf("%lf\n", ans * 180.0 / Pie);
    }
    return 0;
}