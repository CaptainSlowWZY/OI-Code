// chy round, hahahahahaaaa!
#include <algorithm>
#include <cstdio>

int n, m, q, c, u, bmx, bs, F[1 << 20], B[20];

void Solve();

int main() {
	int t; scanf("%d", &t);
	while (t--) Solve();
	return 0;
}

void Solve() {
	scanf("%d%d", &n, &m); std::fill(F, F + (u = 1 << m), 0);
	for (int i = 0, si; i < n; ++i) {
		scanf("%d", &si); ++F[si];
	} scanf("%d", &c); 
	for (int i = bs = bmx = 0; i < c; ++i) {
		scanf("%d", B + i); bs |= 1 << B[i];
		bmx = std::max(bmx, B[i]);
	}
	for (int i = m - bmx - 1, t; ~i; --i) {
		for (int j = t = (1 << i | bs << i); j < u; ++j) {
			if ((j & t) == t) F[j ^ t] += F[j];
		}
	} scanf("%d", &q);
	for (int t; q--; ) { scanf("%d", &t); printf("%d\n", F[t]); }
}
