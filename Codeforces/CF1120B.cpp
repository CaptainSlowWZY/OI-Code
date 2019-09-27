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

const int kLim = 1e5, kMaxn = kLim + 5;

int n;
LL ans;
char A[kMaxn], B[kMaxn];

void Dfs(int i, int del);

int main() {
	scanf("%d%s%s", &n, A, B);
	for (int i = 0; i < n; i++) {
		A[i] ^= '0', B[i] ^= '0';
	} int la = A[0];
	for (int i = 0; i + 1 < n; i++) {
		ans += abs(B[i] - la);
		la = A[i + 1] + B[i] - la;
	}
	if (la != B[n - 1]) {
		puts("-1"); return 0;
	}
	printf("%lld\n", ans);
	ans = std::min(ans, (LL)kLim);
	for (int i = 0; i + 1 < n; i++) {
		while (A[i] != B[i]) {
			Dfs(i, A[i] < B[i] ? 1 : -1);
			if (!ans) break;
		} if (!ans) break;
	}
	return 0;
}

void Dfs(int i, int del) {
	if (!ans) return;
	if (A[i + 1] + del < 0 || A[i + 1] + del > 9)
		Dfs(i + 1, -del);
	if (!ans) return;
	printf("%d %d\n", i + 1, del);
	A[i] += del, A[i + 1] += del, --ans;
}
