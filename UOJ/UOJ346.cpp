#include <algorithm>
#include <cstdio>
#include <vector>
#include <set>

#define pb push_back
#define SZ(_) (int)_.size()
#define ALL(_) _.begin(), _.end()

const int kMaxq = 505, kMod = 998244353;

inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + kMod : a; }
inline int Mul(int a, int b) { return 1ll * a * b % kMod; }
inline void Upa(int & a, int b) { a = Add(a, b); }
inline void Ups(int & a, int b) { a = Sub(a, b); }
inline void Upm(int & a, int b) { a = Mul(a, b); }
int FPow(int bs, int ex = kMod - 2) {
	int res = 1;
	for (; ex; bs = Mul(bs, bs), ex >>= 1)
		if (ex & 1) res = Mul(res, bs);
	return res;
}

typedef int Arr[kMaxq << 1];

struct Limit { int l, r, m; } L[kMaxq];

int n, q, A;

void Solve();

int main() {
	int t; scanf("%d", &t);
	while (t--) Solve();
	return 0;
}

std::vector<int> P, cur;
std::set<int> V;
Arr H, ml, DP[kMaxq << 1];

int Calc(int mi) {
	cur.clear();
	for (int i = 1; i < SZ(P); ++i) if (H[i] == mi) cur.pb(i);
	if (cur.empty()) return -1;
	for (int i = 1; i <= SZ(cur); ++i) ml[i] = 0;
//	printf("cur: "); for (int i = 0; i < SZ(cur); ++i) printf("%2d", cur[i]); puts("");
	for (int i = 0; i < q; ++i) if (L[i].m == mi) {
		int l = std::lower_bound(ALL(cur), L[i].l) - cur.begin() + 1,
			r = std::lower_bound(ALL(cur), L[i].r) - cur.begin();
//		printf(" L[%d] [%d, %d]\n", i, l, r);
		ml[r] = std::max(ml[r], l);
	} DP[0][0] = 1;
//	printf(" mi = %d\n", mi);
	for (int i = 1; i <= SZ(cur); ++i) {
		int ci = cur[i - 1], c0 = FPow(mi - 1, P[ci] - P[ci - 1]), c1 = FPow(mi, P[ci] - P[ci - 1]);
//		printf("   cur[%d] = %d, ex %d\n", i, ci, P[ci + 1] - P[ci]);
		c1 = Sub(c1, c0), DP[i][i] = 0;
		for (int j = 0; j < i; ++j) {
			if (j >= ml[i]) DP[i][j] = Mul(DP[i - 1][j], c0); else DP[i][j] = 0;
			DP[i][i] = Add(DP[i][i], Mul(DP[i - 1][j], c1));
		}
	}
	int res = 0;
	for (int i = 0; i <= SZ(cur); ++i) res = Add(res, DP[SZ(cur)][i]);
	return res;
}

void Solve() {
	// init for a new test case here...
	P.clear(); V.clear();
	scanf("%d%d%d", &n, &q, &A);
	for (int i = 0; i < q; ++i) {
		scanf("%d%d%d", &L[i].l, &L[i].r, &L[i].m);
		P.pb(L[i].l); P.pb(++L[i].r); V.insert(L[i].m);
	} P.pb(1); P.pb(n + 1); std::sort(ALL(P)); P.erase(std::unique(ALL(P)), P.end());
//	printf("P: "); for (int i = 0; i < SZ(P); ++i) printf("%2d", P[i]); puts("");
	for (int i = 1; i < SZ(P); ++i) H[i] = A + 1;
	for (int i = 0; i < q; ++i) {
		L[i].l = std::lower_bound(ALL(P), L[i].l) - P.begin() + 1,
		L[i].r = std::lower_bound(ALL(P), L[i].r) - P.begin() + 1;
	//	printf(" L[%d] [%d, %d)\n", i, L[i].l, L[i].r);
		for (int j = L[i].l; j < L[i].r; ++j) H[j] = std::min(H[j], L[i].m);
	}
	int ans = 1;
	for (std::set<int>::iterator it = V.begin(); it != V.end(); ++it) {
	//	printf(" calcating %d\n", *it);
		int t = Calc(*it);
		if (t == -1) return (void)(puts("0"));
		ans = Mul(ans, t);
	}
	for (int i = 1; i < SZ(P); ++i) if (H[i] == A + 1) ans = Mul(ans, FPow(A, P[i] - P[i - 1]));
	printf("%d\n", ans);
}
