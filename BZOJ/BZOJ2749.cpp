#include <cstdio>

int n, totp;
int f[100010], np[100010], P[100010];

int main() {
	f[1] = 0, f[2] = 1;
	for (int i = 2; i <= 100000; i++) {
		if (!np[i]) {
			P[totp++] = i;
			if (i > 2) f[i] = f[i - 1];
		}
		for (int j = 0, d; j < totp &&
				(d = i * P[j]) <= 100000; j++) {
			np[d] = 1, f[d] = f[i] + f[P[j]];
			if (i % P[j] == 0) break;
		}
	}

	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		int odd = 1;
		long long ans = 0;
		for (int i = 0, Pi, Ki; i < n; i++) {
			scanf("%d%d", &Pi, &Ki);
			odd &= Pi & 1;
			ans += 1ll * Ki * f[Pi];
		}
		printf("%lld\n", ans + odd);
	}
	return 0;
}
