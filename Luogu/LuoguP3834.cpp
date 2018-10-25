// Luogu P3834
// Chair_man-tree template
#pragma GCC diagnostic error "-std=c++11"
#include <cstdio>
#include <map>

#ifdef LOCAL
	#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define debug(format, ...)
#endif
#define fir first
#define sec second

const int MAXN = 2e5 + 10;

int A[MAXN], N, M, val[MAXN], rk;
std::map<int, int> Mp;

namespace FastIO {
	template <typename T>
		void read(T & x) {
			register char ch = getchar();
			for (; ch < '0' || ch > '9'; ch = getchar());
			for (x = 0; ch >= '0' && ch <= '9'; x = (x << 3) + (x << 1) + (ch ^ '0'), ch = getchar());
		}
}
namespace seg {
	const int SEGSIZE = MAXN << 5;
	struct Node {
		int sum;
		Node *lson, *rson;
	} T[SEGSIZE];
	Node *root[MAXN];

	Node *build(int l, int r);
	Node *updata(int key, int l, int r, Node *hst);
	int _query(Node *pre, Node *cur, int l, int r, int k);
	inline void init() { root[0] = build(1, rk); }
	inline void insert(int pos, int key) {
		root[pos] = updata(key, 1, rk, root[pos - 1]);
	}
	inline int query(int l, int r, int k) {
		debug("querying [%d, %d], rank=%d\n", l, r, k);
		return _query(root[l - 1], root[r], 1, rk, k);
	}
}

int main() {
	using FastIO::read;

	read(N), read(M);	
	for (int i = 1; i <= N; i++) read(A[i]), Mp[A[i]] = 0;
//	for (auto i : Mp) i.sec = ++rk, val[rk] = i.fir;
	for (std::map<int, int>::iterator it = Mp.begin(); it != Mp.end(); ++it) it->sec = ++rk, val[rk] = it->fir;
#ifdef DEBUG_MD
	for (int i = 1; i <= rk; i++) debug("%d ", val[i]);
	putchar('\n');
	for (auto i : Mp) printf("%d -rank-> %d\n", i.fir, i.sec);
#endif
	seg::init();
	for (int i = 1; i <= N; i++) seg::insert(i, Mp[A[i]]);

	for (int l, r, k, i = 0; i < M; i++) {
		read(l), read(r), read(k);
		printf("%d\n", val[seg::query(l, r, k)]);
	}
	return 0;
}

namespace seg {
	int sz;

	Node *build(int l, int r) {
		Node *rt = &T[sz++];
		if (l == r) return rt;
		int mid = l + r >> 1;
		rt->lson = build(l, mid);
		rt->rson = build(mid + 1, r);
		return rt;
	}
		
	Node *updata(int key, int l, int r, Node *hst) {
		debug("updata : key=%d, [%d, %d]\n", key, l, r);
		Node *rt = &T[sz++];
		rt->lson = hst->lson, rt->rson = hst->rson, rt->sum = hst->sum + 1;
		if (l == r) return rt;
		int mid = l + r >> 1;
		if (key <= mid) rt->lson = updata(key, l, mid, hst->lson);
		else rt->rson = updata(key, mid + 1, r, hst->rson);
		return rt;
	}

	int _query(Node *pre, Node *cur, int l, int r, int k) {
		debug("  Q[%d, %d], k=%d\n", l, r, k);
		if (l == r) return l;
		int lsum = cur->lson->sum - pre->lson->sum, mid = l + r >> 1;
		debug("  !!lsum=%d\n", lsum);
		if (k <= lsum) return _query(pre->lson, cur->lson, l, mid, k);
		else return _query(pre->rson, cur->rson, mid + 1, r, k - lsum);
	}
}
