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

const int kMaxn = 2e5 + 5, kMaxp = 125;

int n, k, totp;
int P[kMaxn], la[kMaxp];
int T[kMaxp][kMaxp], IT[kMaxp][kMaxp];
Vi tr[kMaxp];
std::map<Vi, int> id;

void PreWork();

int main() {
	scanf("%d%d", &n, &k);
	PreWork();
	Vi pi(k);
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < k; j++) scanf("%d", &pi[j]);
		P[i] = id[pi];
	}
	LL ans = 0;
	for (int i = 1, j; i <= n; i++) {
		j = P[i];
		do {
			la[j] = i;
			for (int k = 0; k < totp; k++) {
				UMax(la[T[j][k]], la[k]);
				UMax(la[T[k][j]], la[k]);
			} j = T[j][P[i]];
		} while (j != P[i]);
		for (int j = 0; j < totp; j++) {
			if (!la[j]) continue;
			for (int k = 0, x; k < totp; k++) {
				x = IT[k][j];
				UMax(la[x], std::min(la[j], la[k]));
			}
		}
		for (int j = 0; j < totp; j++) ans += la[j];
	} printf("%lld\n", ans);
	return 0;
}

int Compose(int a, int b) {
	Vi res;
	for (int i = 0; i < k; i++)
		res.pb(tr[b][tr[a][i] - 1]);
	return id[res];
}

void PreWork() {
	Vi p(k);
	for (int i = 0; i < k; i++) p[i] = i + 1;
	do {
		tr[id[p] = totp++] = p;
	} while (std::next_permutation(p.begin(), p.end()));
	for (int i = 0; i < totp; i++) {
		for (int j = 0; j < totp; j++) {
			T[i][j] = Compose(i, j);
			IT[T[i][j]][i] = j;
		}
	} 
}
