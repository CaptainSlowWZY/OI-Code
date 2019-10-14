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
#ifdef DEBUG
	#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define debug(format, ...) 0
#endif

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

/* NOTICE! The default mod number is 1e9 + 7 ! */

int n;
int cnt[14];
char IN[5];

void Dfs(int);

int main() {
	scanf("%d", &n);
	int n0 = n;
	while (n--) {
		scanf("%s", IN);
		switch (IN[0]) {
			case 'A' : ++cnt[13]; break;
			case 'J' : ++cnt[10]; break;
			case 'Q' : ++cnt[11]; break;
			case 'K' : ++cnt[12]; break;
			case '2' : ++cnt[0]; break;
			case '1' : ++cnt[9]; break;
			default : ++cnt[IN[0] - '1'];
		}
	}
	Dfs(n0);
	puts("No");
	return 0;
}

// remember, our goal is to take the singles.

void Dfs(int r) {
	if (r <= 1) {
		puts("Yes");
		exit(0);
	}
	for (int i = 0; i < 14; ++i) {
		if (!cnt[i]) continue;
		int le = cnt[i];
		for (int j = 1; i + j < 14; ++j) {
			UMin(le, cnt[i + j]);
			if (!le) break;
		//	shun zi
			if (j >= 4) {
				for (int k = 0; k <= j; ++k) --cnt[i + k];
				Dfs(r - j - 1);
				for (int k = 0; k <= j; ++k) ++cnt[i + k];
			}
		//	lian dui
		/*	if (j >= 2 && le >= 2) {
				for (int k = 0; k <= j; ++k) cnt[i + k] -= 2;
				Dfs(r - (j + 1) * 2);
				for (int k = 0; k <= j; ++k) cnt[i + k] += 2;
			} */
		//	san shui zi & plane
		/*	for (j >= 1 && le >= 3) {
				for (int k = 0; k <= j; ++k) cnt[i + k] -= 3;
				Dfs(r - (j + 1) * 3);
				for (int k = 0; k <= j; ++k) cnt[i + k] += 3;
			} */
		}
	}
	for (int i = 0; i < 14; ++i) {
		if (cnt[i] <= 2) continue;
		for (int j = 0; j < 14; ++j) {
			if (!cnt[j] || j == i) continue;
			if (cnt[i] == 4 && cnt[j]) {
				cnt[i] -= 4;
			//	4 with 2
				for (int k = j + 1; k < 14; ++k) {
					if (!cnt[k] || k == i) continue;
				/*	if (cnt[j] >= 2 && cnt[k] >= 2) {
						cnt[j] -= 2, cnt[k] -= 2;
						Dfs(r - 8);
						cnt[j] += 2, cnt[k] += 2;
					} */
					--cnt[j], --cnt[k];
					Dfs(r - 6);
					++cnt[j], ++cnt[k];
				} cnt[i] += 4;
			}
		//	3 with 2
		/*	if (cnt[i] >= 3 && cnt[j] >= 2) {
				cnt[i] -= 3, cnt[j] -= 2;
				Dfs(r - 5);
				cnt[i] += 3, cnt[j] += 2;
			} */
		//	3 with 1
			if (cnt[i] >= 3 && cnt[j]) {
				cnt[i] -= 3, --cnt[j];
				Dfs(r - 4);
				cnt[i] += 3, ++cnt[j];
			}
		}
	}
	int single = 0;
	for (int i = 0; i < 14; ++i) single += cnt[i] == 1;
	if (single <= 1) {
		puts("Yes");
		exit(0);
	}
}
