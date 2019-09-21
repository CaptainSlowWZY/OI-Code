#include <algorithm>
#include <cstdio>

const int kMaxn = 1e6 + 5, kMod = 998244353;

int n, m;
int sum[kMaxn][2];

inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + kMod : a; }

int main() {
	scanf("%d%d", &n, &m);
	
	sum[1][0] = sum[1][1] = 1;
	for (int i = 2; i <= n; i++) {
		sum[i][0] = Sub(sum[std::max(0, i - 2)][1],
			sum[std::max(0, i - m - 1)][1]);
		sum[i][1] = Sub(sum[i - 1][1],
			sum[std::max(0, i - m - 1)][1]);
		if (i <= m) sum[i][0] = Add(sum[i][0], 1);
		if (i < m) sum[i][1] = Add(sum[i][1], 1);
		sum[i][0] = Add(sum[i - 1][0], sum[i][0]);
		sum[i][1] = Add(sum[i - 1][1], sum[i][1]);
	} printf("%d\n", Sub(sum[n][0], (n >= m)));
	return 0;
}
