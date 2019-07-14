#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>

using std::max;

const int kMaxn = 4.5e6 + 10;
const int NULTAG = 0x3f3f3f3f;

int n, m;
int A[kMaxn];
char IN[10];

namespace treap {
	struct Node {
		int val, sz, rkey, ch[2];
		int sum, lsum, msum, rsum;
		int tag, rev;
		Node() {}
		Node(int v_) :
			val(v_), sz(1), rkey(rand()) {
				ch[0] = ch[1] = rev = 0;
				msum = sum = val;
				lsum = rsum = std::max(val, 0);
				tag = NULTAG;
			}
	} T[kMaxn];
	int ROOT, size;

	void Debug() {
		puts(" # DEBUG");
		for (int i = 1; i <= size; i++) {
			printf("   %d val %d, sz %d, ls %d, rs %d, ",
					i, T[i].val, T[i].sz, T[i].ch[0], T[i].ch[1]);
			printf("sum %d, lsum %d, rsum %d, msum %d, ", T[i].sum,
					T[i].lsum, T[i].rsum, T[i].msum);
			printf("tag %d, rev %d\n", T[i].tag, T[i].rev);
		}
	}
	void Delete(int pos, int num);
	void Insert(int pos, int c[], int num);
	void Reverse(int pos, int num);
	void Set(int pos, int num, int val);
	int Sum(int pos, int num);
}

int main() {
	srand(19260817);
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) scanf("%d", A + i);
	treap::Insert(0, A, n);
	
	for (int i = 0, x, y, z; i < m; i++) {
		scanf("%s", IN);
		using namespace treap;
		switch (IN[0]) {
			case 'I' :
				scanf("%d%d", &x, &y);
				for (int j = 0; j < y; j++) scanf("%d", A + j);
				Insert(x, A, y); break;
			case 'D' :
				scanf("%d%d", &x, &y);
				Delete(x, y); break;
			case 'R' :
				scanf("%d%d", &x, &y);
				Reverse(x, y); break;
			case 'G' :
				scanf("%d%d", &x, &y);
				printf("%d\n", Sum(x, y)); break;
			default :
				if (IN[2] == 'K') {
					scanf("%d%d%d", &x, &y, &z);
					Set(x, y, z);
				} else printf("%d\n", T[ROOT].msum);
		}
	//	Debug();
	}
	return 0;
}

namespace treap {
#define lson(_) (T[_].ch[0])
#define rson(_) (T[_].ch[1])

	inline void Maintain(int u) {
		T[u].sz = 1 + T[lson(u)].sz + T[rson(u)].sz;
		T[u].sum = T[u].val + T[lson(u)].sum + T[rson(u)].sum;
		T[u].msum = max(T[lson(u)].rsum + T[u].val + T[rson(u)].lsum, 
						T[u].val);
		if (lson(u)) T[u].msum = max(T[u].msum, T[lson(u)].msum);
		if (rson(u)) T[u].msum = max(T[u].msum, T[rson(u)].msum);
		T[u].lsum = max(max(T[lson(u)].lsum, 
						T[lson(u)].sum + T[u].val + T[rson(u)].lsum), 0);
		T[u].rsum = max(max(T[rson(u)].rsum, 
						T[lson(u)].rsum + T[u].val + T[rson(u)].sum), 0);
	}
	inline void Change(int u, int val) {
		T[u].val = val; T[u].sum = val * T[u].sz; T[u].tag = val;
		T[u].msum = val >= 0 ? T[u].sum : val;
		T[u].lsum = T[u].rsum = max(0, T[u].sum);
	}
	inline void Reverse(int u) {
		T[u].rev ^= 1; std::swap(lson(u), rson(u));
		std::swap(T[u].lsum, T[u].rsum);
	}
	inline int NewNode(int v) {
		T[++size] = v;
		return size;
	}
	void PushDown(int u) {
		if (T[u].rev) {
			if (lson(u)) Reverse(lson(u));
			if (rson(u)) Reverse(rson(u));
			T[u].rev = 0;
		}
		if (T[u].tag != NULTAG) {
			if (lson(u)) Change(lson(u), T[u].tag);
			if (rson(u)) Change(rson(u), T[u].tag);
			T[u].tag = NULTAG;
		}
	}
	void Split(int u, int sd, int & rt1, int & rt2) {
		if (!u) return (void)(rt1 = rt2 = 0);
		if (!sd) return (void)(rt1 = 0, rt2 = u);
		PushDown(u);
		if (T[lson(u)].sz + 1 <= sd) {
			rt1 = u;
			Split(rson(u), sd - T[lson(u)].sz - 1, rson(rt1), rt2);
		} else {
			rt2 = u;
			Split(lson(u), sd, rt1, lson(rt2));
		}
		Maintain(u);
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
	inline int Merge(int rt1, int rt2, int rt3) {
		return Merge(rt1, Merge(rt2, rt3));
	}
	int Build(int c[], int num) {
		static int S[kMaxn];
		int top = 0;
		for (int i = 0, cur, last; i < num; i++) {	
			cur = NewNode(c[i]), last = 0;
			for (int fa; top; ) {
				if (T[S[top - 1]].rkey < T[cur].rkey) {
					lson(cur) = rson(fa = S[top - 1]); rson(fa) = cur;
					break;
				}
				Maintain(last = S[--top]);
			}
			if (!top && last) {
				lson(cur) = last;
			}
			S[top++] = cur;
		}
		while (top) Maintain(S[--top]);
		assert(S[0]);
		return S[0];
	}
	void Insert(int pos, int c[], int num) {
		int rt1, rt2;
		Split(ROOT, pos, rt1, rt2);
		ROOT = Merge(rt1, Build(c, num), rt2);
	}

#define SPLIT(a, b, c, str, len) int a, b, c; \
	Split(ROOT, str - 1, a, b); \
	Split(b, len, b, c)

	void Delete(int pos, int num) {
		SPLIT(rt1, rt2, rt3, pos, num);
		ROOT = Merge(rt1, rt3);
	}
	void Set(int pos, int num, int val) {
		SPLIT(rt1, rt2, rt3, pos, num);
		Change(rt2, val);	
		ROOT = Merge(rt1, rt2, rt3);
	}
	void Reverse(int pos, int num) {
		SPLIT(rt1, rt2, rt3, pos, num);
		Reverse(rt2);
		ROOT = Merge(rt1, rt2, rt3);
	}
	int Sum(int pos, int num) {
		SPLIT(rt1, rt2, rt3, pos, num);
		int res = T[rt2].sum;
		ROOT = Merge(rt1, rt2, rt3);
		return res;
	}
}
