// BZOJ 1018
// SHOI 2008
#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>
#include <utility>

#define x first
#define y second
#define rg register
#define gch getchar
#ifdef DEBUG
	#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define debug(format, ...) 0
#endif

const int MAXN = 1e5 + 10;

typedef std::pair<int, int> Pii;

int N;
bool G[MAXN][2];

namespace SMT {
	struct Node {
		bool cnn[2][2];
		Node() {
//			memset(cnn, 0, sizeof cnn);
		}
		void set(bool f) {
			cnn[0][1] = cnn[1][0] = f;
//			return *this;
		}
/*		void out() const {
#ifdef DEBUG
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 2; j++) {
					debug("%d ", cnn[i][j]);
				}
				debug("%c", '\n');
			}
#endif
		}*/
		friend Node merge(const Node & n1, const Node & n2, int mid) {
			Node ret;
/*			debug(" __merging..., mid = %d\n", mid);
			debug(" OUT n1:%c", '\n');
			n1.out();
			debug(" OUT n2:%c", '\n');
			n2.out();*/
			for (int i1 = 0; i1 < 2; i1++)
				for (int i2 = 0; i2 < 2; i2++)
					ret.cnn[i1][i2] = n1.cnn[i1][0] && G[mid][0] && n2.cnn[0][i2] ||
									  n1.cnn[i1][1] && G[mid][1] && n2.cnn[1][i2];
//			debug(" OUT ret%c", '\n');
//			ret.out();
			return ret;
		}
	} T[MAXN << 1];

	int QL, QR, FG;

	void build(int l, int r);
	Node _Q(int l, int r);
	inline Node query(int l, int r) {
		QL = std::min(l, r), QR = std::max(l, r);
		return _Q(1, N);
	}
	void update(Pii p1, Pii p2, bool flag);
}
namespace FastIO {
	template <typename T>
		void read(T & x) {
			x = 0; rg char ch = gch();
			for (; !isdigit(ch); ch = gch());
			for (; isdigit(ch); ch = gch()) x = (x << 3) + (x << 1) + (ch ^ '0');
		}
}

Pii find(int l, int r, const Pii & p, int f);

int main() {
	using FastIO::read;
	read(N);
	SMT::build(1, N);

	char IN[10];
	for (Pii p1, p2; scanf("%s", IN) && IN[0] != 'E'; ) {
		read(p1.x), read(p1.y), read(p2.x), read(p2.y);
		--p1.x, --p2.x;
//		debug("__%s__ (%d, %d) (%d, %d)\n", IN, p1.x, p1.y, p2.x, p2.y);
		if (IN[0] == 'A') {
			if (p1.y > p2.y || p1.y == p2.y && p1.x > p2.x) std::swap(p1, p2);
			Pii lb = find(1, p1.y, p1, 0), ub = find(p2.y, N, p2, 1);
			putchar(SMT::query(lb.y, ub.y).cnn[lb.x][ub.x] ? 'Y' : 'N');
			putchar('\n');
		}
		else SMT::update(p1, p2, IN[0] == 'O');
	}
	return 0;
}

Pii find(int l, int r, const Pii & p, int f) {
//	f : 0 - most left, (l, r]; 1 - most - right, [l, r)
	f ? ++r : --l;
	SMT::Node tmp;
	for (int mid; r - l > 1; ) {
		mid = l + r >> 1;
		tmp = SMT::query(mid, p.y);
		if (f ? (tmp.cnn[p.x][0] || tmp.cnn[p.x][1]) : (tmp.cnn[0][p.x] || tmp.cnn[1][p.x])) {
			f ? l = mid : r = mid;
		}
		else f ? r = mid : l = mid; 
	}
	tmp = SMT::query(f ? l : r, p.y);
	return f ? Pii(tmp.cnn[p.x][1], l) : Pii(tmp.cnn[1][p.x], r);
}

namespace SMT {
	inline int id(int l, int r) {
		return l + r | l != r;
	}

#define lson id(l, mid)
#define rson id(mid + 1, r)

	void build(int l, int r) {
		int cur = id(l, r);
		memset(T[cur].cnn, 0, sizeof T[cur].cnn);
		if (l == r) {
			T[cur].cnn[0][0] = T[cur].cnn[1][1] = true;
			return;
		}
		int mid = l + r >> 1;
		build(l, mid), build(mid + 1, r);
	}
	Node _Q(int l, int r) {
		int cur = id(l, r);
//		debug("___Q [%d, %d], id = %d\n", l, r, id(l, r));
		if (QL <= l && r <= QR) return T[cur];
		int mid = l + r >> 1;
		if (QL <= mid && QR > mid) return merge(_Q(l, mid), _Q(mid + 1, r), mid);
		else if (QL <= mid) return _Q(l, mid);
		else return _Q(mid + 1, r);
	}
	void _UPD(int l, int r) {
//		debug("  __UPD [%d, %d]\n", l, r);
		int cur = id(l, r);
		if (l == r) {
/*			if (cur == 8) {
				puts("!!!!!!!");
				exit(0);
			}*/
			if (QL == QR) T[cur].set(FG);
			return;
		}
		int mid = l + r >> 1;
		if (QL <= l && r <= QR) {
			T[cur] = merge(T[lson], T[rson], mid);
			return ;
		}
		if (QL <= mid) _UPD(l, mid);
		if (mid < QR) _UPD(mid + 1, r);
		T[cur] = merge(T[lson], T[rson], mid);
	}
	void update(Pii p1, Pii p2, bool flag) {
		if (p1.y == p2.y) QL = QR = p1.y;
		else {
			if (p1.y > p2.y) std::swap(p1, p2);
			QL = p1.y, QR = p2.y, G[QL][p1.x] = flag;
		}
		FG = flag;
//		debug("QL = %d, QR = %d, FG = %d\n", QL, QR, FG);
		_UPD(1, N);
	}
}
