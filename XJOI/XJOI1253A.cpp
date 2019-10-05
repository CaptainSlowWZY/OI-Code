// game
#include <algorithm>
// #include <cassert>
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

#define GETZERO { puts("0"); zero = 1; break; }

int t, n, ans;
int cnt[32];

void Dfs(Vi rem);

int main() {
	scanf("%d", &t);
	while (t--) {
		std::fill(cnt, cnt + 31, 0);
		scanf("%d", &n);
		for (int i = 0, si; i < n; ++i) {
			scanf("%d", &si); ++cnt[si];
		}
		int zero = 0;
		if (cnt[0]) { puts("0"); continue; }
		for (int i = 0; i <= 30; ++i)
			if (cnt[i] > 1) GETZERO;
		if (zero) continue;
		// puts("lol");
		for (int i = 0; i <= 30; ++i) {
			if (!cnt[i]) continue;
			for (int j = i + 1; j <= 30; j++) {
				if (!cnt[j]) continue;
				// printf(" i = %d, j = %d\n", i, j);
				int del = j - i, sum = i + j, prod = i * j;
				for (int k = 0; k <= 30; k++) {
					if (!cnt[k] || k == i || k == j) continue;
				/*	printf(" k = %d\n", k);
					puts("   -");*/
					if (k + del <= 30 && cnt[k + del] &&
						k + del != i && k + del != j &&
						k != del) GETZERO;
					// puts("   +");
					if (sum >= k && sum - k <= 30 &&
						cnt[sum - k] && sum - k != i &&
						sum - k != j && sum - k != k) GETZERO;
					// puts("   *");
					if (k && prod % k == 0 &&
						prod / k <= 30 && cnt[prod / k] &&
						i * k != prod && j * k != prod &&
						k * k != prod) GETZERO;
				} if (zero) break;
			} if (zero) break;
		} if (zero) continue;
		Vi num;
		for (int i = 0; i <= 30; i++) {
			if (!cnt[i]) continue;
			num.pb(i);
		} ans = kInf;
		Dfs(num);
		printf("%d\n", ans);
	}
}

void Dfs(Vi rem) {
/*	printf(" ans = %d\n", ans);
	for (int i = 0; i < SZ(rem); ++i) printf("%4d", rem[i]);
	pch('\n');*/
	if (!ans) return;
	if (SZ(rem) == 1) {
		UMin(ans, rem[0]);
		return;
	}
	for (int i = 0; i < SZ(rem); ++i) {
		for (int j = i + 1; j < SZ(rem); ++j)
			if (rem[i] == rem[j]) { ans = 0; return; }
	}
	for (int i = 0; i < SZ(rem); ++i) {
		for (int j = i + 1; j < SZ(rem); ++j) {
			Vi nxt;
			for (int k = 0; k < SZ(rem); k++)
				if (i != k && j != k) nxt.pb(rem[k]);
			nxt.pb(rem[i] + rem[j]);
			Dfs(nxt);
			*nxt.rbegin() = abs(rem[i] - rem[j]);
			Dfs(nxt);
			*nxt.rbegin() = rem[i] * rem[j];
			Dfs(nxt);
		}
	}
}