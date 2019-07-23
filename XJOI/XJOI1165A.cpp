#include <cstdio>

int n, m, k, a, b;

namespace solver1 {
	void Solve();
}

int main() {
	scanf("%d%d%d%d%d", &n, &m, &k, &a, &b);

	solver1::Solve();

	return 0;
}

namespace solver1 {
	// 30pts
	double C(int n, int r) {
		long long res = 1;
		for (int i = n - r + 1; i <= n; i++) res *= i;
		for (int i = 2; i <= r; i++) res /= i;
		return res;
	}
	void Solve() {
		double ans = 0;
		for (int i = a; i <= b; i++) {
			ans += C(m, i) * C(n - m, k - i);
		}
		ans /= C(n, k);
		printf("%.4lf\n", ans);
	}
}
