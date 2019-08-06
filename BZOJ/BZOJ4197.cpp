#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long LL;
typedef LL Matrix[1 << 8][1 << 8];

struct Number {
	int large, pset;
	bool operator<(const Number & num) const {
		return large < num.large;
	}
} num[505];

Matrix DP;
int n, totp;
LL P;
int np[505], D[505], Pr[505];

void Produce(int fir, int lst);

int main() {
	scanf("%d%lld", &n, &P);
	for (int i = 2; i <= n; i++) {
		if (!np[i]) { D[i] = totp; Pr[totp++] = i; }
		for (int j = 0, d; j < totp && (d = i * Pr[j]) <= n; j++) {
			np[d] = 1, D[d] = j;
			if (i % Pr[j] == 0) break;
		}
		for (int t = i; t > 1; t /= Pr[D[t]]) {
			if (Pr[D[t]] > 22) num[i].large = Pr[D[t]];
			else num[i].pset |= 1 << D[t];
		}
	}
	std::sort(num + 2, num + n + 1);
	int t = 2;
	DP[0][0] = 1;
	for (int i = 3; i <= n; i++) {
		if (num[i].large != num[t].large || !num[t].large) {
			Produce(t, i); t = i;
		}
	} Produce(t, n + 1);
	LL ans = 0;
	for (int m1 = 0; m1 < 256; m1++) {
		for (int m2 = 0; m2 < 256; m2++) {
			(ans += DP[m1][m2]) %= P;
		}
	} printf("%lld\n", (ans + P) % P);
	return 0;
}

void Produce(int fir, int lst) {
	static Matrix buf[2];
	LL (*G)[256] = buf[0], (*W)[256] = buf[1];
	memcpy(G, DP, sizeof DP);
	memcpy(W, DP, sizeof DP);
	for (int i = fir; i < lst; i++) {
		for (int m1 = 255; m1 >= 0; --m1) {
			for (int m2 = 255; m2 >= 0; --m2) {
				if (m1 & m2) continue;
				if (!(m2 & num[i].pset))
					(G[m1 | num[i].pset][m2] += G[m1][m2]) %= P;
				if (!(m1 & num[i].pset))
					(W[m1][m2 | num[i].pset] += W[m1][m2]) %= P;
			}
		}
	}
	for (int m1 = 0; m1 < 256; m1++) {
		for (int m2 = 0; m2 < 256; m2++) {
			DP[m1][m2] = (G[m1][m2] + W[m1][m2] -
					DP[m1][m2]) % P;
		}
	}
}
