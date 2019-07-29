#include <algorithm>
#include <cstdio>

typedef long long LL;

const int kMaxn = 2e5 + 10;

int n, k, m;
LL A[kMaxn], sum[kMaxn];

bool Check(LL);

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d", &n, &k);
		LL lb = 0, ub = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%lld", sum + i);
			lb += std::min(sum[i], 0ll);
			ub += std::max(sum[i], 0ll);
			A[i] = sum[i] += sum[i - 1];
		}

		A[m = n + 1] = 0;
		std::sort(A + 1, A + m + 1);
		m = std::unique(A + 1, A + m + 1) - A - 1;
	//	puts("# MAP");
	//	for (int i = 1; i <= m; i++) printf("%lld%c", A[i], i == m ? '\n' : ' ');
		--lb;
	//	printf(" (%lld, %lld]\n", lb, ub);
	//	printf(" K = %d\n", k);
		for (LL mid; ub - lb > 1; ) {
			mid = (lb + ub) / 2;
			if (Check(mid)) ub = mid;
			else lb = mid;
		}
		printf("%lld\n", ub);
	}
	return 0;
}

namespace smt {
	int T[kMaxn << 1];

	inline int Id(int l, int r) { return l + r | l != r; }
	void Build(int l, int r) {
		T[Id(l, r)] = -1;
		if (l == r) return;
		int mid = l + r >> 1;
		Build(l, mid); Build(mid + 1, r);
	}
	int Query(int l, int r, int ql, int qr) {
		if (ql <= l && r <= qr) return T[Id(l, r)];
		int mid = l + r >> 1, res = -1;
		if (ql <= mid) res = Query(l, mid, ql, qr);
		if (qr > mid) res = std::max(res, Query(mid + 1, r, ql, qr));
		return res;
	}
	void Modify(int l, int r, int pos, int val) {
		int cur = Id(l, r);
		if (l == r) return (void)(T[cur] = std::max(T[cur], val));
		int mid = l + r >> 1;
		if (pos <= mid) Modify(l, mid, pos, val);
		else Modify(mid + 1, r, pos, val);
		T[cur] = std::max(T[Id(l, mid)], T[Id(mid + 1, r)]);
	//	printf("   .... after modify [%d, %d] = %d\n", l, r, T[cur]);
	}
}

inline int Index(LL x) {
	return std::lower_bound(A + 1, A + m + 1, x) - A;
}

bool Check(LL lim) {
//	printf(" Check %lld\n", lim);
	smt::Build(1, m);
	int fmx = 0;
	smt::Modify(1, m, Index(0), 0);
	for (int fi, i = 1; i <= n; i++) {
	//	printf("   i %d, [%lld, +inf) --> [%d, %d]\n", i, sum[i] - lim, Index(sum[i] - lim), m);
		fi = smt::Query(1, m, Index(sum[i] - lim), m) + 1;
		if (!fi) continue;
	//	printf("   fi = %d\n", fi);
		fmx = std::max(fmx, fi);
		smt::Modify(1, m, Index(sum[i]), fi);
	}
//	printf(" fmx = %d fmx >= %d ? %d###\n", fmx, k, fmx >= k);
	return fmx >= k;
}
