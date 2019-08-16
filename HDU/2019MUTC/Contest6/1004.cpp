#include <algorithm>
#include <cstdio>

typedef long long LL;
typedef std::pair<LL, LL> PLL;

const int kMaxn = 2.5e5 + 5;

typedef int IAr[kMaxn];

int n;
IAr A, B, id, rank;

namespace smt {
	void Build(int l, int r);
	void Insert(int l, int r, int pos, int va, int vb);
	PLL Query(int l, int r, int sa = 0, int sb = 0);
}
inline bool CmpR(int x, int y) {
	return 1.0 * A[x] / B[x] < 1.0 * A[y] / B[y];
}

int main() {
	int t;
	for (scanf("%d", &t); t--; ) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			scanf("%d%d", A + i, B + i);
			id[i] = i;
		} std::sort(id + 1, id + n + 1, CmpR);
		for (int i = 1; i <= n; i++) rank[id[i]] = i;

		smt::Build(1, n);
		for (int i = 1; i <= n; i++) {
			using namespace smt;
			Insert(1, n, rank[i], A[i], B[i]);
			PLL ans = Query(1, n);
			printf("%lld/%lld\n", ans.first, ans.second);
		}
	} return 0;
}

namespace smt {
	struct Node {
		int suma, sumb;
		Node operator+(const Node & n) const {
			return {suma + n.suma, sumb + n.sumb};
		}
	} T[kMaxn << 1];

	inline int Id(int l, int r) { return l + r | l != r; }
	void Build(int l, int r) {
		int cur = Id(l, r);
		T[cur] = {0, 0};
		if (l == r) return;
		int mid = l + r >> 1;
		Build(l, mid); Build(mid + 1, r);
	}
	void Insert(int l, int r, int pos, int va, int vb) {	
		int cur = Id(l, r);
		if (l == r) {
			T[cur].suma += va, T[cur].sumb += vb;
			return;
		} int mid = l + r >> 1;
		if (pos <= mid) Insert(l, mid, pos, va, vb);
		else Insert(mid + 1, r, pos, va, vb);
		T[cur] = T[Id(l, mid)] + T[Id(mid + 1, r)];
	}
	PLL Query(int l, int r, int sa, int sb) {
		if (l == r) {
			int cur = Id(l, r);
			LL f2 = T[cur].suma + T[cur].sumb,
			   f1 = 1ll * (sa + T[cur].suma - sb) *
				   T[cur].sumb + f2 * sb,
			   g = std::__gcd(f1, f2);
			return PLL(f1 / g, f2 / g);
		} int mid = l + r >> 1, ls = Id(l, mid),
			rs = Id(mid + 1, r);
		if (T[ls].suma + sa >= T[rs].sumb + sb)
			return Query(l, mid, sa, sb + T[rs].sumb);	
		return Query(mid + 1, r, sa + T[ls].suma, sb);
	}
}
