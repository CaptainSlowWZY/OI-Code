#include <cstdio>

int N, totp, flag[1005], P[1005];
long long DP[1005];

int main() {
	scanf("%d", &N);
	
	for (int i = 2; i <= N; i++) {
		if (!flag[i]) P[totp++] = i;
		for (int j = 0; j < totp && i * P[j] <= N; j++) {
			flag[i * P[j]] = 1;
			if (i % P[j] == 0) break;
		}
	}
	DP[0] = 1;
	for (int i = 0; i < totp; i++)
		for (int j = N; j >= P[i]; j--)
			for (int k = P[i]; k <= j; k *= P[i])
				DP[j] += DP[j - k];
	long long ans = 0;
	for (int i = 0; i <= N; i++) ans += DP[i];
	printf("%lld\n", ans);
	return 0;
}
