#include <algorithm>
#include <cstdio>

const int kMaxn = 1e5 + 10;

struct Element {
	int val, l, r, id, dp;
	bool operator<(const Element & e) const {
		return id < e.id;
	}
} A[kMaxn];

int n, m, maxv;

template <typename T> inline
void UMin(T & x, const T & y) {
	if (x > y) x = y;
}
template <typename T> inline
void UMax(T & x, const T & y) {
	if (x < y) x = y;
}
inline bool CmpV(const Element & a, const Element & b) {
	return a.val <= b.val;
}
inline bool CmpL(const Element & a, const Element & b) {
	return a.l <= b.l;
}
void Solve(int, int);

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%d", &A[i].val);
		A[i].l = A[i].r = A[i].val;
		A[i].dp = 1, A[i].id = i;
	}
	for (int i = 0, x, y; i < m; i++) {
		scanf("%d%d", &x, &y);
		UMin(A[--x].l, y); UMax(A[x].r, y);
	}
	for (int i = 0; i < n; i++) UMax(maxv, A[i].r);

	Solve(0, n);
	int ans = 0;
	for (int i = 0; i < n; i++) UMax(ans, A[i].dp);
	printf("%d\n", ans);
	return 0;
}

namespace bit {
	int T[kMaxn];

	void Modify(int p, int v) {
		for (; p <= maxv; p += p & -p) UMax(T[p], v);
	}
	int Query(int p) {
		int res = 0;
		for (; p; p &= p - 1) UMax(res, T[p]);
		return res;
	}
	void Clear(int p) {
		for (; p <= maxv; p += p & -p) T[p] = 0;
	}
}

void Solve(int l, int r) {
	if (r - l <= 1) return;
	int mid = l + r >> 1;
//	printf(" Solve [%d, %d)\n", l, r);
	Solve(l, mid);
	std::sort(A + l, A + mid, CmpV);
	std::sort(A + mid, A + r, CmpL);
	int p1 = l, p2 = mid;
	while (p1 < mid && p2 < r) {
		if (A[p1].val <= A[p2].l) {
			bit::Modify(A[p1].r, A[p1].dp);
			++p1;
		} else {
			UMax(A[p2].dp, bit::Query(A[p2].val) + 1);
			++p2;
		}
	}
	while (p2 < r) {
		UMax(A[p2].dp, bit::Query(A[p2].val) + 1);
		++p2;
	}
	while (p1-- > l) bit::Clear(A[p1].r);
	std::sort(A + mid, A + r);
	Solve(mid, r);
}
