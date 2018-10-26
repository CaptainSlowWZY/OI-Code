// pigeon
#include <cstdio>
#include <algorithm>

#ifdef DEBUG_MD
	#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define debug(format, ...) 
#endif

const int MAXN = 2e5 + 10;

struct Opt {
	int tp, op1, op2, op3;
	Opt() { tp = 1; }
	Opt(int v_) : tp(2), op1(v_) {}
	Opt(int l_, int r_, int k_) : tp(3), op1(l_), op2(r_), op3(k_) {}
	operator int() const { return tp; }
} O[MAXN];

int N, M, rk, A[MAXN], num[MAXN << 1];

namespace FastIO {
	template <typename T>
		void read(T & x);
	template <typename T>
		void write(T x);
	template <typename T>
		inline void writeln(T x) {
			write(x), putchar('\n');
		}
}
namespace seg {
	const int ARSIZE = 3e5 + 10;

	int sz, lstsz, top;
	struct Node {
		int sum;
		Node *lson, *rson;
	} T[MAXN << 6], *root[ARSIZE];

	Node *build(int l, int r);
	Node *updata(int k, int l, int r, Node *hst);
	inline void init() {
		root[top = sz = lstsz = 0] = build(1, rk);
	}
	inline void push_back(int k) {
		lstsz = sz;
		root[top + 1] = updata(k, 1, rk, root[top]);
		++top;
	}
	inline void pop_back() { --top, sz = lstsz; }
	int query(int l, int r, int k);
}
inline int get_id(int v) {
	return std::lower_bound(num, num + rk, v) - num + 1;
}

int main() {
	using FastIO::read;

	read(N), read(M);
	for (int i = 0; i < N; i++) read(A[i]), num[rk++] = A[i];
	for (int i = 0, tp, v, l, r, k; i < M; i++) {
		read(tp);
		if (tp == 2) {
			read(v);
			O[i] = Opt(v);
			num[rk++] = v;
		}
		if (tp == 3) {
			read(l), read(r), read(k);
			O[i] = Opt(l, r, k);
		}
	}

	std::sort(num, num + rk);
	rk = std::unique(num, num + rk) - num;
	seg::init();
	for (int i = N - 1; i >= 0; i--) seg::push_back(get_id(A[i]));

	for (int i = 0; i < M; i++) {
		if (O[i] == 1) seg::pop_back();
		if (O[i] == 2) seg::push_back(get_id(O[i].op1));
		if (O[i] == 3) FastIO::writeln(seg::query(O[i].op1, O[i].op2, O[i].op3));
	}
	return 0;
}

namespace seg {
	Node *New() {
		T[sz].sum = 0, T[sz].lson = T[sz].rson = NULL;
		return &T[sz++];
	}

	Node *build(int l, int r) {
		Node *rt = New();
		if (l == r) return rt;
		int mid = l + r >> 1;
		rt->lson = build(l, mid);
		rt->rson = build(mid + 1, r);
		return rt;
	}

	Node *updata(int k, int l, int r, Node *hst) {
		Node *rt = New();
		rt->sum = hst->sum + 1, rt->lson = hst->lson, rt->rson = hst->rson;
		if (l == r) return rt;
		int mid = l + r >> 1;
		if (k <= mid) rt->lson = updata(k, l, mid, hst->lson);
		else rt->rson = updata(k, mid + 1, r, hst->rson);
		return rt;
	}

	int _query(Node *pre, Node *cur, int l, int r, int k) {
		if (l == r) return l;
		int sum = cur->lson->sum - pre->lson->sum, mid = l + r >> 1;
		if (k <= sum) return _query(pre->lson, cur->lson, l, mid, k);
		else return _query(pre->rson, cur->rson, mid + 1, r, k - sum);
	}

	int query(int l, int r, int k) {
		int len = r - l + 1;
		debug("query: from left to right[%d, %d], len=%d\n", l, r, len);
		l = top - r + 1, r = l + len - 1;
		debug("top=%d, [%d, %d]\n", top, l, r);
		return num[_query(root[l - 1], root[r], 1, rk, k) - 1];
	}
}
namespace FastIO {
	template <typename T>
		void read(T & x) {
			register char ch = getchar();
			for (; ch < '0' || ch > '9'; ch = getchar());
			for (x = 0; ch >= '0' && ch <= '9'; x = (x << 3) + (x << 1) + (ch ^ '0'), ch = getchar());
		}
	template <typename T>
		void write(T x) {
			if (!x) return (void)putchar('0');
			if (x < 0) x = -x, putchar('-');
			int arr[20], len = 0;
			for (; x; x /= 10) arr[len++] = x % 10;
			while (len) putchar(arr[--len] ^ '0');
		}
}

// AC!!!
