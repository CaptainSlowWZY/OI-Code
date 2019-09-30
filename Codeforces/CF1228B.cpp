#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
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

int n, m;
int A[1005][1005];

int main() {
	scanf("%d%d", &n, &m);
	int nos = 0;
	for (int i = 1, ri; i <= n; i++) {
		scanf("%d", &ri);
		for (int j = 1; j <= ri; j++) {
			if (A[i][j] == 2) nos = 1;
			else A[i][j] = 1;
		}
		if (A[i][ri + 1] == 1) nos = 1;
		else A[i][ri + 1] = 2;
	}
	for (int i = 1, ri; i <= m; i++) {
		scanf("%d", &ri);
		for (int j = 1; j <= ri; j++) {
			if (A[j][i] == 2) nos = 1;
			else A[j][i] = 1;
		}
		if (A[ri + 1][i] == 1) nos = 1;
		else A[ri + 1][i] = 2;
	}
	if (nos) { puts("0"); return 0; }
	
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (!A[i][j]) ++cnt;
		}
	}
	printf("%d\n", FPow(2, cnt));
	return 0;
}
