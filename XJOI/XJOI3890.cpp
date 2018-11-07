#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <ctime>

#define torad(x) ((x) * Pie / 180)

struct Point;

typedef Point Vector;
typedef double real;

const double Pie = acos(-1);
const int MAXN = 55;

struct Point {
	real x, y;
	Point (real x_ = 0, real y_ = 0) : x(x_), y(y_) {}
	real length() const { return sqrt(x * x + y * y); }
	// real angle() const { return atan2(y, x); }
	Vector operator+(const Vector & v) const { return Vector(x + v.x, y + v.y); }
	Vector operator-(const Vector & v) const { return Vector(x - v.x, y - v.y); }
	Vector operator*(real k) const { return Vector(x * k, y * k); }
	// cross product
	Vector rotate(real ang) const {
	// this angle must in rad
		return Vector(x * cos(ang) - y * sin(ang), x * sin(ang) + y * cos(ang));
	}
};

int N, lst, dp[55][370];
char opt[20];

int main() {
	scanf("%d", &N);
	dp[lst = 0][0] = 1;
	int l1 = 0, l2 = 0;
	for (int i = 0, x; i < N; i++) {
		scanf("%s%d", opt, &x);
		if (opt[0] == 'r' || opt[0] == 'l') {
			if (opt[0] == 'r') x = -x;
			++lst;
//			printf(" x=%d\n", x);
			for (int j = 0; j < 360; j++) dp[lst][j] = dp[lst - 1][j];
			for (int j = 0; j < 360; j++) dp[lst][((j + x) % 360 + 360) % 360] |= dp[lst - 1][j];
		}
		else {
			if (opt[0] == 'f') l1 += x;
			else l2 += x;
		}
	}
	
	real ans = 0;
	for (int i = 0; i < 360; i++) {
		if (!dp[lst][i]) continue;
//		printf("i=%d\n", i);
		ans = std::max(ans, (Point(l1, 0) - Vector(l2, 0).rotate(torad(i))).length());
	}
	printf("%.10f\n", ans);
}
