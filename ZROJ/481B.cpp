#include <algorithm>
#include <cstdio>
#include <functional>

#define fi first
#define se second

typedef double Db;
typedef std::pair<Db, Db> Pdd;

const int kMaxn = 505;
const Db kEps = 1e-6;

int n, id[kMaxn];
Pdd L[kMaxn];
Db P[kMaxn];

inline bool CmP(int a, int b) { return (L[a].fi - 1) / L[a].se > (L[b].fi - 1) / L[b].se; }

int main() {
	scanf("%d", &n);
	for (int i = 0, k; i < n; ++i) {
		scanf("%d", &k);
		for (int j = 0; j < k; ++j) scanf("%lf", P + j);
		std::sort(P, P + k, std::greater<Db>());
		if (P[0] + kEps > 1) { --i; --n; continue; }
		while (k && P[k - 1] < kEps) --k;
		Db prd = 1;
		for (int j = 0; j < k; ++j) { L[i].fi += prd * P[j], L[i].se += prd * P[j] * (j + 1), prd *= 1 - P[j]; }
		L[i].se += prd * k, id[i] = i;
	} std::sort(id, id + n, CmP);
	Pdd l(1, 0);
	for (int j, i = 0; i < n; ++i) { l.fi *= L[j = id[i]].fi, l.se *= L[j].fi, l.se += L[j].se; }
	printf("%.10lf\n", l.se); return 0;
}
