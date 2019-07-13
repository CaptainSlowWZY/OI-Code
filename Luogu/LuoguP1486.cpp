#include <cstdio>
#include <cstdlib>

const int kMaxn = 3e5 + 10;

int n, min;
char IN[5];

namespace treap {
	struct Node {
		int slr, rkey, tag;
		int sz, ch[2];
		Node() {}
		Node(int s) :
			slr(s), rkey(rand()), sz(1) {
				ch[0] = ch[1] = tag = 0;
			}
	} T[kMaxn];
	int ROOT, size;

	void Insert(int);
	void Split(int, int, int &, int &);
	int Kth(int);
	inline void Change(int u, int del) {
		T[u].slr += del, T[u].tag += del;
	}
}

int main() {
	srand(19260817);
	scanf("%d%d", &n, &min);
	int sum = 0;
	for (int k, rt1, rt2; n--; ) {
		scanf("%s%d", IN, &k);
		using namespace treap;
		switch (IN[0]) {
			case 'I' :
				if (k >= min) Insert(k);
				break;
			case 'A' :
				Change(ROOT, k); break;
			case 'S' :
				Change(ROOT, -k);
				Split(ROOT, min - 1, rt1, rt2);
				sum += T[rt1].sz; ROOT = rt2; break;
			case 'F' :
				if (k > T[ROOT].sz) puts("-1");
				else {
					k = T[ROOT].sz - k + 1;
					printf("%d\n", Kth(k));
				}
				break;
		}
	}
	printf("%d\n", sum); 
	return 0;
}

namespace treap {
#define lson(_) (T[_].ch[0])
#define rson(_) (T[_].ch[1])
	inline int NewNode(int salary) {
		T[++size] = salary;
		return size;
	}
	inline void Maintain(int u) {
		T[u].sz = 1 + T[lson(u)].sz + T[rson(u)].sz;
	}
	void PushDown(int u) {
		if (T[u].tag) {
			if (lson(u)) Change(lson(u), T[u].tag);
			if (rson(u)) Change(rson(u), T[u].tag);
			T[u].tag = 0;
		}
	}
	void Split(int u, int bd, int & rt1, int & rt2) {
		if (!u) return (void)(rt1 = rt2 = 0);
		PushDown(u);
		if (T[u].slr <= bd) {
			rt1 = u; Split(rson(u), bd, rson(u), rt2);
		} else {
			rt2 = u; Split(lson(u), bd, rt1, lson(rt2));
		}
		Maintain(u);
	}
	int Merge(int rt1, int rt2) {
		if (!rt1 || !rt2) return rt1 + rt2;
		if (T[rt1].rkey < T[rt2].rkey) {
			rson(rt1) = Merge(rson(rt1), rt2); Maintain(rt1);
			return rt1;
		} else {
			lson(rt2) = Merge(rt1, lson(rt2)); Maintain(rt2);
			return rt2;
		}
	}
	void Insert(int salary) {
		int rt1, rt2;
		Split(ROOT, salary, rt1, rt2);
		ROOT = Merge(rt1, Merge(NewNode(salary), rt2));
	}
	int Kth(int k) {
		for (int u = ROOT; ; ) {
			PushDown(u);
			if (k <= T[lson(u)].sz) u = lson(u);
			else if (k > T[lson(u)].sz + 1) {
				k -= T[lson(u)].sz + 1; u = rson(u);
			} else return T[u].slr;
		}
		return -1;
	}
}
