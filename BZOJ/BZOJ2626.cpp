#include <cstdio>
#include <cctype>
#include <algorithm>
#include <vector>
#include <queue>

#define rg register
#define gch getchar
#define fir first
#define sec second
#ifdef DEBUG
	#define db(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define db(format, ...) 0
#endif

namespace fast_io {
	template <typename T>
		void Read(T & x) {
			rg char ch = gch(); rg bool f = false; x = 0;
			for (; !isdigit(ch); ch = gch()) f |= ch == '-';
			for (; isdigit(ch); ch = gch()) {
				x = (x << 3) + (x << 1) + (ch ^ '0');
			}
			f ? x = -x : 0;
		}
}
typedef long long LL;

const int kMaxn = 1e5 + 10, kInf = 0x3f3f3f3f;

inline LL Sqr(LL x) { return x * x; }

struct Point {
	int x, y, id;
	static bool dim;
	Point(int x_ = 0, int y_ = 0, int id_ = 0) :
		x(x_), y(y_), id(id_) {}	
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

int n, m;

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
			if (this == null) return -kInf;
			return std::max(std::max(Dist2(p, lb), Dist2(p, ub)),
					std::max(Dist2(p, Point(lb.x, ub.y)),
							Dist2(p, Point(ub.x, lb.y))));
		}
	} pool[kMaxn], *root;

	Node *Build(int fir, int lst, int dim);
	inline void Init() {
		pit = pool;
		null = new Node();
		null->lb = Point(kInf, kInf);
		null->ub = Point(-kInf, -kInf);
		root = Build(0, n, 1);
	}
	int Kth(const Point & p, int k);
}

int main() {
	using fast_io::Read;

	Read(n);
	for (int i = 0; i < n; i++) {
		Read(P[i].x), Read(P[i].y);
		P[i].id = i + 1;
	}

	kdt::Init();

	Read(m);
	for (int xi, yi, k; m--; ) {
		Read(xi), Read(yi), Read(k);
		printf("%d\n", kdt::Kth(Point(xi, yi), k));
	}
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

	typedef std::pair<LL, int> PLi;
	struct Greater {
		bool operator()(const PLi & p1, const PLi & p2) {
			return p1.fir > p2.fir ||
					p1.fir == p2.fir && p1.sec < p2.sec;
		}
	} cmp;
	std::priority_queue<PLi, std::vector<PLi>, Greater> hap;

	void Query(Node *rt, const Point & p) {
		if (rt == null) return;
		LL d[2] = {Dist2(p, rt->slf), 0};
	//	db(" rt(%d, %d) id %d, dist = %lld\n",
	//			rt->slf.x, rt->slf.y, rt->slf.id, d[0]);
		if (cmp.operator()(PLi(d[0], rt->slf.id), hap.top())) {
			hap.pop();
			hap.push(PLi(d[0], rt->slf.id));
		}
		d[0] = rt->ls->dist(p), d[1] = rt->rs->dist(p);
	//	db("   lson %lld, rson %lld\n", d[0], d[1]);
		int r = d[0] < d[1];
		Query(rt->ch[r], p);
		if (cmp.operator()(PLi(d[r ^ 1], rt->ch[r ^ 1]->slf.id),
							hap.top())) {
			Query(rt->ch[r ^ 1], p);
		}
	}
	int Kth(const Point & p, int k) {
		for (; !hap.empty(); hap.pop());
		for (int i = 0; i < k; i++) hap.push(PLi(-kInf, -1));
		Query(root, p);
		return hap.top().sec;
	}
}
