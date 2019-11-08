#include <algorithm>
#include <cstdio>

const int kMaxn = 1e4 + 5;

typedef int Arr[kMaxn];

int n, cntc;
Arr vis, P, W, L, R;

int main() {
	scanf("%d", &n);
	for (int i = 2; i <= n; ++i) scanf("%d", P + i);
	for (int i = 1; i <= n; ++i) scanf("%d", W + i);
	long long ans = 0;
	for (int sz, i = 1; i <= n; ++i) if (!vis[i]) {
		L[cntc] = i, R[cntc] = i, sz = 0;
		for (int j = i; !vis[j]; vis[j] = 1, j = W[j]) { ++sz; R[cntc] = std::max(R[cntc], j); ans += abs(P[W[j]] - P[j]); }
		if (sz > 1) ++cntc;
	}
//	printf(" ans = %lld\n", ans);
	int mr = 0;
	for (int i = 0; i < cntc; ++i) {
//		printf(" L[i] %d, R[i] %d\n", L[i], R[i]);
		if (mr >= P[L[i]]) mr = std::max(mr, P[R[i]]);
		else { ans += P[L[i]] - mr << 1; mr = P[R[i]]; }
	}
//	printf(" mr = %d\n", mr);
	printf("%lld\n", ans); return 0;
}
