#include <algorithm>
#include <cstdio>

#define x first
#define y second

typedef std::pair<int, int> Pii;
typedef long long LL;

const int kMaxn = 2e5 + 5;

int n, nx;
Pii P[kMaxn];
int X[kMaxn];

namespace smt {
	int T[kMaxn << 1];
	void Modify(int l, int r, int p);
	int Query(int l, int r, int ql, int qr);
}
inline bool CmpY(const Pii & a, const Pii & b) {
	return a.y > b.y || a.y == b.y && a.x < b.x;
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d%d", &P[i].x, &P[i].y);
		X[i] = P[i].x;
	}
	std::sort(X, X + n); std::sort(P, P + n, CmpY);
	nx = std::unique(X, X + n) - X;
	for (int i = 0; i < n; i++)
		P[i].x = std::lower_bound(X, X + nx, P[i].x) - X + 1;
	int top = 0;
	LL ans = 0;
	smt::Modify(1, nx, P[0].x);
	for (int i = 1; i < n; i++) {
		using namespace smt;
		if (P[i].y == P[top].y) {
			Modify(1, nx, P[i].x);
			continue;
		}
	//	printf(" y = %d, [%d, %d)\n", P[top].y, top, i);
		for (int j = top, la = 0; j < i; j++) {
		/*	printf(" ans0 = %lld\n", ans);
			printf("   query for [%d, %d] & [%d, %d]\n",
					la + 1, P[j].x - 1, P[j].x + 1, nx); */
			ans += 1ll * (Query(1, nx, la + 1,
				P[j].x - 1) + 1) * 
				(Query(1, nx, P[j].x + 1, nx) + 1);
		//	printf(" ans1 = %lld\n", ans);
			la = P[j].x;
		} top = i; Modify(1, nx, P[i].x);
	} 
//	printf(" y = %d, [%d, %d)\n", P[top].y, top, n);
	for (int i = top, la = 0; i < n; i++) {
	//	printf(" ans0 = %lld\n", ans);
		ans += 1ll * (smt::Query(1, nx, la + 1, P[i].x - 1) + 1) * 
			(smt::Query(1, nx, P[i].x + 1, nx) + 1);
	//	printf(" ans1 = %lld\n", ans);
		la = P[i].x;
	}
	printf("%lld\n", ans);
	return 0;
}

namespace smt {
	inline int Id(int l, int r) { return l + r | l != r; }
	void Modify(int l, int r, int p) {
		int cur = Id(l, r);
		if (l == r) return (void)(T[cur] = 1);
		int mid = l + r >> 1;
		if (p <= mid) Modify(l, mid, p);
		else Modify(mid + 1, r, p);
		T[cur] = T[Id(l, mid)] + T[Id(mid + 1, r)];
	}
	int Query(int l, int r, int ql, int qr) {
		if (ql > qr) return 0;
		if (ql <= l && r <= qr) return T[Id(l, r)];
		int mid = l + r >> 1, res = 0;
		if (ql <= mid) res = Query(l, mid, ql, qr);
		if (qr > mid) res += Query(mid + 1, r, ql, qr);
		return res;
	}
}
