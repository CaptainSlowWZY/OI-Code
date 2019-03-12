#include <cstdio>
#include <cmath>
#include <algorithm>

#define blc(_) ((_ - 1) / Unsz + 1)

typedef long long LL;

const int kMaxn = 5e4 + 10;

int Unsz;

struct Query {
	int l, r, id;
	bool operator<(const Query & q) const {
		return blc(l) == blc(q.l) ? r < q.r : l < q.l;
	}
} qry[kMaxn];

int n, m, C[kMaxn], sum[kMaxn];
LL way, ans1[kMaxn], ans2[kMaxn];

inline void Vld(int p) {
	p ? way += sum[C[p]]++ : 0;
}
inline void InVld(int p) {
	p ? way -= (sum[C[p]]-- - 1) : 0;
}
inline LL C2(LL n) {
	return n * (n - 1) >> 1;
}

int main() {
	scanf("%d%d", &n, &m);
	Unsz = sqrt(n + 0.5);
	for (int i = 1; i <= n; i++) scanf("%d", C + i);
	for (int i = 0; i < m; i++) {
		scanf("%d%d", &qry[i].l, &qry[i].r);
		qry[i].id = i;
	}

	std::sort(qry, qry + m);
	int l = 0, r = 0;
	for (int i = 0; i < m; i++) {
		for (; r < qry[i].r; ) Vld(++r);
		for (; r > qry[i].r; ) InVld(r--);
		for (; l < qry[i].l; ) InVld(l++);
		for (; l > qry[i].l; ) Vld(--l);
		LL a2 = C2(r - l + 1), g = std::__gcd(way, a2);
		ans1[qry[i].id] = way / g;
		ans2[qry[i].id] = a2 / g;
	}
	
	for (int i = 0; i < m; i++) {
		printf("%lld/%lld\n", ans1[i], ans2[i]);
	}
	return 0;
}
