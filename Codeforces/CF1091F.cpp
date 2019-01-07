// Codeforces 1091 F
// Good Bye 2018
#include <cstdio>
#include <algorithm>

typedef long long LL;

const int MAXN = 1e5 + 10;

int N;
LL L[MAXN];
char str[MAXN];

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) scanf("%lld", L + i);
	scanf("%s", str);

	int swimed = 0;
	LL stm = 0, ans = 0, wlk = 0;
	for (int i = 0; i < N; i++) {
		if (str[i] == 'G') stm += L[i], ans += 5LL * L[i], wlk += L[i] * 2;
		else if (str[i] == 'W') {
			swimed = 1;
			stm += L[i], ans += 3LL * L[i];
		}
		else {
			if (stm < L[i]) {
				ans += (swimed ? 3LL : 5LL) * (L[i] - stm);
				stm = 0;
			}
			else stm -= L[i];
			ans += L[i]; 
		}
		wlk = std::min(wlk, stm);
	}

	if (stm > 0) ans -= wlk * 2 + (stm - wlk);

	printf("%lld\n", ans);

	return 0;
}
