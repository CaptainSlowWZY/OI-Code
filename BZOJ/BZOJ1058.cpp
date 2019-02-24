// BZOJ 1058
// ZJOI 2007
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>
#include <set>

typedef std::multiset<int> Set;

const int MAXN = 5e5 + 10, INF = 0x3f3f3f3f;

int N, M, ming = INF;
std::vector<int> A[MAXN];
Set D;
char IN[20];

namespace Treap {
	struct Node {
		int val, rkey, cnt, ch[2];
		Node(int v_ = 0) :
			val(v_) {
			rkey = rand(), cnt = 1;
			ch[0] = ch[1] = 0;
		}
	} T[MAXN];
	int ROOT = 1, size = 1;

	int insert(int v_, int & u = ROOT);
	int prec(int v_, int u = ROOT);
	int succ(int v_, int u = ROOT);
	void debug() {
#ifdef DEBUG
		printf("===== DEBUG =====\n ROOT = %d\n", ROOT);
		for (int i = 1; i <= size; i++) {
			printf(" %d val = %d, rkey = %d, lson = %d, rson = %d\n", i, T[i].val, T[i].rkey, T[i].ch[0], T[i].ch[1]);
		}
		printf("===== ===== =====\n");
#endif
	}
	inline void init() {
		T[1] = Node(-INF);
		insert(INF);
	}
}

int main() {
	srand(19260817);
	scanf("%d%d", &N, &M);
	Treap::init();
	for (int i = 0, ai; i < N; i++) {
		scanf("%d", &ai);
		A[i].push_back(ai);
		if (Treap::insert(ai)) {
			Treap::debug();
			int pr = Treap::prec(ai), su = Treap::succ(ai);
#ifdef DEBUG
			printf(" A%d = %d, prec = %d, succ = %d\n", i, ai, pr, su);
#endif
			if (pr != -INF) pr = ai - pr;
			else pr = INF;
			if (su != INF) su = su - ai;
			ming = std::min(ming, std::min(pr, su));
		}
		else ming = 0;
	}
	for (int i = 1; i < N; i++) D.insert(abs(A[i][0] - A[i - 1][0]));

	for (int i, k; M--; ) {
		scanf("%s", IN);
		if (IN[0] == 'I') {
			scanf("%d%d", &i, &k);
			--i;
			if (ming) {
				if (Treap::insert(k)) {
					int pr = Treap::prec(k), su = Treap::succ(k);
					if (pr != -INF) pr = k - pr;
					else pr = INF;
					if (su != INF) su = su - k;
					else su = INF;
					ming = std::min(ming, std::min(pr, su));
				}
				else ming = 0;
			}
			if (i + 1 < N) {
				Set::iterator it = D.find(abs(A[i + 1].front() - A[i].back()));
				D.erase(it);
				D.insert(abs(k - A[i].back())), D.insert(abs(k - A[i + 1].front()));
			}
			else D.insert(abs(k - A[i].back()));
			A[i].push_back(k);
		}
		else if (IN[4] == 'G') printf("%d\n", *D.begin());
		else printf("%d\n", ming);
	}

	return 0;
}

namespace Treap {
	// notice the REFERENCE in the argument-list
	void rotate(int & u, int r) {
		int son = T[u].ch[r];
		T[u].ch[r] = T[son].ch[r ^ 1];
		T[son].ch[r ^ 1] = u;
		u = son;
	}
	int insert(int v_, int & u) {
		if (!u) {
			T[u = ++size] = Node(v_);
			return 1;
		}
		if (T[u].val == v_) {
			++T[u].cnt;
			return 0;
		}
		int r = T[u].val < v_;
		int tmp = insert(v_, T[u].ch[r]);
		if (T[u].rkey > T[T[u].ch[r]].rkey) rotate(u, r);
		return tmp;
	}
	int prec(int v_, int u) {
		if (!u) return -INF;
		if (T[u].val >= v_) return prec(v_, T[u].ch[0]);
		return std::max(T[u].val, prec(v_, T[u].ch[1]));
	}
	int succ(int v_, int u) {
		if (!u) return INF;
		if (T[u].val <= v_) return succ(v_, T[u].ch[1]);
		return std::min(T[u].val, succ(v_, T[u].ch[0]));
	}
}
