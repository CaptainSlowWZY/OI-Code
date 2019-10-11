#include <algorithm>
#include <cassert>
#include <cctype>
// #include <cmath>
#include <cstdio>
// #include <cstdlib>
#include <cstring>
// #include <ctime>
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
#define SORT(_) std::sort(_.begin(), _.end())
#define LB(_, __) std::lower_bound(_.begin(), _.end(), __)
#define UB(_, __) std::upper_bound(_.begin(), _.end(), __)

typedef long long LL;
typedef double DB;
typedef std::pair<DB, DB> Pdd;
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
// const double kPie = acos(-1), kEps = 1e-9;

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

const int kLen = 1e6 + 5, kLg = 21;

char S[kLen];
int n;

namespace sam {
	void Extend(int, int);
	void Gao();
	int Game(int, int);
}

int main() {
	scanf("%s%d", S, &n);
	for (int i = 0; S[i]; ++i) sam::Extend(S[i] - 'a', i);
	sam::Gao();
	int x0 = 0, all1 = 1;
	for (int l, r, t; n--; ) {
		scanf("%d%d", &l, &r);
		t = sam::Game(r - 1, r - l + 1);
		x0 ^= t;
		if (t) all1 &= t == 1;
		puts(x0 ? "Fir" : "Sec");
		puts(all1 && !x0 || !all1 && x0 ? "Fir" : "Sec");
	} return 0;
}

namespace sam {
	typedef int IAr[kLen << 1];
	
	IAr max, pos, cnt, id, SG0;
	int A[kLen << 1][26], F[kLen << 1][kLg];
	int last = 1, size = 1;

	void Extend(int ch, int la) {
		int p = last, np = ++size;
		max[last = np] = max[p] + 1, pos[la] = np;
		for (; p && !A[p][ch]; p = F[p][0]) A[p][ch] = np;
		if (!p) return (void)(F[np][0] = 1);
		int q = A[p][ch];
		if (max[q] == max[p] + 1) F[np][0] = q;
		else {
			int nq = ++size;
			max[nq] = max[p] + 1;
			F[nq][0] = F[q][0], F[q][0] = F[np][0] = nq;
			memcpy(A[nq], A[q], sizeof A[nq]);
			for (; A[p][ch] == q; p = F[p][0]) A[p][ch] = nq;
		}
	}
	void Gao() {
		for (int i = 1; i <= size; ++i) ++cnt[max[i]];
		for (int i = 1; i <= size; ++i) cnt[i] += cnt[i - 1];
		for (int i = 1; i <= size; ++i) id[cnt[max[i]]--] = i;
		for (int j = size, i, la; j; --j) {
			SG0[i = id[j]] = la = -1;
			Si s0;
			for (int c = 0; c < 26; ++c) {
				if (!A[i][c]) continue;
				s0.insert(SG0[A[i][c]]);
			}
			for (auto k : s0) {
				if (k != la + 1) { break; }
				la = k;
			} SG0[i] = la + 1;
		}
		for (int i = 1; i < kLg; ++i) {
			for (int u = 1; u <= size; ++u) {
				if (!F[u][i - 1]) continue;
				F[u][i] = F[F[u][i - 1]][i - 1];
			}
		}
	}
	int Game(int u, int len) {
		u = pos[u];
		for (int i = kLg - 1; i >= 0; --i) {
			if (max[F[u][i]] >= len) u = F[u][i];
		} return SG0[u];
	}
}
