#include <algorithm>
#include <cstdio>

#define x first
#define y second

const int kMaxn = 3e5 + 10;

typedef long long LL;
typedef LL LAr[kMaxn];
typedef std::pair<LL, LL> Pll;

const LL kInf64 = 0x7f7f7f7f7f7f7f7f;

int n, m;
LAr H, ans;
Pll S[kMaxn], K[kMaxn];

inline long double Inter(const Pll & l1, const Pll & l2) {
	return (l2.y - l1.y) / (long double)(l1.x - l2.x);
}
inline LL F(const Pll & l, LL x) {
	return l.x * x + l.y;
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) scanf("%lld", H + i);
	int top = 0;
	for (int i = n - 1; i >= 0; i--) {
		Pll l(i + 1, H[i]);
		for (; top > 1 && Inter(S[top - 1], S[top - 2]) >= 
				Inter(S[top - 1], l); --top);
		S[top++] = l;
	}
	for (int i = 0; i < m; i++) {
		scanf("%lld", &K[i].x);
		K[i].y = i;
	}
	
	std::sort(K, K + m);
	for (int i = 0, j = 0; i < m; i++) {
		for (; j + 1 < top &&
				F(S[j + 1], K[i].x) <= F(S[j], K[i].x); j++);
		ans[K[i].y] = F(S[j], K[i].x);
	}
	for (int i = 0; i < m; i++) printf("%lld ", ans[i]);
	putchar('\n');
	return 0;
}
