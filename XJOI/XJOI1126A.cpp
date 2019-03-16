#include <cstdio>
#include <cmath>
#include <algorithm>

const int kBits = 15;

int n, m, lenm;
int dig[kBits], fail[kBits];

namespace solver1 {
	void Solve();
}

int main() {
	scanf("%d%d", &n, &m);

	for (int m0 = m; m0; m0 /= 10) {
		dig[lenm++] = m0 % 10;
	}
	if (!m) lenm = 1;
	std::reverse(dig, dig + lenm);
	fail[0] = fail[1] = 0;
	for (int i = 1, j; i < lenm; i++) {
		for (j = fail[i]; j && dig[j] != dig[i]; j = fail[j]);
		fail[i + 1] = dig[j] == dig[i] ? j + 1 : 0;
	}

	solver1::Solve();

	return 0;
}

namespace solver1 {
	double EXP[kBits], DP[kBits][kBits][2], vis[kBits][kBits][2];
	int lenn, num[kBits];

	double FPow(double bs, int ex) {
		double ret = 1;
		for (; ex; bs *= bs, ex >>= 1)
			if (ex & 1) ret *= bs;
		return ret;
	}
	double Dfs(int pos, int mch, int pre, int lmt) {
		if (pos < 0) return int(mch < lenm);
		if (!lmt && vis[pos][mch][pre]) return DP[pos][mch][pre];
		double ret = 0;
		for (int i = 0, j, u = lmt ? num[pos] : 9; i <= u; i++) {
			for (j = mch; j && i != dig[j]; j = fail[j]);
			i == dig[j] && (i || !i && !pre) ? j++ : 0;
		//	printf(" Dfs (pos %d, match %d, limit %d), num[pos] %d, i %d, u %d, j %d\n", pos, mch, lmt, num[pos], i, u, j);
			if (j < lenm) {
				ret += FPow(EXP[pos], i) * Dfs(pos - 1, j, pre & !i, lmt & (i == num[pos]));
			}
		}
		if (!lmt) {
			vis[pos][mch][pre] = 1;
			DP[pos][mch][pre] = ret;
		}
	//	printf(" Dfs (pos %d, match %d, limit %d) = %.6lf\n", pos, mch, lmt, ret);
		return ret;
	}
	void Solve() {
		for (int n0 = n; n0; n0 /= 10) {
			num[lenn++] = n0 % 10;
		}
	//	printf(" lennn = %d, lenm = %d\n", lenn, lenm);
		double pow10 = 1;
		EXP[0] = std::exp(1.0 / n);
		for (int i = 1; i <= lenn; i++) {
			pow10 *= 10;
			EXP[i] = std::exp(pow10 / n);
		}
		printf("%.3lf\n", Dfs(lenn - 1, 0, 1, 1) - 1);
	}
}
