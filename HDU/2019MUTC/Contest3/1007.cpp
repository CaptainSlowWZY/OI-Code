#include <algorithm>
#include <cstdio>

typedef long long LL;

const int kMaxn = 2e5 + 10, kUb = 1e9;

namespace smt {
	struct Node {
		LL sum;
		int cnt, ch[2];
	} T[kMaxn * 20];
	int size, root;

#define lson(_) (T[_].ch[0])
#define rson(_) (T[_].ch[1])

	inline int NewNode() {
		T[++size] = (Node){0, 0, 0, 0};
		return size;
	}
	inline void Init() { size = 0; root = NewNode(); }
	void Insert(int & u, int l, int r, int val);
	int Query(int u, int l, int r, int lim);
}

int n, m;

int main() {
	int q;
	scanf("%d", &q);
	while (q--) {
		scanf("%d%d", &n, &m);
		smt::Init();
		for (int i = 0, ai; i < n; i++) {
			scanf("%d", &ai);
		//	printf("\n m - ai %d\n", m - ai);
			printf("%d ", i -
					smt::Query(smt::root, 1, kUb, m - ai));
			smt::Insert(smt::root, 1, kUb, ai);
		}
		putchar('\n');
	}
	return 0;
}

namespace smt {
	inline void Maintain(int u) {
		T[u].sum = T[lson(u)].sum + T[rson(u)].sum;
		T[u].cnt = T[lson(u)].cnt + T[rson(u)].cnt;
	}
	void Insert(int & u, int l, int r, int val) {
		if (!u) u = NewNode();
		if (l == r) {
			T[u].sum += val, ++T[u].cnt;
			return;
		}
		int mid = l + r >> 1;
		if (val <= mid) Insert(lson(u), l, mid, val);
		else Insert(rson(u), mid + 1, r, val);
		Maintain(u);
	}
	int Query(int u, int l, int r, int lim) {
	//	printf("\n query %d(%lld, %d), [%d, %d], lim %d\n", u, T[u].sum, T[u].cnt, l, r, lim);
		if (!u) return 0;
		if (lim >= T[u].sum) return T[u].cnt;
		if (l == r) return std::min(T[u].cnt, lim / l);
		int mid = l + r >> 1, res = 0;
		if (lim <= T[lson(u)].sum) return Query(lson(u), l, mid, lim);
		return T[lson(u)].cnt +
			Query(rson(u), mid + 1, r, lim - T[lson(u)].sum);
	}
}
