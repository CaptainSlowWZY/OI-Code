#include <algorithm>
#include <cassert>
#include <cstdio>

const int kMaxn = 2e5 + 5;

int n, q, A[kMaxn];

namespace solver1 { void Solve(); }
namespace solver2 { void Solve(); }

int main() {
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; ++i) scanf("%d", A + i);
//	if (n <= 1000 && q <= 1000) solver1::Solve();
//	else solver2::Solve();
	solver2::Solve();
	return 0;
}

namespace solver1 {
	void Solve() {
		for (int o, x, y; q--; ) {
			scanf("%d%d", &o, &x);
			if (o == 1) {
				int res = 0;
				for (int i = 1; i <= n; ++i) {
					if (A[i] < x) continue;
					res += A[i - 1] < x;
				} printf("%d\n", res);
			} else {
				scanf("%d", &y);
				A[x] = y;
			}
		}
	}
}

namespace solver2 {
	int cntm, mp[kMaxn << 2], O[kMaxn], X[kMaxn], Y[kMaxn];

	namespace bit {
		int T[kMaxn << 2];
		void Add(int p, int f) { for (; p <= cntm + 1; p += p & -p) T[p] += f; }
		void Add(int l, int r, int f) { Add(l, f); Add(r + 1, -f); }
		int Qry(int p) { int r = 0; for (; p; p &= p - 1) r += T[p]; return r; }
	}
	inline int Id(int x) { return std::lower_bound(mp, mp + cntm, x) - mp + 1; }
	void Solve() {
		cntm = 0;
		for (int i = 0; i < q; ++i) {
			scanf("%d%d", O + i, X + i);
			if (O[i] == 2) { scanf("%d", Y + i); mp[cntm++] = Y[i], mp[cntm++] = Y[i] + 1; }
		}
		for (int i = 1; i <= n; ++i) { mp[cntm++] = A[i], mp[cntm++] = A[i] + 1; }
	//	assert(cntm < kMaxn * 4);
		std::sort(mp, mp + cntm); cntm = std::unique(mp, mp + cntm) - mp;
	//	printf(" cntm = %d\n", cntm);
//		for (int i = 0; i < cntm; ++i) printf("%d ", mp[i]); puts("");
		for (int i = 1; i <= n; ++i) if (A[i - 1] < A[i]) {
			bit::Add(Id(A[i - 1] + 1), Id(A[i]), 1);
//			printf("    gain [%d, %d]\n", Id(A[i - 1] + 1), Id(A[i]));
		}
		for (int i = 0, x, y; i < q; ++i) {
			if (O[i] == 1) printf("%d\n", bit::Qry(Id(X[i])));
			else {
				x = X[i], y = Y[i];
				if (A[x - 1] < A[x]) bit::Add(Id(A[x - 1] + 1), Id(A[x]), -1);
				if (x < n && A[x] < A[x + 1]) bit::Add(Id(A[x] + 1), Id(A[x + 1]), -1);
				A[x] = y;
				if (A[x - 1] < A[x]) bit::Add(Id(A[x - 1] + 1), Id(A[x]), 1);
				if (x < n && A[x] < A[x + 1]) bit::Add(Id(A[x] + 1), Id(A[x + 1]), 1);
			}
		}	
	}
}
