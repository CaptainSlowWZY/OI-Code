#include <algorithm>
#include <cstdio>

typedef double Db;

const int kMaxn = 1e3 + 5;

int n, m, l, r, V, L;
int A[kMaxn];
Db DP[2][kMaxn], sn[kMaxn];

int main() {
	freopen("pigeon.in", "r", stdin);
	freopen("pigeon.out", "w", stdout);
	scanf("%d%d%d%d%d", &n, &m, &l, &r, &V);
	for (int i = 1; i <= n; ++i) scanf("%d", A + i);
	Db *prv = DP[0], *nxt = DP[1];
	nxt[m] = V, L = r - l + 1;
	for (int i = m; ~i; --i) {
		sn[i] = sn[i + 1] + nxt[i];
		if (m - i + 1 > L) sn[i] -= nxt[i + L];
	}
	for (int i = n; i; --i) {
		for (int al, ar, exc, j = m - 1; ~j; --j) {
			al = j + l, ar = j + r;
			Db t;
			if (al > m) { t = 0, exc = L; }
			else if (ar > m) { t = sn[al], exc = ar - m; }
			else { t = sn[al], exc = 0; }
			prv[j] = std::max((t + exc * nxt[m]) / L, nxt[j] + A[i]);
		} prv[m] = nxt[m] + A[i]; std::swap(nxt, prv);
		for (int j = m; ~j; --j) {
			sn[j] = sn[j + 1] + nxt[j];
			if (m - j + 1 > L) sn[j] -= nxt[j + L];
		}
	} printf("%.3lf\n", nxt[0]); fclose(stdin); fclose(stdout); return 0;
}
