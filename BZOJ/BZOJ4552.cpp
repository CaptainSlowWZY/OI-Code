// TJOI2016 & HEOI2016
#include <cstdio>

const int kMaxn = 1e5 + 10;

int n, m, pos;
int A[kMaxn], B[kMaxn], O[kMaxn], L[kMaxn], R[kMaxn];

namespace seg {
	int Build(int l, int r);
	int Query(int l, int r, int ql, int qr);
	int Modify(int l, int r, int ql, int qr, int cvr);
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", A + i);
	for (int i = 0; i < m; i++) scanf("%d%d%d", O + i, L + i, R + i);
	scanf("%d", &pos);

	int l = 1, r = n + 1;
	for (int mid; r - l > 1; ) {	// [l, r)
		mid = l + r >> 1;
	//	printf(" [%d, %d) mid = %d\n", l, r, mid);
		for (int i = 1; i <= n; i++) B[i] = A[i] >= mid;
	/*	for (int i = 1; i <= n; i++) {
			printf("%d%c", B[i], i == n ? '\n' : ' ');
		}*/
		using namespace seg;
		Build(1, n);
		for (int i = 0, cnt; i < m; i++) {
			cnt = Query(1, n, L[i], R[i]);
		/*	printf(" i = %d, [%d, %d], Oper %d, cnt = %d\n", 
					i, L[i], R[i], O[i], cnt);*/
			if (O[i]) {
				Modify(1, n, L[i], L[i] + cnt - 1, 1);
				Modify(1, n, L[i] + cnt, R[i], 0);
			} else {
				Modify(1, n, L[i], R[i] - cnt, 0);
				Modify(1, n, R[i] - cnt + 1, R[i], 1);
			}
		}
	//	printf("  result : %d\n", Query(1, n, pos, pos));
		if (Query(1, n, pos, pos)) l = mid;
		else r = mid;
	}
	printf("%d\n", l);
	return 0;
}

namespace seg {
	struct Node {
		int sum, tag;
	} T[kMaxn << 1];

	inline int Id(int l, int r) { return l + r | l != r; }
	int Build(int l, int r) {
		int rt = Id(l, r);
		T[rt].tag = -1;
		if (l == r) return T[rt].sum = B[l];
		int mid = l + r >> 1;
		return T[rt].sum = Build(l, mid) + Build(mid + 1, r);
	}
	void PushDown(int rt, int l, int r) {
		if (T[rt].tag == -1) return;
		int mid = l + r >> 1, ls = Id(l, mid), rs = Id(mid + 1, r);
		if (T[rt].tag) {
			T[ls].sum = mid - l + 1, T[rs].sum = r - mid;
		} else {
			T[ls].sum = T[rs].sum = 0;
		}
		T[ls].tag = T[rt].tag, T[rs].tag = T[rt].tag;
		T[rt].tag = -1;
	}
	int Query(int l, int r, int ql, int qr) {
		int rt = Id(l, r);
		if (ql <= l && r <= qr) return T[rt].sum;
	/*	printf("    query[%d, %d] cur[%d, %d], sum %d, tag %d\n",
				ql, qr, l, r, T[rt].sum, T[rt].tag);*/
		PushDown(rt, l, r);
		int mid = l + r >> 1;
		if (ql <= mid && qr > mid) {
			return Query(l, mid, ql, qr) + Query(mid + 1, r, ql, qr);
		} else if (ql <= mid) {
			return Query(l, mid, ql, qr);
		} else {
			return Query(mid + 1, r, ql, qr);
		}
	}
	int Modify(int l, int r, int ql, int qr, int cvr) {
		int rt = Id(l, r);
		if (l > qr || r < ql) return T[rt].sum;
		if (ql <= l && r <= qr) {
			T[rt].sum = cvr ? r - l + 1 : 0;
			T[rt].tag = cvr;
			return T[rt].sum; 
		}
		PushDown(rt, l, r);
		int mid = l + r >> 1;
		return T[rt].sum = Modify(l, mid, ql, qr, cvr) + 
				Modify(mid + 1, r, ql, qr, cvr);
	}
}
