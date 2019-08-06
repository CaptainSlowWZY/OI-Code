#include <algorithm>
#include <cstdio>

#define fir first
#define sec second

const int kMaxn = 1e5 + 10;

int n;
std::pair<int, int> A[kMaxn];

namespace bit {
	void Add(int p);
	int Query(int p);
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d%d", &A[i].fir, &A[i].sec);
	std::sort(A, A + n);
	long long ans = 0;
	for (int i = 0; i < n; i++) {
		ans += bit::Query(A[i].sec); bit::Add(A[i].sec);
	} printf("%lld\n", 1ll * n * (n - 1) / 2 - ans);
	return 0;
}

namespace bit {
	int T[kMaxn];
	void Add(int p) {
		for (; p <= n; p += p & -p) ++T[p];
	}
	int Query(int p) {
		int res = 0;
		for (; p; p &= p - 1) res += T[p];
		return res;
	}
}
