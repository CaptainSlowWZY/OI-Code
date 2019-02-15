#include <cstdio>
#include <cmath>
#include <algorithm>

const int MAXN = 1e5 + 5;
const double EPS = 1e-8;

struct Point;
typedef Point Vector;
struct Point {
    double x, y;
    Point(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
    Vector operator-(const Point & p) const {
        return Vector(x - p.x, y - p.y);
    }
    double operator*(const Vector & v) const {
        return x * v.y - y * v.x;
    }
} P[MAXN][2];

inline int sign(double x) {
	return fabs(x) < EPS ? 0 : (x < 0 ? -1 : 1);
}
inline bool seg_intersec(const Point & A1, const Point & A2, const Point & B1, const Point & B2) {
	return std::min(A1.x, A2.x) <= std::max(B1.x, B2.x) && std::min(B1.x, B2.x) <= std::max(A1.x, A2.x) &&
		std::min(A1.y, A2.y) <= std::max(B1.y, B2.y) && std::min(B1.y, B2.y) <= std::max(A1.y, A2.y) &&
		sign((A2 - A1) * (B1 - A1)) * sign((A2 - A1) * (B2 - A1)) <= 0 &&
		sign((B2 - B1) * (A1 - B1)) * sign((B2 - B1) * (A2 - B1)) <= 0;
}

int main() {
    for (int N; scanf("%d", &N) == 1 && N; ) {
        for (int i = 0; i < N; i++)
            for (int j = 0; j < 2; j++)
                scanf("%lf%lf", &P[i][j].x, &P[i][j].y);
        
        printf("Top sticks");
        int cnt = 0;
        for (int i = 0; i < N; i++) {
            int flag = 0;
            for (int j = i + 1; j < N; j++)
                if (seg_intersec(P[i][0], P[i][1], P[j][0], P[j][1])) {
                    flag = 1;
                    break;
                }
            if (!flag) printf("%c%c%d", cnt++ ? ',' : ':', ' ', i + 1);
        }
        puts(".");
    }

    return 0;
}