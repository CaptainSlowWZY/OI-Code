#include <cstdio>
#include <cctype>
#include <algorithm>
#include <vector>
#include <queue>

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
}

typedef long long LL;

const int kMaxn = 1e5 + 10;
const LL kInf64 = 0x3f3f3f3f3f3f3f3f;

inline LL Sqr(LL x) { return x * x; }

struct Point {
	LL x, y;
	static bool dim;
	Point(LL x_ = 0, LL y_ = 0) :
		x(x_), y(y_) {}	
	static void set_dims(bool d) { dim = d; }
	bool operator<(const Point & p) const {
		return dim ? (x == p.x ? y < p.y : x < p.x) :
			(y == p.y ? x < p.x : y < p.y);
	}
	friend LL Dist2(const Point & p1, const Point & p2) {
		return Sqr(p1.x - p2.x) + Sqr(p1.y - p2.y);
	}
} P[kMaxn];
bool Point::dim;

#define ls ch[0]
#define rs ch[1]

int n, k;

namespace kdt {
	struct Node *null, *pit;
	struct Node {
		Point slf, lb, ub;
		Node *ch[2];
		Node() {}
		Node(const Point & p) :
			slf(p), lb(p), ub(p) {
				ch[0] = ch[1] = null;
			}
		void *operator new (size_t) { return pit++; }
		void maintain() {
			lb.x = std::min(lb.x, std::min(ls->lb.x, rs->lb.x));
			lb.y = std::min(lb.y, std::min(ls->lb.y, rs->lb.y));
			ub.x = std::max(ub.x, std::max(ls->ub.x, rs->ub.x));
			ub.y = std::max(ub.y, std::max(ls->ub.y, rs->ub.y));
		}
		LL dist(const Point & p) const {
			return this == null ? -kInf64 :
					std::max(
					std::max(Dist2(p, lb), Dist2(p, ub)),
					std::max(Dist2(p, Point(lb.x, ub.y)),
							Dist2(p, Point(ub.x, lb.y))));
		}
	} pool[kMaxn], *root;

	Node *Build(int fir, int lst, int dim);
	inline void Init() {
		pit = pool;
		null = new Node();
		null->lb = Point(kInf64, kInf64);
		null->ub = Point(-kInf64, -kInf64);
		root = Build(0, n, 1);
	}
	void Query(Node *rt, const Point & p);
}

std::priority_queue<LL, std::vector<LL>, std::greater<LL> > hap;

int main() {
	using fast_io::Read;

	Read(n), Read(k);
	for (int i = 0; i < n; i++) {
		Read(P[i].x), Read(P[i].y);
	}

	kdt::Init();

	for (int i = 0; i < k + k; i++) {
		hap.push(-kInf64);
	}
	for (int i = 0; i < n; i++) kdt::Query(kdt::root, P[i]);

	printf("%lld\n", hap.top());
	return 0;
}

namespace kdt {
	Node *Build(int fir, int lst, int dim) {
		if (fir >= lst) return null;
		int mid = fir + lst >> 1;
		Point::set_dims(dim);
		std::nth_element(P + fir, P + mid, P + lst);
		Node *rt = new Node(P[mid]);
		rt->ls = Build(fir, mid, dim ^ 1);
		rt->rs = Build(mid + 1, lst, dim ^ 1);
		rt->maintain();
		return rt;
	}
	void Query(Node *rt, const Point & p) {
		if (rt == null) return;
		LL d[2] = {Dist2(rt->slf, p), 0};
		if (d[0] > hap.top()) {
			hap.pop();
			hap.push(d[0]);
		}
		d[0] = rt->ls->dist(p), d[1] = rt->rs->dist(p);
		int r = d[0] < d[1];
		Query(rt->ch[r], p);
		if (d[r ^ 1] > hap.top()) Query(rt->ch[r ^ 1], p);
	}
}
