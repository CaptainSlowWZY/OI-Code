#include <algorithm>
#include <cstdio>
#include <cctype>
#include <queue>
#include <vector>

typedef std::pair<int, int> Pii;

const int kMaxn = 7e4 + 10, kMaxm = 1.5e5 + 10, kInf = 0x3f3f3f3f;

using std::min;
using std::max;

#define CP const Point
#define fir first
#define sec second
#define rg register

struct Point {
	int x, y, id;
	static int dim;
	Point(int x_ = 0, int y_ = 0, int id_ = 0) :
		x(x_), y(y_), id(id_) {}
	static void set_dim(int d) { dim = d; }
	bool operator<(CP & p) const {
	//	dim 1 - x, 0 - y
		return dim ? (x == p.x ? y < p.y : x < p.x) :
			(y == p.y ? x < p.x : y < p.y);
	}
	friend inline bool Less(CP & p1, CP & p2) {
		return dim ? p1.x < p2.x : p1.y < p2.y;
	}
	friend inline bool LessEq(CP & p1, CP & p2) {
		return dim ? p1.x <= p2.x : p1.y <= p2.y;
	}
} P[kMaxn];
int Point::dim;

struct Device {
	int id, next;
} Dv[kMaxm];

#define forto(_) for (int d = back[_], v = Dv[d].id; d; \
		v = Dv[d = Dv[d].next].id)

int n, m, w, h, totd, top;
int back[kMaxn], vis[kMaxn], dis[kMaxn], S[kMaxn];
int T[kMaxm], L[kMaxm], R[kMaxm], D[kMaxm], U[kMaxm];
std::priority_queue<Pii, std::vector<Pii>, std::greater<Pii> > hap;

namespace fast_io {
#define gch getchar
	template <typename T>
		void Read(T & x) {
			rg char ch = gch(); x = 0;
			for (; !isdigit(ch); ch = gch());
			for (; isdigit(ch); ch = gch()) x = (x << 3) + (x << 1) + (ch ^ '0');
		}
#undef gch
}
namespace kdt {
	struct Node *root;
	void Init();
	void Query(CP & lb, CP & ub, int dim, Node *cur = root);
}
inline void AddDevice(int u, int v) {
	Dv[++totd] = (Device){v, back[u]}, back[u] = totd;
}

int main() {
#ifndef LOCAL
	freopen("jump.in", "r", stdin);
	freopen("jump.out", "w", stdout);
#endif
	using fast_io::Read;
	Read(n); Read(m); Read(w); Read(h);
	for (int i = 0; i < n; i++) {
		Read(P[i].x); Read(P[i].y);
		P[i].id = i + 1;
	}
	for (int i = 0, Pi; i < m; i++) {
		Read(Pi); Read(T[i]); Read(L[i]);
		Read(R[i]); Read(D[i]); Read(U[i]);
		AddDevice(Pi, i);
	}

	kdt::Init();
	vis[1] = 1; dis[1] = 0;
	forto(1) hap.push(Pii(T[v], Dv[d].id));
	for (Pii cur; !hap.empty(); ) {
		cur = hap.top(), hap.pop(); top = 0;
		int k = cur.sec;
	/*	printf(" x[%d, %d], y[%d, %d], dis %d\n",
				L[k], R[k], D[k], U[k], cur.fir);*/
		kdt::Query(Point(L[k], D[k]), Point(R[k], U[k]), 1);
	/*	printf(" top = %d\n", top);
		for (int i = 0; i < top; i++) printf(" %d", S[i]);
		putchar('\n');*/
		if (!top) continue;
		for (int u; top; ) {
			dis[u = S[--top]] = cur.fir;
			forto(u)
				hap.push(Pii(cur.fir + T[v], v));
		}
	}

	for (int i = 2; i <= n; i++) printf("%d\n", dis[i]);
#ifndef LOCAL
	fclose(stdin); fclose(stdout);
#endif
	return 0;
}

namespace kdt {
	struct Node *pit, *null;
	struct Node {
		Point slf, lb, ub;
		int rem;
		Node *ch[2];
#define ls ch[0]
#define rs ch[1]
		Node() {}
		Node(CP & p) :
			slf(p), lb(p), ub(p) {
				ch[0] = ch[1] = null;
				rem = 1;
			}
		void *operator new(size_t) { return pit++; }
		void maintain() {
			lb.x = min(lb.x, min(ls->lb.x, rs->lb.x));
			lb.y = min(lb.y, min(ls->lb.y, rs->lb.y));
			ub.x = max(ub.x, max(ls->ub.x, rs->ub.x));
			ub.y = max(ub.y, max(ls->ub.y, rs->ub.y));
		}
	} pool[kMaxn];

	Node *Build(int fir, int lst, int dim) {
		if (fir >= lst) return null;
		Point::set_dim(dim);
		int mid = fir + lst >> 1;
		std::nth_element(P + fir, P + mid, P + lst);
		Node *cur = new Node(P[mid]);
		cur->ls = Build(fir, mid, dim ^ 1);
		cur->rs = Build(mid + 1, lst, dim ^ 1);
		cur->maintain(); cur->rem = 1 + cur->ls->rem + cur->rs->rem;		
		return cur;
	}
	void Init() {
		pit = pool; null = new Node();
		null->lb = Point(kInf, kInf), null->ub = Point(-kInf, -kInf);
		null->rem = 0; root = Build(0, n, 1);
	}
	inline bool InRec(CP & u, CP & lb, CP & ub) {
		return lb.x <= u.x && u.x <= ub.x &&
			lb.y <= u.y && u.y <= ub.y;
	}
	void Query(CP & lb, CP & ub, int dim, Node *cur) {
	//	lb - left & bottem, ub - right & top
		if (cur == null || !cur->rem) return;
		Point::set_dim(dim);
	/*	printf(" lb(%d, %d) ub(%d, %d), d %d, u(%d, %d)\n",
				lb.x, lb.y, ub.x, ub.y, dim, cur->slf.x, cur->slf.y);*/
		if (LessEq(lb, cur->slf) && LessEq(cur->slf, ub)) {
			if (InRec(cur->slf, lb, ub) && !vis[cur->slf.id]) {
				S[top++] = cur->slf.id; vis[cur->slf.id] = 1;
			}
			Query(lb, ub, dim ^ 1, cur->ls);
			Query(lb, ub, dim ^ 1, cur->rs);
		} else if (LessEq(cur->slf, lb)) Query(lb, ub, dim ^ 1, cur->rs);
		else Query(lb, ub, dim ^ 1, cur->ls);
		cur->rem = !vis[cur->slf.id] + cur->ls->rem + cur->rs->rem;
	}
}
