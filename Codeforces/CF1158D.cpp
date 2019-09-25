#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <map>
#include <queue>
#include <set>
#include <vector>

#define x first
#define y second
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

const int kMaxn = 2005;

int n, vis[kMaxn];
Pii P[kMaxn];
char S[kMaxn];

inline Pii operator-(const Pii & a, const Pii & b) {
	return {a.x - b.x, a.y - b.y};
}
inline LL operator*(const Pii & a, const Pii & b) {
	return 1ll * a.x * b.y - 1ll * b.x * a.y;
}

int main() {
	scanf("%d", &n);
	int s0 = 0;
	for (int i = 0; i < n; i++) {
		scanf("%d%d", &P[i].x, &P[i].y);
		if (P[i].y < P[s0].y || P[i].y == P[s0].y &&
			P[i].x < P[s0].x) s0 = i;
	}
	scanf("%s", S);
	vis[s0] = 1; printf("%d ", s0 + 1);
	for (int i = 0; i + 2 < n; i++) {
		int k = -1;
		for (int j = 0; j < n; j++) {
			if (vis[j]) continue;
			if (k == -1) { k = j; continue; }
			LL tmp = (P[k] - P[s0]) * (P[j] - P[s0]);
			if (S[i] == 'R') tmp = -tmp;
			if (tmp < 0) k = j;
		} printf("%d ", (s0 = k) + 1);
		vis[s0] = 1;
	}
	for (int i = 0; i < n; i++) {
		if (!vis[i]) {
			printf("%d\n", i + 1);
			return 0;
		}
	}
}
