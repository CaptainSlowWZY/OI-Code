#include <bits/stdc++.h>

const int MOD = 1e9 + 7;

int n, cnt[30];
char S[100010];

int main() {
	scanf("%d%s", &n, S);
	
	for (int i = 0; i < n; i++) {
		++cnt[S[i] - 'a'];
	}
	long long ans = 1;
	for (int i = 0; i < 26; i++) {
		(ans *= cnt[i] + 1) %= MOD;
	}
	--ans;
	ans = (ans + MOD) % MOD;
	printf("%lld\n", ans);

	return 0;
}
