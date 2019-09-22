#include <cstdio>

int n, k, sum[100005];
char S[100005];

inline int Sum(int l, int r) {
	return sum[r] - sum[l];
}

int main() {
	scanf("%d%d%s", &n, &k, S);
	for (int i = 0; S[i]; i++) {
		S[i] ^= '0';
		sum[i + 1] = sum[i] + S[i];
	}
	for (int s, i = 0; i + k <= n; i++) {
		s = Sum(0, i) + Sum(i + k, n);
		if (!s || s + k == n) {
			puts("tokitsukaze");
			return 0;
		}
	}
	if (k * 2 >= n && k > 1) {
		int fail = 0;
		for (int i = 1; i + k + 1 < n; i++) {
			if (S[i] != S[i - 1] || S[n - i] != S[n - i - 1]) {
				fail = 1; break;
			}
		}
		if (!fail && S[0] != S[n - 1]) {
			puts("quailty");
			return 0;
		}
	} puts("once again");
	return 0;
}
