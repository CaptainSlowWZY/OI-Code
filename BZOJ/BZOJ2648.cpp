// Sun Jiayu
// My 100-th accepted problem on bzoj
// Today is March 22, 2019. Two days before ZJOI 2019.
#pragma GCC optimize(2)
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cassert>

#define rg register

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

const int kMaxn = 5e5 + 10, kInf = 0x3f3f3f3f;
const int kAph = 0.723;

struct Point {
	int x, y;
	static bool dim;
	Point(int x_ = 0, int y_ = 0) : x(x_), y(y_) {}
	void set_dim(bool d) const { dim = d; }
	bool operator<(const Point & p) const {
		return dim ? (x == p.x ? y < p.y : x < p.x) :
			(y == p.y ? x < p.x : y < p.y);
	}
	friend int dist(const Point & p1, const Point & p2) {
		return std::abs(p1.x - p2.x) + std::abs(p1.y - p2.y);
	}
} P[kMaxn];
bool Point::dim;

int n, m;

#define ls ch[0]
#define rs ch[1]

namespace kdt {
	const int kSize = 1e6 + 10;
	struct Node *null, *pit;
	struct Node {
		Point slf, lb, rt;
		int sz;
		Node *ch[2];

		Node() {}
		Node(const Point & p) :
			slf(p), lb(p), rt(p) {
				ch[0] = ch[1] = null, sz = 1;
			}
		void *operator new (size_t) { return pit++; }
		void maintain() {
			lb.x = std::min(lb.x, std::min(ls->lb.x, rs->lb.x));
			lb.y = std::min(lb.y, std::min(ls->lb.y, rs->lb.y));
			rt.x = std::max(rt.x, std::max(ls->rt.x, rs->rt.x));
			rt.y = std::max(rt.y, std::max(ls->rt.y, rs->rt.y));
			sz = ls->sz + rs->sz + 1;
		}
		bool check() const {
			return ls->sz > sz * kAph || rs->sz > sz * kAph;
		}
		int dist(const Point & p) const {
			if (this == null) return kInf;
			return (p.x < lb.x || p.x > rt.x ? 
					(p.x < lb.x ? lb.x - p.x : p.x - rt.x) : 0) +
					(p.y < lb.y || p.y > rt.y ? 
					(p.y < lb.y ? lb.y - p.y : p.y - rt.y) : 0);
		}
	} T[kSize], *root, *rp, *rfa, *buf[kSize], **buffer;
	int size, rson, rdim, back;

	Node *Build(int l, int r, int dim);
	inline void Init() {
		pit = T;
		null = new Node();
		null->lb = Point(kInf, kInf);
		null->rt = Point(-kInf, -kInf);
		null->sz = 0;
		root = Build(0, n, 1);
	}
	void Query(Node *rt, const Point & p);
	void Modify(Node **rt, const Point & p, int dim);
	Node *Rebuild(int l, int r, int dim);
	void Kill(Node *rt);
}

int ans;

int main() {
	using fast_io::Read;

	Read(n), Read(m);
	for (rg int i = 0; i < n; i++) {
		Read(P[i].x), Read(P[i].y);
	}

	kdt::Init();

	for (rg int tp, x, y, cnt = 0; m--; ) {
		Read(tp), Read(x), Read(y);
		using namespace kdt;
		if (tp == 1) {
			rp = null;
			Modify(&root, Point(x, y), 1);
			if (rp != null) {
			//	if (++cnt < 12) continue;
				cnt = 0;
				if (rp == root) rfa = null;
				back = 0;
				Kill(rp);
			/*	for (int i = 0; i < back; i++) {
					printf("(%d, %d)%c",
							buf[i]->slf.x, buf[i]->slf.y,
							i + 1 == back ? '\n' : ' ');
				}*/
				buffer = buf;
				if (rfa != null) {
					rfa->ch[rson] = Rebuild(0, back, rdim);
					rfa->maintain();
				//	return 0;
				} else {
					root = Rebuild(0, back, rdim);
				}
			}
		} else {
			ans = kInf;
			Query(root, Point(x, y));
			fast_io::Println(ans);
		}
	}
	return 0;
}

namespace kdt {
	Node *Build(int l, int r, int dim) {
		if (l >= r) return null;
		int mid = l + r >> 1;
		P[l].set_dim(dim);
		std::nth_element(P + l, P + mid, P + r);
		Node *rt = new Node(P[mid]);
		rt->ls = Build(l, mid, dim ^ 1);
		rt->rs = Build(mid + 1, r, dim ^ 1);
		rt->maintain();
		return rt;
	}
	void Query(Node *rt, const Point & p) {
		if (rt == null) return;
		ans = std::min(ans, dist(rt->slf, p));
		int d = rt->ls->dist(p) > rt->rs->dist(p);
		Query(rt->ch[d], p);
		if (rt->ch[d ^ 1]->dist(p) < ans) Query(rt->ch[d ^ 1], p);
	}
	void Modify(Node **rt, const Point & p, int dim) {
		if (*rt == null) return (void)(*rt = new Node(p));
		(*rt)->slf.set_dim(dim);
		int d = (p < (*rt)->slf) ^ 1;
		Modify(&(*rt)->ch[d], p, dim ^ 1);
		(*rt)->maintain();
	//	rebuild-prework
		if (rp != null && (*rt)->check()) {
			rp = *rt;
			rdim = dim;
		}
		if (rp == (*rt)->ls) {
			rfa = *rt, rson = 0;
		}
		if (rp == (*rt)->rs) {
			rfa = *rt, rson = 1;
		}
	}
	Node *Rebuild(int l, int r, int dim) {
		if (l >= r) return null;
		int mid = l + r >> 1;
		P[l].set_dim(dim);
		std::nth_element(P + l, P + mid, P + r);
		Node *rt = *(buffer++);
		*rt = Node(P[mid]);
		rt->ls = Rebuild(l, mid, dim ^ 1);
		rt->rs = Rebuild(mid + 1, r, dim ^ 1);
		rt->maintain();
		return rt;
	}
	void Kill(Node *rt) {
		if (rt == null) return;
		P[back] = rt->slf, buf[back++] = rt;
		Kill(rt->ls), Kill(rt->rs);
	}
}
