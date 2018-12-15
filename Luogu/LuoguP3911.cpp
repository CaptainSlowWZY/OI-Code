// Luogu P3911
#include <cstdio>
#include <algorithm>

const int MAXN = 5e4;

typedef long long LL;
typedef int IntAr[MAXN + 10];
typedef LL LLAr[MAXN + 10];

int N, totp, mxai;
IntAr C, mu, flag, Prm;
LLAr g;

void calc();

int main() {
	scanf("%d", &N);
	for (int Ai, i = 0; i < N; i++) {
		scanf("%d", &Ai);
		++C[Ai], mxai = std::max(mxai, Ai);
	}

	calc();
	for (int i = 1; i <= mxai; i++) {
		for (int j = i; j <= mxai; j += i) g[i] += (LL)j * C[j];
		g[i] *= g[i];
	}
	LL ans = 0;
	for (int i = 1; i <= mxai; i++) {
		LL f = 0;
		for (int j = i, t = 1; j <= mxai; j += i, ++t) f += g[j] * mu[t];
		ans += f / i;
	}

	printf("%lld\n", ans);
	
	return 0;
}

void calc() {
	mu[1] = 1;
	for (int i = 2; i <= mxai; i++) {
		if (!flag[i]) Prm[totp++] = i, mu[i] = -1;
		for (int j = 0, pd; j < totp && (pd = Prm[j] * i) <= mxai; j++) {
			flag[pd] = 1;
			if (i % Prm[j] == 0) {
				mu[pd] = 0;
				break;
			}
			mu[pd] = -mu[i];
		}
	}
}
