// Luogu P3835
#include <cstdio>
#include <cstdlib>
#include <ctime>

#define lson(_) T[_].ch[0]
#define rson(_) T[_].ch[1]
#ifdef DEBUG
	#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define debug(format, ...) 0
#endif

const int MAXN = 5e5 + 10;

namespace treap {
	int root[MAXN], VERSION, totn;
	void insert(int ver, int val);
	void erase(int ver, int val);
	int rank(int ver, int v_);
	int _KTH(int rt, int k);
	inline int kth(int ver, int k) {
		root[++VERSION] = root[ver];
		return _KTH(root[ver], k);
	}
	int prec(int ver, int v_);
	int succ(int ver, int v_);
	void Debug();
}

int main() {
	srand((unsigned)time(NULL));
	int O;
	scanf("%d", &O);
	for (int ver, opt, x; O--; ) {
		scanf("%d%d%d", &ver, &opt, &x);
		using namespace treap;
		switch (opt) {
			case 1	:
				insert(ver, x);
				break;
			case 2	:
				erase(ver, x);
				break;
			case 3	:
				printf("%d\n", rank(ver, x));
				break;
			case 4	:
				printf("%d\n", kth(ver, x));
				break;
			case 5	:
				printf("%d\n", prec(ver, x));
				break;
			case 6	:
				printf("%d\n", succ(ver, x));
		}
		debug("------ ------ ------%c", '\n');
		Debug();
	}
	return 0;
}

namespace treap {
	struct Node {
		int val, rkey, sz, ch[2];
		Node() {}
		Node(int v_) :
			val(v_), rkey(rand()), sz(1) {
			ch[0] = ch[1] = 0;
		}
	} T[MAXN * 50];

	inline int new_node(int v_) {
		T[++totn] = Node(v_);
		return totn;
	}
	inline int new_node(const Node & n) {
		T[++totn] = n;
		return totn;
	}
	inline void maintain(int rt) {
		T[rt].sz = 1 + T[lson(rt)].sz + T[rson(rt)].sz;
	}
	void split(int rt, int v_, int & r1, int & r2) {
		if (!rt) return (void)(r1 = r2 = 0);
		if (T[rt].val <= v_) {
			r1 = new_node(T[rt]);
			split(rson(rt), v_, rson(r1), r2);
			maintain(r1);
		}
		else {
			r2 = new_node(T[rt]);
			split(lson(rt), v_, r1, lson(r2));
			maintain(r2);
		}
	}
	int merge(int r1, int r2) {
		if (!r1 || !r2) return r1 + r2;
//		int cur;
		if (T[r1].rkey < T[r2].rkey) {
//			cur = new_node(T[r1]);
//			rson(cur) = merge(rson(cur), r2);
			rson(r1) = merge(rson(r1), r2);
			maintain(r1);
			return r1;
		}
		else {
//			cur = new_node(T[r2]);
//			lson(cur) = merge(r1, lson(cur));
			lson(r2) = merge(r1, lson(r2));
			maintain(r2);
			return r2;
		}
//		maintain(cur);
//		return cur;
	}
	void insert(int ver, int val) {
		debug("\n====== Insert ======%c", '\n');
		int rt1 = 0, rt2 = 0;
		debug(" root_ver  %d\n", root[ver]);
		split(root[ver], val, rt1, rt2);
		debug(" Insert val %d into version %d\n", val, ver);
		debug(" Succ split: rt1 = %d, rt2 = %d\n", rt1, rt2);
		root[++VERSION] = merge(rt1, merge(new_node(val), rt2));
		debug(" new root of version %d.0 is %d\n", VERSION, root[VERSION]);
	}
	void erase(int ver, int val) {
		debug("\n====== Erase ======%c", '\n');
		int rt1 = 0, rt2 = 0, rt3 = 0;
		split(root[ver], val, rt1, rt3);
		debug(" root_ver = %d\n", root[ver]);
		split(rt1, val - 1, rt1, rt2);
		debug(" Erase val %d from version %d\n", val, ver);
		debug(" Succ split: rt1 = %d, rt2 = %d, rt3 = %d\n", rt1, rt2, rt3);
		root[++VERSION] = merge(rt1, merge(merge(lson(rt2), rson(rt2)), rt3));
		debug(" new root of version %d.0 is %d\n", VERSION, root[VERSION]);
	}
	int rank(int ver, int v_) {
		int rt1 = 0, rt2 = 0, totn0 = totn;
		split(root[ver], v_ - 1, rt1, rt2);
		totn = totn0, root[++VERSION] = root[ver];
		return T[rt1].sz + 1;
	}
	int _KTH(int rt, int k) {
		for (; ; ) {
			if (k <= T[lson(rt)].sz) rt = lson(rt);
			else if (k > T[lson(rt)].sz + 1) {
				k -= T[lson(rt)].sz + 1;
				rt = rson(rt);
			}
			else return T[rt].val;
		}
		return -1;
	}
	int prec(int ver, int v_) {
		int rt1 = 0, rt2 = 0, totn0 = totn;
		split(root[ver], v_ - 1, rt1, rt2);
		totn = totn0, root[++VERSION] = root[ver];
		if (!rt1) return -2147483647;
		return _KTH(rt1, T[rt1].sz);
	}
	int succ(int ver, int v_) {
		int rt1 = 0, rt2 = 0, totn0 = totn;
		split(root[ver], v_, rt1, rt2);
		totn = totn0, root[++VERSION] = root[ver];
		if (!rt2) return 2147483647;
		return _KTH(rt2, 1);
	}
	void Debug() {
		debug("\n====== Out Treap ======%c", '\n');
		debug(" totn = %d\n", totn);
#ifdef DEBUG
		for (int i = 0; i <= totn; i++) {	
			debug(" Node %d : {val %d, randkey %d, sz %d, lson %d, rson %d}\n", i, T[i].val, T[i].rkey, T[i].sz, lson(i), rson(i));
		}
#endif
		debug("====== E   N   D ======%c", '\n');
	}
}
