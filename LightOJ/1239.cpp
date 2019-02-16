#include <cstdio>
#include <cctype>
#include <cmath>
#include <algorithm>

#define rg register
#define gch getchar

typedef double real;

const int MAXN = 5e4 + 10;
const real Pie = acos(-1);
const real EPS = 1e-8;

inline int sign(real x) {
    return fabs(x) < EPS ? 0 : (x < 0 ? -1 : 1); 
}

struct Point;
typedef Point Vector;
struct Point {
	real x, y;
	Point (real x_ = 0, real y_ = 0) : x(x_), y(y_) {}
	Vector operator+(const Vector & v) const { return Vector(x + v.x, y + v.y); }
	Vector operator-(const Vector & v) const { return Vector(x - v.x, y - v.y); }
	Vector operator*(real k) const { return Vector(x * k, y * k); }
	real operator*(const Vector & v) const { return x * v.y - y * v.x; }
	bool operator<(const Point & p) const {
		return !sign(x - p.x) ? y < p.y : x < p.x;
	}
    friend real dot(const Vector & v1, const Vector & v2) {
        return v1.x * v2.x + v1.y * v2.y;
    }
    real length() const { return sqrt(x * x + y * y); }
    Vector rotate(real ang) const {
		return Vector(x * cos(ang) - y * sin(ang), x * sin(ang) + y * cos(ang));
	}
    friend real angle(const Vector & v1, const Vector & v2) {
        return atan2(v1 * v2, dot(v1, v2));
    }
} P[MAXN], S[MAXN];

int N, d;

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
        read(N), read(d);
        for (int i = 0, xi; i < N; i++) {
            read(xi), P[i].x = xi;
            read(xi), P[i].y = xi;
        }
        printf("Case %d: ", cs);

        if (N == 1) {
            printf("%lf\n", 2.0 * d * Pie);
            continue;
        }
        if (N == 2) {
            printf("%lf\n", 2.0 * (d * Pie + (P[1] - P[0]).length()));
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

        real ans = 0;
        S[top++] = S[0], S[top++] = S[1];
        for (int i = 1; i + 1 < top; i++) {
            Vector v1 = (S[i - 1] - S[i]).rotate(Pie / 2), v2 = (S[i + 1] - S[i]).rotate(-Pie / 2);
            ans += angle(v1, v2) * d + v2.length();
        }

        printf("%lf\n", ans);
    }

    return 0;
}