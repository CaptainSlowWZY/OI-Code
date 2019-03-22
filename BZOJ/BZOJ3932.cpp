// CQOI 2015
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <vector>
#include <cassert>

namespace fast_io {
	template <typename T>
		void Read(T & x) {
			register char ch = getchar();
			register bool f = false; x = 0;
			for (; !isdigit(ch); f |= (ch == '-'), ch = getchar());
			for (; isdigit(ch); ch = getchar())
				x = (x << 3) + (x << 1) + (ch ^ '0');
			f ? x = -x : 0;
		}
	template <typename T>
		void Print(T x) {
			if (!x) return (void)(putchar('0'));
			if (x < 0) x = -x, putchar('-');
			register int arr[20], len = 0;
			for (; x; arr[len++] = x % 10, x /= 10);
			while (len) putchar(arr[--len] ^ '0');
		}
	template <>
		void Print(const char * buff) {
			for (register int i = 0; buff[i]; ++i) putchar(buff[i]);
		}
	template <typename T>
		inline void Println(T x) {
			Print(x), putchar('\n');
		}
}

#ifdef DEBUG
	#define db(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define db(format, ...) 0
#endif

typedef long long LL;

const int kMaxn = 1e5 + 10;

int m, n, rank;
int rev[kMaxn];
std::vector<int> tas[kMaxn];

namespace smt {
	struct Node {
		int cnt;
		LL sum;
		int lson, rson;
	} T[kMaxn * 40];
	int size, val, sgn, last, root[kMaxn];
	
	int Build(int l, int r);
	int Modify(int prv, int l, int r);
	inline void Insert(int pos, int val_, int sgn_, int flag) {
		if (flag) last = size;
		val = val_, sgn = sgn_;
		db("  Insert at %d, val %d, sign %d, flag %d\n",
					pos, val, sgn, flag);
		root[pos] = Modify(flag ? root[pos - 1] : root[pos],
							1, rank);
	}
	LL Q(int cur, int l, int r, int k);
	inline LL Query(int pos, int k) {
		return Q(root[pos], 1, rank, k);
	}
}

int main() {
	using fast_io::Read;

	Read(m), Read(n);
	for (int i = 1, Si, Ei, Pi; i <= m; i++) {
		Read(Si), Read(Ei), Read(Pi);
		rev[i] = Pi;
		tas[Si].push_back(Pi);
		tas[Ei + 1].push_back(-Pi);
	}
	
	std::sort(rev + 1, rev + m + 1);
	rank = std::unique(rev + 1, rev + m + 1) - rev - 1;
//	rank = m;
	smt::root[0] = smt::Build(1, rank);
	for (int i = 1, cur, sgn, f; i <= n; i++) {
		db("TIME %d\n", i);
		f = 1;
		for (std::vector<int>::iterator it = tas[i].begin();
				it != tas[i].end(); ++it) {
			cur = std::abs(*it), sgn = *it < 0 ? -1 : 1;
			db(" insert %d, sign %d\n", cur, sgn);
			smt::Insert(i,
					std::lower_bound(rev + 1, rev + rank + 1, cur) - rev,
				   	sgn, f);
			f = 0;
		}
		if (f) smt::root[i] = smt::root[i - 1];
	}

	LL lastans = 1;
	for (int i = 0, Xi, Ai, Bi, Ci, Ki; i < n; i++) {
		Read(Xi), Read(Ai), Read(Bi), Read(Ci);
		Ki = 1 + (1ll * Ai * lastans + Bi) % Ci;
	//	printf(" Query %d at %d\n", Ki, Xi);
		assert(Ki >= 0);
		lastans = smt::Query(Xi, Ki);
		fast_io::Println(lastans);
	}
	return 0;
}

#define lson(_) (T[_].lson)
#define rson(_) (T[_].rson)
#define cnt(_) (T[_].cnt)
#define sum(_) (T[_].sum)

namespace smt {
	int Build(int l, int r) {
		int rt = size++;
		if (l == r) return rt;
		int mid = l + r >> 1;
		lson(rt) = Build(l, mid);
		rson(rt) = Build(mid + 1, r);
		return rt;
	}
	int Modify(int prv, int l, int r) {
		db("  Modify [%d, %d] val = %d, sgn = %d\n", l, r, val, sgn);
		int rt = prv >= last ? prv : size++;
		db("  RT %d\n", rt);
	//	int rt = size++;
		lson(rt) = lson(prv), rson(rt) = rson(prv);
		cnt(rt) = cnt(prv) + sgn, sum(rt) = sum(prv) + rev[val] * sgn;
		db("    cnt %d, sum %lld\n", cnt(rt), sum(rt));
		if (l == r) return rt;
		int mid = l + r >> 1;
		if (val <= mid) lson(rt) = Modify(lson(prv), l, mid);
		else rson(rt) = Modify(rson(prv), mid + 1, r);
		return rt;
	}
	LL Q(int cur, int l, int r, int k) {
		db(" RT %d [%d, %d], count = %d\n", cur, l, r, cnt(cur));
		assert(cnt(cur) >= 0);
		if (cnt(cur) <= k) return sum(cur);
		if (l == r) return 1ll * std::min(k, cnt(cur)) * rev[l];
		int mid = l + r >> 1;
		if (k <= cnt(lson(cur))) return Q(lson(cur), l, mid, k);
		else return sum(lson(cur)) +
					Q(rson(cur), mid + 1, r, k - cnt(lson(cur)));
	}
}
