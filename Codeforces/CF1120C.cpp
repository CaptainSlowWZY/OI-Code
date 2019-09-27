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

const int kMaxn = 5e3 + 5;

int n, a, b;
int DP[kMaxn];
char S[kMaxn];

bool Match(int m1, int m2, int p1, int p2);

int main() {
	scanf("%d%d%d%s", &n, &a, &b, S);
	std::fill(DP, DP + n + 1, kInf);
	DP[0] = 0;
	for (int i = 1; i <= n; i++) {
		UMin(DP[i], DP[i - 1] + a);
		int l = i + 1, r = std::min(i + i, n), ans = -1;
		for (int mid; l <= r; ) {
			mid = l + r >> 1;
			if (Match(i, mid, 0, i)) {
				ans = mid; l = mid + 1;
			} else r = mid - 1;
		}
		for (int j = i + 1; j <= ans; j++)
			UMin(DP[j], DP[i] + b);
	}
	printf("%d\n", DP[n]);
	return 0;
}

bool Match(int m1, int m2, int p1, int p2) {
	int ml = m2 - m1, mp = p2 - p1;
	if (ml > mp) return false;
	static int nxt[kMaxn];
	nxt[0] = nxt[1] = 0;
	for (int p, j, i = m1 + 1; i < m2; i++) {
		for (j = nxt[p = i - m1]; j &&
			S[i] != S[m1 + j]; j = nxt[j]);
		nxt[p + 1] = S[i] == S[m1 + j] ? j + 1 : 0;
	}
	for (int i = p1, j = 0; i < p2; i++) {
		while (S[i] != S[m1 + j] && j) j = nxt[j];
		if (S[i] == S[m1 + j]) ++j;
		if (j == ml) return true;
	} return false;
}
