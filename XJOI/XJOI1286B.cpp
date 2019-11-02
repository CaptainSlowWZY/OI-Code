#include <algorithm>
#include <cstdio>

typedef long long LL;

const int kMaxn = 1e5 + 5, kMaxm = 3e5 + 5;

struct Edge {
	int u, v, c;
	bool operator<(const Edge & e) const {
		return c < e.c;
	}
} E[kMaxm];

int n, m;
int A[kMaxn], B[kMaxn], fa[kMaxn];
LL sum, ans, tot[kMaxn];

inline int Find(int x) { return fa[x] == x ? x : (fa[x] = Find(fa[x])); }
void Merge(int, int, int);

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d", A + i, B + i);
		fa[i] = i, sum += (tot[i] = (LL)A[i] * B[i]);
	} ans = sum;
	for (int i = 0; i < m; ++i)
		scanf("%d%d%d", &E[i].u, &E[i].v, &E[i].c);
	std::sort(E, E + m);
	for (int i = 0, cnt = 0; i < m; ++i) {
		if (Find(E[i].u) == Find(E[i].v)) continue;
		Merge(E[i].u, E[i].v, E[i].c);
		if (++cnt == n - 1) break;
	} printf("%lld\n", ans);
	return 0;
}

void Merge(int x, int y, int c) {
//	printf(" %d, %d cost %d\n", x, y, c);
	sum -= tot[x = Find(x)] + tot[y = Find(y)];
	A[x] = std::max(A[x], std::max(c, A[y]));
	B[x] = std::min(B[x], B[y]), fa[y] = x;
	sum += (tot[x] = std::min(tot[x] + tot[y], (LL)A[x] * B[x]));
//	printf(" tot[%d] = %lld\n", x, tot[x]);
	ans = std::min(ans, sum);
}
