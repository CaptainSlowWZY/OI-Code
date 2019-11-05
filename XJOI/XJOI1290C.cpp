#pragma GCC optimize(2)
#include <algorithm>
#include <cstdio>

const int kMaxn = 5e6 + 10;

void Solve();

int main() {
	int t; scanf("%d", &t);
	while (t--) Solve();
	return 0;
}

int n, k;
char S[kMaxn];
int la[kMaxn];
long long F[kMaxn];

void Solve() {
	scanf("%d%d%s", &n, &k, S + 1);
	la[n + 1] = n + k * 2;
	for (int i = n; i; --i) la[i] = S[i] == '1' ? i : la[i + 1];
	for (int laa, i = 1; i <= n; ++i) {
		F[i] = F[i - 1] + i, laa = la[std::max(1, i - k)];
		if (laa <= std::min(n, i + k))
			F[i] = std::min(F[i], F[std::max(1, laa - k) - 1] + laa);
	} printf("%lld\n", F[n]);
}
