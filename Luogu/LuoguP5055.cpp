#include <algorithm>
#include <cstdio>
#include <cstdlib>

const int kMaxn = 2e5 + 10, kInf = 0x7fffffff;

typedef long long LL;

int n;

namespace treap {
	int root[kMaxn];
	int size, vrsn;

	void Insert(int his, int pos, int val);
	void Erase(int his, int pos);
	void Flip(int his, int l, int r);
	LL Sum(int his, int l, int r);
}

int main() {
	srand(19260817);
	scanf("%d", &n);
	LL lastans = 0, p, x, l, r;
	for (int v, opt; n--; ) {
		scanf("%d%d", &v, &opt);
		using namespace treap;
		switch (opt) {
			case 1 :
				scanf("%lld%lld", &p, &x);
				p ^= lastans, x ^= lastans;
				Insert(v, p, x); break;
			case 2 :
				scanf("%lld", &p);
				p ^= lastans;
				Erase(v, p); break;
			case 3 :
				scanf("%lld%lld", &l, &r);
				l ^= lastans, r ^= lastans;
				Flip(v, l, r); break;
			case 4 :
				scanf("%lld%lld", &l, &r);
				l ^= lastans, r ^= lastans;
				printf("%lld\n", lastans = Sum(v, l, r));
		}
	}
	return 0;
}

namespace treap {
	struct Node {
		int val, rkey, rev;
		LL sum;
		int sz, ch[2];
		Node() {}
		Node(int v_) :
			val(v_), rkey(rand()), sum(v_), sz(1) {
				ch[0] = ch[1] = rev = 0;
			}
	} T[kMaxn * 60];

#define lson(_) (T[_].ch[0])
#define rson(_) (T[_].ch[1])

	inline int NewNode(int val) {
		T[++size] = val;
		return size;
	}
	inline int NewNode(const Node & n) {
		T[++size] = n;
		return size;
	}
	inline void Maintain(int u) {
		T[u].sz = 1 + T[lson(u)].sz + T[rson(u)].sz;
		T[u].sum = T[u].val + T[lson(u)].sum + T[rson(u)].sum;
	}
	void PushDown(int u) {
		if (!T[u].rev) return;
		std::swap(lson(u), rson(u));
		if (lson(u)) {
			lson(u) = NewNode(T[lson(u)]);
			T[lson(u)].rev ^= 1;
		}
		if (rson(u)) {
			rson(u) = NewNode(T[rson(u)]);
			T[rson(u)].rev ^= 1;
		}
		T[u].rev = 0;
	}
	void Split(int u, int k, int & rt1, int & rt2) {
		if (!u) return (void)(rt1 = rt2 = 0);
		PushDown(u);
		if (T[lson(u)].sz + 1 <= k) {
			rt1 = NewNode(T[u]);
			Split(rson(u), k - T[lson(u)].sz - 1, rson(rt1), rt2);
			Maintain(rt1);
		} else {
			rt2 = NewNode(T[u]);
			Split(lson(u), k, rt1, lson(rt2));
			Maintain(rt2);
		}
	}
	int Merge(int rt1, int rt2) {
		PushDown(rt1); PushDown(rt2);
		if (!rt1 || !rt2) return rt1 + rt2;
		if (T[rt1].rkey < T[rt2].rkey) {
			rson(rt1) = Merge(rson(rt1), rt2); Maintain(rt1);
			return rt1;
		} else {
			lson(rt2) = Merge(rt1, lson(rt2)); Maintain(rt2);
			return rt2;
		}
	}
	int Merge(int rt1, int rt2, int rt3) {
		return Merge(rt1, Merge(rt2, rt3));
	}
	void Insert(int his, int pos, int val) {
		int rt1, rt2;
		Split(root[his], pos, rt1, rt2);
		root[++vrsn] = Merge(rt1, NewNode(val), rt2);
	}
	void Erase(int his, int pos) {
		int rt1, rt2, rt3;
		Split(root[his], pos, rt1, rt3);
		Split(rt1, pos - 1, rt1, rt2);
		root[++vrsn] = Merge(rt1, rt3);
	}
	void Flip(int his, int l, int r) {
		int rt1, rt2, rt3;
		Split(root[his], r, rt1, rt3);
		Split(rt1, l - 1, rt1, rt2);
		if (rt2) T[rt2].rev ^= 1;
		root[++vrsn] = Merge(rt1, rt2, rt3);
	}
	LL Sum(int his, int l, int r) {
		int rt1, rt2, rt3, osize = size;
		Split(root[his], r, rt1, rt3); 
		Split(rt1, l - 1, rt1, rt2);
		LL res = T[rt2].sum;
		root[++vrsn] = Merge(rt1, rt2, rt3);
		return res;
	}
}
