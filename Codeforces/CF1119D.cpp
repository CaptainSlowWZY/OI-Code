#include <cstdio>
#include <algorithm>
#include <map>

#define fir first
#define sec second

typedef long long LL;

const int kMaxn = 1e5 + 10;

int n, q, k;
LL A[kMaxn], scnt[kMaxn], sgle[kMaxn], lev[kMaxn];
std::map<LL, int> cnt;

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%lld", A + i);
	
	std::sort(A, A + n);
	n = std::unique(A, A + n) - A;
	for (int i = 1; i < n; i++) {
		LL gap = A[i] - A[i - 1];
		++cnt[gap];
	}
	for (auto it = cnt.begin(); it != cnt.end(); ++it) {
		lev[++k] = it->fir;
		scnt[k] = scnt[k - 1] + 1ll * it->fir * it->sec;
		sgle[k] = sgle[k - 1] + it->sec;
	/*	printf(" %d level %lld, gap %lld, cnt %d, scnt %lld, sgle %lld\n",
				k, lev[k], it->fir, it->sec, scnt[k], sgle[k]);*/
	}

	scanf("%d", &q);
	for (LL gap, l, r, res; q--; ) {
		scanf("%lld%lld", &l, &r);	
		gap = r - l;
		int i = std::upper_bound(lev + 1, lev + k + 1, gap) - lev - 1;
	//	printf(" i %d\n", i);
		res = scnt[i] + (1 + gap) * (sgle[k] - sgle[i]) + gap + 1;
		printf("%lld ", res);
	}
	puts("");

	return 0;
}
