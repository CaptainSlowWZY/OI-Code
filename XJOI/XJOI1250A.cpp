// prefix
#pragma GCC optimize(2)
#include <algorithm>
// #include <cassert>
#include <cctype>
#include <cstdio>
#include <cstring>
// #include <cmath>
#include <map>
#include <queue>
#include <set>
#include <vector>

#define fir first
#define sec second
#define pb push_back
#define pch putchar
#define rg register
#define SZ(_) (int)_.size()
#define LB(_, __) std::lower_bound(_.begin(), _.end(), __)
#define UB(_, __) std::upper_bound(_.begin(), _.end(), __)

typedef long long LL;
typedef std::pair<int, int> Pii;
typedef std::pair<LL, int> Pli;
typedef std::pair<int, LL> Pil;
typedef std::pair<LL, LL> Pll;
typedef std::vector<int> Vi;
typedef std::vector<LL> Vl;
typedef std::map<int, int> Mii;
typedef std::map<LL, int> Mli;
typedef std::map<int, LL> Mil;
typedef std::map<LL, LL> Mll;
typedef std::set<int> Si;
typedef std::set<LL> Sl;

const int kInf = 0x3f3f3f3f, kMod = 1e9 + 7;
const LL kInf64 = 0x3f3f3f3f3f3f3f3f;

template <typename T> inline
void UMin(T & x, const T & y) { if (x > y) x = y; }
template <typename T> inline
void UMax(T & x, const T & y) { if (x < y) x = y; }
inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + kMod : a; }
inline int Mul(int a, int b) { return 1ll * a * b % kMod; }
int FPow(int bs, int ex = kMod - 2) {
	int res = 1;
	for (; ex; bs = Mul(bs, bs), ex >>= 1)
		if (ex & 1) res = Mul(res, bs);
	return res;
}

const int kMaxn = 2005, kLen = 205;

int n, m;
int DP[kMaxn][kMaxn];
char S[kLen];

namespace trie {
	void Insert(const char st[]);
	void Solve();
}

int main() {
	// freopen("test.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%s", S);
		trie::Insert(S);
	}
	// fclose(stdin);
	trie::Solve();
	return 0;
}

namespace trie {
	const int kMaxv = 4e5 + 5;
	int dfs_clock = 1, sz;
	int A[kMaxv][26], end[kMaxv];
	int idfn[kMaxv], odfn[kMaxv];
	Mii left[kMaxn];

	void Insert(const char st[]) {
		int rt = 0;
		for (int i = 0, ch; st[i]; i++) {
			if (!A[rt][ch = st[i] - 'a']) {
				A[rt][ch] = ++sz;
				memset(A[sz], 0, sizeof A[sz]);
			} rt = A[rt][ch];
		} end[rt] = 1;
	}
	void Dfs(int u) {
		idfn[u] = dfs_clock;
		if (end[u]) ++dfs_clock;
		for (int i = 0; i < 26; i++) {
			if (!A[u][i]) continue;
			Dfs(A[u][i]);
		} odfn[u] = dfs_clock;
	}
	void Solve() {
		// printf(" sz = %d\n", sz);
		Dfs(0);
		for (int i = 1; i <= sz; i++)
			++left[odfn[i] - 1][idfn[i]];
		DP[0][0] = 1;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				for (auto & p : left[i])
					DP[i][j] = Add(DP[i][j], Mul(DP[p.fir - 1][j - 1], p.sec));
			}
		} printf("%d\n", DP[n][m]);
	}
}
