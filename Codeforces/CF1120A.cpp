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

const int kMaxn = 5e5 + 5;

int n, k, m, s;
int A[kMaxn], B[kMaxn], cnt[kMaxn];
int cnt0[kMaxn], vis[kMaxn], flag[kMaxn];

// inline int Calc(int x) { return x - x / k * k; }

int main() {
	scanf("%d%d%d%d", &m, &k, &n, &s);
	for (int i = 0; i < m; i++) scanf("%d", A + i);
	for (int i = 0; i < s; i++) {
		scanf("%d", B + i);
		++cnt[B[i]], ++cnt0[B[i]], vis[B[i]] = 1;
	}

	int l = 0, r = 0, rem = s;
	while (l <= r) {
		if (l == r && r == m) break;
		while (r < m && (rem > 0 || r - l < k)) {
			if (vis[A[r]]) {
				if (--cnt[A[r]] >= 0) --rem;
			} ++r;
		}
	//	printf(" [%d, %d)\n", l, r);
		if (r == m && (rem || r - l < k)) break;
		if (l / k + (m - r) / k + 1 >= n) {
			int fcnt = std::min(l / k, n - 1);
			printf("%d\n", m - n * k);
			for (int i = fcnt * k; i < l; i++) {
				printf("%d ", i + 1);
			}
			int bas = 0;
			for (int i = l; i < r; i++) {
				if (vis[A[i]] && cnt0[A[i]] > 0) {
					--cnt0[A[i]]; flag[i] = 1, ++bas;
				//	printf(" i = %d\n", i);
				}
			}
			int take = k - bas;
			for (int i = l; i < r; i++) {
				if (flag[i]) continue;
				if (take > 0) { --take; continue; }
				printf("%d ", i + 1);
			}
			int bcnt = n - 1 - fcnt;
		//	printf(" r = %d, bcnt = %d\n", r, bcnt);
			for (int i = r + bcnt * k; i < m; i++) {
				printf("%d ", i + 1);
			} pch('\n'); return 0;
		}
		if (vis[A[l]]) {
			if (++cnt[A[l]] > 0) ++rem;
		} ++l;
	} puts("-1");
	return 0;
}
