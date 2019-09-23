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

typedef long long LL;
typedef std::pair<int, int> Pii;

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

const int kMaxn = 1e5 + 5;

int n, m;
int B[kMaxn], G[kMaxn];

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) scanf("%d", B + i);
	for (int i = 0; i < m; i++) scanf("%d", G + i);

	std::sort(B, B + n); std::sort(G, G + m);
	if (B[n - 1] > G[0]) {
		puts("-1"); return 0;
	}
	int pb = n - 1, pg = m - 1, rem = m;
	LL ans = 0;
	while (pb >= 0 && pg >= 0) {
		if (rem > 1) {
			ans += G[pg--];
			--rem;
		} else {
			if (B[pb] == G[pg]) ans += G[pg--];
			else ans += B[pb];
			rem = m, --pb;
		}
	}
	if (pg >= 0) {
		puts("-1"); return 0;
	} ans += 1ll * rem * B[pb];
	for (int i = 0; i < pb; i++)
		ans += 1ll * m * B[i];
	printf("%lld\n", ans);
	return 0;
}
