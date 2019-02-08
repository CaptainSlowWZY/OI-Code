// Luogu P3391
// Splay
#include <cstdio>
#include <algorithm>
#include <vector>

class Splay {
private:
	struct Node {
		int val, sz, tag;	// tag - have been fliped or not
	/*	Notice!
	 *	This time we uses splay-tree to maintian itervals
	 *	so val is not the key-value!
	 */
		Node *fa, *ch[2];
		Node(int v_, Node *fa_ = NULL) : val(v_), fa(fa_), tag(0) {
			ch[0] = ch[1] = NULL, sz = 1;
		}
		int relat() const {
			return this == fa->ch[0] ? 0 : 1;
		}
		void reset() {
			sz = 1 + (ch[0] ? ch[0]->sz : 0) + (ch[1] ? ch[1]->sz : 0);
		}
		int lsize() const {
			return ch[0] ? ch[0]->sz : 0;
		}
		Node *push_down() {
			if (tag) {
				std::swap(ch[0], ch[1]);
				if (ch[0]) ch[0]->tag ^= 1;
				if (ch[1]) ch[1]->tag ^= 1;
				tag = 0;
			}
			return this;
		}
	} *root;

	Node *build(const int arr[], int l, int r, Node *fa) {
		if (l > r) return NULL;
		int mid = l + r >> 1;
		Node *cur = new Node(arr[mid], fa);
		if (l != r) {
			cur->ch[0] = build(arr, l, mid - 1, cur);
			cur->ch[1] = build(arr, mid + 1, r, cur);
			cur->reset();
		}
		return cur;
	}
	void rotate(Node *u) {
		Node *prf = u->fa->push_down();
		int r = u->push_down()->relat();
		u->fa = prf->fa;
		if (prf->fa) prf->fa->ch[prf->relat()] = u;
		if (u->ch[r ^ 1]) u->ch[r ^ 1]->fa = prf;
		prf->ch[r] = u->ch[r ^ 1];
		prf->fa = u, u->ch[r ^ 1] = prf;
		prf->reset(), u->reset();
		if (!u->fa) root = u;
	}
	Node *splay(Node *u, Node *trgt = NULL) {
		while (u->fa != trgt) {
			if (u->fa->push_down()->fa == trgt) rotate(u->push_down());
			else if (u->fa->relat() == u->push_down()->relat()) {
				rotate(u->fa);
				rotate(u);
			}
			else {
				rotate(u), rotate(u);
			}
		}
		return u;
	}
	Node *select(int k) {
		++k;
		Node *v = root;
		while (k != v->push_down()->lsize() + 1) {
			if (k < v->lsize() + 1) v = v->ch[0];
			else {
				k -= v->lsize() + 1;
				v = v->ch[1];
			}
		}
		return splay(v);
	}
	void dfs(Node *u, std::vector<int> & V) {
		u->push_down();
		if (u->ch[0]) dfs(u->ch[0], V);
		if (~u->val) V.push_back(u->val);
		if (u->ch[1]) dfs(u->ch[1], V);
	}
public:
	Splay() {
		root = NULL;
	}
	void build(int arr[], int n) {
	//	the first element in the array should be indexed 1
		arr[0] = -1, arr[n + 1] = -1;
		root = build(arr, 0, n + 1, NULL);
	}
	void flip(int l, int r) {
		Node *ub = select(r + 1), *lb = select(l - 1);
		splay(lb);
		splay(ub, lb);
		ub->ch[0]->tag ^= 1;
	}
	void get_ans(std::vector<int> & V) {
		dfs(root, V);
	}
} T;

int N, M, A[100005];
std::vector<int> ans;

int main() {
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; i++) A[i] = i;
	T.build(A, N);
	for (int l, r; M--; ) {
		scanf("%d%d", &l, &r);
		T.flip(l, r);
	}
	T.get_ans(ans);
	for (auto i : ans) printf("%d ", i);
	putchar('\n');
	return 0;
}