#include <algorithm>
#include <cstdio>

typedef long long LL;

const int kMaxn = 2e5 + 10;

int n, dfs_clock;
int ch[kMaxn << 1][2], val[kMaxn << 1];
LL ans;

int Dfs(int u);
int DfsRead();

int main() {
	scanf("%d", &n);
	DfsRead();

	Dfs(1);

	printf("%lld\n", ans);
	return 0;
}

namespace smt {
	struct Node {
		int sum, ls, rs;
	} T[kMaxn << 5];
	int size, top;
	int pool[kMaxn << 5];
#define lson(_) (T[_].ls)
#define rson(_) (T[_].rs)

	int NewNode(int sum) {
		int id = top ? pool[--top] : ++size;
		T[id] = (Node){sum, 0, 0};
		return id;
	}
	inline void Recycle(int u) {
		pool[top++] = u;
	}
	int NewTree(int val) {
		int l = 1, r = n, rt = NewNode(1);
		for (int mid, u = rt; l < r; ) {
			mid = l + r >> 1;
			if (val <= mid) {
				lson(u) = NewNode(1); u = lson(u); r = mid;
			} else {
				rson(u) = NewNode(1); u = rson(u); l = mid + 1;
			}
		}
		return rt;
	}
	int Merge(int l, int r, int rt1, int rt2, LL & cnt, LL & cntr) {
		if (!rt1 || !rt2) return rt1 + rt2;
		if (l < r) {
			cnt += 1ll * T[rson(rt1)].sum * T[lson(rt2)].sum;
			cntr += 1ll * T[lson(rt1)].sum * T[rson(rt2)].sum;
			int mid = l + r >> 1;
			lson(rt1) = Merge(l, mid, lson(rt1), lson(rt2), cnt, cntr);
			rson(rt1) = Merge(mid + 1, r, rson(rt1), rson(rt2), cnt, cntr);
		}
		T[rt1].sum = T[rt1].sum + T[rt2].sum; Recycle(rt2);
		return rt1;
	}
}

int Dfs(int u) {
	using namespace smt;
	if (!ch[u][0]) return NewTree(val[u]);
	else {
		int v1 = Dfs(ch[u][0]), v2 = Dfs(ch[u][1]);	
		LL cstr = 0, cst0 = 0;
		int u = Merge(1, n, v1, v2, cst0, cstr);
		ans += std::min(cstr, cst0);
		return u;
	}
}

int DfsRead() {
	int x, u = ++dfs_clock;
	scanf("%d", &x);
	if (x) val[u] = x;
	else {
		ch[u][0] = DfsRead();
		ch[u][1] = DfsRead();
	}
	return u;
}
