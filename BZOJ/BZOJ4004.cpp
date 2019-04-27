// JLOI 2015
#include <cstdio>
#include <cmath>
#include <algorithm>

const int kMaxn = 505;
const double kEps = 1e-6;

struct Vector {
	double ar[kMaxn];
	int cost;
	
	double & operator[](int x) {
		return ar[x];
	}
	bool operator<(const Vector & v) const {
		return cost < v.cost;
	}
} A[kMaxn];

int n, m;

inline int Sign(double x) {
	return fabs(x) < kEps ? 0 : (x < 0 ? -1 : 1);
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) scanf("%lf", &A[i][j]);
	}
	for (int i = 0; i < n; i++) scanf("%d", &A[i].cost);
	
	std::sort(A, A + n);
	int ans = 0, tot = 0;
	for (int i = 0, dim; i < n; i++) {
		double mx = 0;
		for (int j = 0; j < m; j++) {
			if (fabs(A[i][j]) > mx) {
				mx = fabs(A[i][j]);
				dim = j;
			}
		}

		if (Sign(mx)) {
			++tot, ans += A[i].cost;
			for (int j = i + 1; j < n; j++) {
				double mul = A[j][dim] / A[i][dim];
				for (int k = 0; k < m; k++) {
					A[j][k] -= A[i][k] * mul;
				}
			}
		}
	}

	printf("%d %d\n", tot, ans);
	return 0;
}
