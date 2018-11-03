// seg
#include <cstdio>
#include <cmath>

#ifdef DEBUG_MD
	#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define debug(format, ...) 0
#endif
#define rg register
#define gch getchar
#define pch putchar 

typedef long long LL;

const int MAXN = 1e5 + 500;
const int MOD = 998244353;

int N, Q;

namespace FastIO {
	template <typename T>
		void read(T & x);
	template <typename T>
		void write(T x);
	template <typename T>
		inline void writeln(T x) {
			write(x), pch('\n');
		}
}

namespace segtree {
	struct Node;
	int	QL, QR;
	LL kk;

	const Node & build(int l, int r);
	const Node & upd(int l, int r); 
	LL query(int l, int r, int md);
	inline void modify(int l, int r, LL k) {
		QL = l, QR = r, kk = k;
		upd(1, N);
	}
}

int main() {
	using FastIO::read;

	read(N);
	segtree::build(1, N);
	
	read(Q);
	for (rg int opt, l, r, k; Q--; ) {
		read(opt), read(l), read(r);
		if (opt == 1) {
			read(k);
			segtree::modify(l, r, k);
		}
		if (opt == 2) FastIO::writeln(segtree::query(l, r, 0));
		if (opt == 3) FastIO::writeln(segtree::query(l, r, 1));
	}

	return 0;
}

namespace segtree {
	struct Node {
		LL _or, sum1, sum2;
		Node() {}
		Node(LL v_) : sum2(v_ * v_ % MOD) { _or = sum1 = v_; }
		Node(LL _o, LL s1_, LL s2_) : _or(_o), sum1(s1_), sum2(s2_) {}
		Node operator+(const Node & n) const {
			return Node(_or | n._or, sum1 + n.sum1, (sum2 + n.sum2) % MOD);
		}
		Node & operator&=(LL k) {
			_or = sum1 &= k;
			sum2 = sum1 * sum1 % MOD;
			return *this;
		}
	} T[MAXN << 1];

	inline int get_id(int l, int r) {
		return l + r | l != r;
	}

	const Node & build(int l, int r) {
		int rt = get_id(l, r);
		if (l == r) {
			int tmp;
			FastIO::read(tmp);
			debug("building...\n read A_%d\n", l);
			return T[rt] = Node(tmp);
		}
		int mid = l + r >> 1;
		return T[rt] = build(mid + 1, r) + build(l, mid);
	}

	const Node & upd(int l, int r) { 
		debug(" upd[%d, %d]\n", l, r);
		int rt = get_id(l, r);
		if (r < QL || QR < l || (T[rt]._or & kk) == T[rt]._or) return T[rt];
		if (l == r) return T[rt] &= kk;
		int mid = l + r >> 1;
		return T[rt] = upd(l, mid) + upd(mid + 1, r);
	}

	LL _sum1(int l, int r) {
		int rt = get_id(l, r);
		if (r < QL || QR < l) return 0;
		if (QL <= l && r <= QR) return T[rt].sum1;
		int mid = l + r >> 1;
		return _sum1(l, mid) + _sum1(mid + 1, r);
	}

	LL _sum2(int l, int r) {
		int rt = get_id(l, r);
		if (r < QL || QR < l) return 0;
		if (QL <= l && r <= QR) return T[rt].sum2;
		int mid = l + r >> 1;
		return _sum2(l, mid) + _sum2(mid + 1, r);
	}

	LL query(int l, int r, int md) {
		QL = l, QR = r;
		LL s1 = _sum1(1, N);
		if (md) {
			LL s2 = _sum2(1, N);
			s1 %= MOD;
			return ((s2 * (r - l + 1) % MOD + s1 * s1 % MOD) << 1) % MOD;
		}
		return s1;
	}
}

namespace FastIO {
	template <typename T>
		void read(T & x) {
			rg char ch = gch(); rg int f = 0;
			for (; ch < '0' || ch > '9'; ch = gch()) f |= ch == '-';
			for (x = 0; ch >= '0' && ch <= '9'; ch = gch()) x = (x << 3) + (x << 1) + (ch ^ '0');
			if (f) x = ~x + 1;
		}
	template <typename T>
		void write(T x) {
			if (!x) return (void)pch('0');	
			if (x < 0) x = -x, pch('-');
			rg int arr[20], len = 0;
			for (; x; x /= 10) arr[len++] = x % 10;
			while (len) pch(arr[--len] ^ '0');
		}
}
