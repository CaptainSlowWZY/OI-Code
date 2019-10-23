#include <algorithm>
#include <cstdio>

#define fi first
#define se second

typedef std::pair<int, int> Pii;

int n, u;
Pii A[(1 << 18) + 5];

inline void Upd(Pii & a, const Pii & b) {
	if (b.fi > a.fi) {
		a.se = a.fi; a.fi = b.fi;
		if (b.se > a.se) a.se = b.se;
	} else if (b.fi > a.se) a.se = b.fi;
}

int main() {
	scanf("%d", &n);
	u = 1 << n;
	for (int i = 0; i < u; ++i) {
		scanf("%d", &A[i].fi);
		A[i].se = 0;
	}
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < u; ++j)
			if (j >> i & 1) Upd(A[j], A[j ^ 1 << i]);
	int ans = 0;
	for (int i = 1; i < u; ++i) {
		ans = std::max(ans, A[i].fi + A[i].se);
		printf("%d\n", ans);
	} return 0;
}
