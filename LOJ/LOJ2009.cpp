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
void UMin(T & x, const T & y) {
	if (x > y) x = y;
}
template <typename T> inline
void UMax(T & x, const T & y) {
	if (x < y) x = y;
}
inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + kMod : a; }
inline int Mul(int a, int b) { return 1ll * a * b % kMod; }
int FPow(int bs, int ex = kMod - 2) {
	int res = 1;
	for (; ex; bs = Mul(bs, bs), ex >>= 1)
		if (ex & 1) res = Mul(res, bs);
	return res;
}

#define BR(U, I) (U >> I - 1 ^ 1)
#define FA(U, I) (1 << I - 1 <= U ? U >> I : -1)
#define LSON(_) (_ << 1)
#define RSON(_) (_ << 1 | 1)

const int kMaxn = 2e5 + 5, kLg = 19;

int n;
int A[kMaxn];
LL dis[kMaxn][kLg], DP[kMaxn][kLg][2];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", A + i);
	for (int i = 2; i <= n; i++) {
		scanf("%lld", dis[i] + 1);
		for (int j = 2; ~FA(i, j); j++)
			dis[i][j] = dis[FA(i, 1)][j - 1] + dis[i][1];
	}

	for (int u = n; u; u--) {
		for (int i = 1; ~FA(u, i); i++) {
			if (LSON(u) > n) {
				DP[u][i][0] = dis[u][i] * A[FA(u, i)];
				DP[u][i][1] = (dis[u][i] + dis[BR(u, i)][1]) * A[BR(u, i)];
			} else if (RSON(u) > n) {
				DP[u][i][0] = DP[LSON(u)][i + 1][0] +
					dis[LSON(u)][1] * A[LSON(u)];
				DP[u][i][1] = DP[LSON(u)][i + 1][1] + 
					dis[LSON(u)][1] * A[LSON(u)];
			} else {
				DP[u][i][0] = std::min(DP[LSON(u)][1][1] +
					dis[LSON(u)][1] * A[LSON(u)] + DP[RSON(u)][i + 1][0],
					DP[RSON(u)][1][1] + dis[RSON(u)][1] * A[RSON(u)] +
					DP[LSON(u)][i + 1][0]);
				DP[u][i][1] = std::min(DP[LSON(u)][1][1] +
					dis[LSON(u)][1] * A[LSON(u)] + DP[RSON(u)][i + 1][1],
					DP[RSON(u)][1][1] + dis[RSON(u)][1] * A[RSON(u)] +
					DP[LSON(u)][i + 1][1]);
			}
		}
	}
	LL ans = kInf64;
	for (int u = 1; u <= n; u++) {
		LL sum = DP[u][1][0];
		for (int v = u, fa = FA(u, 1); ~fa; v = FA(v, 1), fa = FA(fa, 1)) {
			if (BR(v, 1) <= n) {
				sum += dis[BR(v, 1)][1] * A[BR(v, 1)] +
					DP[BR(v, 1)][2][0];
			} else {
				sum += dis[fa][1] * A[FA(fa, 1)];
			}
		} UMin(ans, sum);
	} printf("%lld\n", ans);
	return 0;
}
