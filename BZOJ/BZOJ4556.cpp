#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cassert>

const int kMaxn = 1e5 + 10, kLg = 19;

int n, m;
char S[kMaxn];

namespace sam {
	void Extend(int, int);
	void Init();
	bool Check(int, int, int, int);
}

int main() {
	scanf("%d%d%s", &n, &m, S);
	
	for (int i = 0; i < n; i++) sam::Extend(S[i] - 'a', i + 1);
	sam::Init();
	for (int i = 0, a, b, c, d; i < m; i++) {
		scanf("%d%d%d%d", &a, &b, &c, &d);
		int lb = 0, ub = std::min(b - a + 1, d - c + 1) + 1;
		for (int mid; ub - lb > 1; ) {
			mid = lb + ub >> 1;
			if (sam::Check(a + mid - 1, b, c + mid - 1, mid)) lb = mid;
			else ub = mid;
		}
		printf("%d\n", lb);
	}

	return 0;
}

namespace smt {
	struct Node {
		int sum, ls, rs;
#define lson(_) (T[_].ls)
#define rson(_) (T[_].rs)
	} T[kMaxn << 6];
	int size;

	inline int NewNode(int s) {	
		T[++size] = (Node){s, 0, 0};
		return size;
	}
	int Build(int val) {
		int rt = NewNode(1), l = 1, r = n;
		for (int mid, u = rt; l < r; ) {
			mid = l + r >> 1;
			if (val <= mid) {
				lson(u) = NewNode(1); u = lson(u); r = mid;
			} else {
				rson(u) = NewNode(1); u = rson(u); l = mid + 1;
			}
		}
		return rt;
	}
	int Merge(int l, int r, int rt1, int rt2) {
		if (!rt1 || !rt2) return rt1 + rt2;
		int u = NewNode(0);
		if (l < r) {
			int mid = l + r >> 1;
			lson(u) = Merge(l, mid, lson(rt1), lson(rt2));
			rson(u) = Merge(mid + 1, r, rson(rt1), rson(rt2));
			T[u].sum = T[lson(u)].sum + T[rson(u)].sum;
		} else T[u].sum = T[rt1].sum + T[rt2].sum;
		return u;
	}
	int Sum(int rt, int l, int r, int ql, int qr) {
		if (!rt) return 0;
		if (ql <= l && r <= qr) return T[rt].sum;
		int mid = l + r >> 1, res = 0;
		if (ql <= mid) res += Sum(lson(rt), l, mid, ql, qr);
		if (mid < qr) res += Sum(rson(rt), mid + 1, r, ql, qr);
		return res;
	}
}

namespace sam {
	const int kV = kMaxn << 1;

	int max[kV], A[kV][26], F[kV][kLg];
	int cnt[kMaxn], id[kV], root[kV], pos[kMaxn];
	int size = 1, last = 1;

#define par(_) (F[_][0])

	void Extend(int ch, int id) {
		int np = ++size, p = last;
		max[last = np] = max[p] + 1, pos[id] = np;
		root[np] = smt::Build(id);
		for (; p && !A[p][ch]; p = par(p)) A[p][ch] = np;
		if (!p) return (void)(par(np) = 1);
		int q = A[p][ch];
		if (max[p] + 1 == max[q]) par(np) = q;
		else {
			int nq = ++size; max[nq] = max[p] + 1;
			par(nq) = par(q), par(np) = par(q) = nq;
			memcpy(A[nq], A[q], sizeof(A[q]));
			for (; A[p][ch] == q; p = par(p)) A[p][ch] = nq;
		}
	}
	void Init() {
		for (int i = 1; i <= size; i++) ++cnt[max[i]];
		for (int i = 1; i <= n; i++) cnt[i] += cnt[i - 1];
		for (int i = 1; i <= size; i++) id[cnt[max[i]]--] = i;
		for (int i = 1; i < kLg; i++) {
			for (int j = 1; j <= size; j++) {
				F[j][i] = F[F[j][i - 1]][i - 1];
			}
		}
		for (int i = size, u; i; i--) {
			if (!par(u = id[i])) continue;
			root[par(u)] = smt::Merge(1, n, root[par(u)], root[u]);
		}
	}
	bool Check(int l, int r, int t, int len) {
		t = pos[t];
		for (int i = kLg - 1; i >= 0; i--) {
			if (max[F[t][i]] >= len) t = F[t][i];
		}
		return smt::Sum(root[t], 1, n, l, r);
	}
}
