#include <algorithm>
#include <cmath>
#include <cstdio>

#define fi first
#define se second

typedef double Db;
typedef std::pair<Db, Db> Pdd;

inline void operator+=(Pdd & a, const Pdd & b) { a.fi += b.fi, a.se += b.se; }

int t, n;
Db p;
int A[55];

Pdd Dfs(int, int);

int main() {
	while (~scanf("%lf%d%d", &p, &t, &n)) {
		for (int i = 0; i < n; ++i) scanf("%d", A + i);
		std::sort(A, A + n); printf("%.3lf\n", round(Dfs(n, 0).se * 1000) / 1000.0);
	} return 0;
}

Pdd Dfs(int lim, int sum) {
	if (sum > t) return Pdd(0, 0);
	Pdd res(0, 0);
	for (int i = lim - 1; ~i; --i) res += Dfs(i + 1, sum + A[i]);	
	Db pv = sum ? p : 0, t = lim - (1 - pv) * res.fi;
	return Pdd(lim * pv / t, ((1 - pv) * res.se + lim) / t);
}
