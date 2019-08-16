#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <stack>

typedef long long LL;

const int kMaxn = 3e5 + 5;

struct Node {
	LL lb, ub, sz;
	int rkey, ch[2];
	Node() {}
	Node(LL lb_, LL ub_) :
		lb(lb_), ub(ub_), rkey(rand()) {
			ch[0] = ch[1] = 0; sz = ub_ - lb_;
		}
} T[kMaxn * 5];
int size, top, pool[kMaxn * 5];

int NewNode(const Node & n) {
	if (top) {
		T[pool[top - 1]] = n; return pool[--top];
	} else {
		T[++size] = n; return size;
	}
}
inline void Release(int id) { pool[top++] = id; }

class FT {
// Fhq Treap
private:
/*	std::vector<Node> T;
	std::stack<int> pool;*/
	int root;
#define LSON(_) (T[_].ch[0])
#define RSON(_) (T[_].ch[1])
	void maintain(int u) {
		T[u].sz = T[u].ub - T[u].lb + T[LSON(u)].sz + T[RSON(u)].sz;
	}
	int merge(int u, int v);
	void split(int u, LL & k, int & rt1, int & rt2, int & rt3);
public:
	FT() { root = 0; }
	Node pop_kth(LL k);
	void push_back(const Node & n) {
		root = merge(root, NewNode(n));
	}
} seq[kMaxn];

#define rg register
#define GCH getchar()

namespace fast_io {
	template <typename T>
		void Read(T & x) {
			rg char ch = GCH; x = 0;
			for (; !isdigit(ch); ch = GCH);
			for (; isdigit(ch); ch = GCH)
				x = (x << 3) + (x << 1) + (ch ^ '0');
		}
}

int n, m, q;

int main() {
	srand(19260817);
	using fast_io::Read;
	Read(n); Read(m); Read(q);
	for (LL i = 1; i <= n; i++) {
		seq[i].push_back(Node((i - 1) * m + 1, i * m));
		seq[0].push_back(Node(i * m, i * m + 1));
	}
	for (int x, y; q--; ) {
		Read(x); Read(y);
		Node z = y == m ? seq[0].pop_kth(x) : seq[x].pop_kth(y);
		printf("%lld\n", z.lb);
		if (y < m)
			seq[x].push_back(seq[0].pop_kth(x));
		seq[0].push_back(z);
	} return 0;
}

void FT::split(int u, LL & k, int & rt1, int & rt2, int & rt3) {
/*	fprintf(stderr, " split k %lld, %d, [%lld, %lld), ls %d(%lld), rs %d(%lld)\n",
		k, u, T[u].lb, T[u].ub, LSON(u), T[LSON(u)].sz, RSON(u),
			T[RSON(u)].sz);*/
	if (!u) { return (void)(rt1 = rt3 = 0); }
	if (T[LSON(u)].sz >= k) {
	//	printf("  Case 1, goto %d(sz = %d)\n", LSON(u), T[LSON(u)].sz);
		split(LSON(u), k, rt1, rt2, LSON(rt3 = u));
	} else if (T[LSON(u)].sz + T[u].ub - T[u].lb < k) {
		k -= T[LSON(u)].sz + T[u].ub -T[u].lb;
	//	printf("  Case 2, goto %d(sz = %d)\n", RSON(u), T[RSON(u)].sz);
		split(RSON(u), k, RSON(rt1 = u), rt2, rt3);
	} else {
	//	printf("  Case 3, u = %d\n", u);
		rt1 = LSON(u), rt3 = RSON(u); rt2 = u;
		k -= T[LSON(u)].sz, LSON(u) = RSON(u) = 0;
	} maintain(u);
}

int FT::merge(int u, int v) {
	if (!u || !v) return u + v;
	if (T[u].rkey < T[v].rkey) {
		RSON(u) = merge(RSON(u), v); maintain(u); return u;
	} LSON(v) = merge(u, LSON(v)); maintain(v); return v;
}

Node FT::pop_kth(LL k) {
	int rt1, rt2, rt3;
	split(root, k, rt1, rt2, rt3);	
	Node p = T[rt2]; Release(rt2);
	if (k > 1) rt1 = merge(rt1, NewNode(Node(p.lb, p.lb + k - 1)));
	if (p.lb + k < p.ub)
		rt3 = merge(NewNode(Node(p.lb + k, p.ub)), rt3);
	root = merge(rt1, rt3);
	return Node(p.lb + k - 1, p.lb + k);
}
