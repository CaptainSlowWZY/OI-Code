// BZOJ 4652
// NOI 2016
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <map>
#include <cassert>

const int MAXK = 2005, MAXN = 1e7;

typedef int IntAr[MAXN + 10];
typedef long long LL;
typedef std::pair<int, int> Pii;

int N, M, K, totp, totf, fack[MAXK], F[MAXK];
IntAr mu, sum1, /*sum2, */flag, P/*, vis*/;
std::map<Pii, int> mp;
std::map<int, int> mpm;

int g(int n, int k);
inline LL f(int n) {
	return (LL)n / K * F[K] + F[n % K];
}
	
int main() {
	scanf("%d%d%d", &N, &M, &K);
	
	mu[1] = sum1[1] = 1;
	for (int i = 2; i <= MAXN; i++) {
		if (!flag[i]) P[totp++] = i, mu[i] = -1;
		for (int j = 0, pd; j < totp && (pd = i * P[j]) <= MAXN; j++) {
			flag[pd] = 1;
			if (i % P[j] == 0) {
				mu[pd] = 0;
				break;
			}
			mu[pd] = -mu[i];
		}
		sum1[i] = sum1[i - 1] + mu[i];
	}
	for (int i = 1; i <= K; i++) {
		if (K % i == 0) fack[totf++] = i;
		F[i] = F[i - 1] + (std::__gcd(i, K) == 1);
	}
	
	LL ans = 0, lst = 0, cur;
	for (int i = 1, j; i <= N && i <= M; i = j + 1, lst = cur) {
		j = std::min(N / (N / i), M / (M / i));
		cur = g(j, K);
		ans += LL(cur - lst) * (N / i) * f(M / i);
	}

	printf("%lld\n", ans);
	return 0;
}

int S(int n) {
	if (n <= MAXN) return sum1[n];
//	if (vis[N / n]) return sum2[N / n];
//	vis[N / n] = 1;
//	int & ret = sum2[N / n];
	if (mpm.count(n)) return mpm[n];
	int & ret = mpm[n];
	ret = n > 1;
	for (int i = 2, j; i <= n; i = j + 1) {
		j = n / (n / i);
		ret -= (j - i + 1) * S(n / i);
	}
	return ret;
}
	
int g(int n, int k) {
	if (!n) return 0;
	if (k == 1) return S(n);
	Pii cur(n, k);
	if (mp.count(cur)) return mp[cur];
	int & ret = mp[cur];
	ret = 0;
	for (int i = 0, fac; i < totf && (fac = fack[i]) <= k; i++) {
		if (k % fac || !mu[fac]) continue;
		ret += g(n / fac, fac);
	}
	return ret;
}
