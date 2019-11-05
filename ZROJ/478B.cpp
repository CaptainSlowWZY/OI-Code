#include <cstdio>
#include <set>

#define SZ(_) (int)_.size()

#define SZ(_) (int)_.size()

typedef std::set<int> Si;

const int kU = 1 << 16, kMod = 1e9 + 7;

inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + kMod : a; }
inline int Mul(int a, int b) { return 1ll * a * b % kMod; }

int n, m, U, vis[kU + 5], P[kU + 5];

int Solve(int cur, int fr, int ls);

int main() {
	scanf("%d%d", &n, &m); U = 1 << m;
	for (int i = 0; i < U; ++i) {
		scanf("%d", P + i); vis[P[i]] = 1;
	}
	for (int i = 1; i <= n; ++i)
		if (!vis[i]) { puts("0"); return 0; }
	printf("%d\n", Solve(m - 1, 0, U));
	return 0;
}

int Solve(int cur, int fr, int ls) {
	if (ls - fr <= 1) return 1;
	int md = fr + ls >> 1, nof = 0;
	Si p1, p2;
	for (int i = fr; i < md; ++i) p1.insert(P[i]);
	for (int i = md; i < ls; ++i) {
		nof += !p1.count(P[i]); p2.insert(P[i]);
	} if (nof == ls - md)
		return Mul(Solve(cur - 1, fr, md), Solve(cur - 1, md, ls));
	if (SZ(p1) == SZ(p2)) {	
		Si::iterator j = p1.begin(), k = p2.begin();
		for (int i = 0; i < SZ(p1); ++i, ++j, ++k) {
			if (*j != *k) return 0;
		} return Mul(Solve(cur - 1, fr, md), 2);
	} return 0;
}
