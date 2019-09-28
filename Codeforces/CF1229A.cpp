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

typedef long long LL;
typedef unsigned long long ULL;
typedef std::pair<int, int> Pii;
typedef std::vector<int> Vi;

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

const int kMaxn = 7005;

int n;
LL A[kMaxn];
int B[kMaxn], cnt[kMaxn], dsc[kMaxn];
Vi in[kMaxn];

inline bool Check(int a, int b) { return A[a] & ~A[b]; }

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%lld", A + i);
		for (int j = 0; j < i; j++) {
			if (Check(i, j)) { ++cnt[i]; in[j].pb(i); }
			if (Check(j, i)) { ++cnt[j]; in[i].pb(j); }
		}
	}
	for (int i = 0; i < n; i++) scanf("%d", B + i);
	int rem = n;
	while (true) {
		int suc = 1;
		for (int i = 0; i < n; i++) {
			if (dsc[i]) continue;
			if (cnt[i] + 1 == rem) {
				for (auto j : in[i]) {
					if (dsc[j]) continue;
					--cnt[j];
				} --rem; suc = 0; dsc[i] = 1; break;
			}
		} if (suc) break;
	}
	LL ans = 0;
	for (int i = 0; i < n; i++) {
		if (dsc[i]) continue;
		ans += B[i];
	} printf("%lld\n", ans);
	return 0;
}
