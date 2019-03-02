#include <cstdio>
#include <cctype>
#include <algorithm>
#include <set>

#define fir first
#define sec second
#define rg register
#define gch getchar
#define forto(_) for (int e = last[_], v = E[e].to; e; v = E[e = E[e].next].to)

typedef long long LL;
typedef std::pair<LL, int> PLi;

const int kMaxn = 1e5 + 10, kHash = 31, MOD = 1e9 + 7;

struct Tree {
	struct Edge {
		int to, next;
	} E[kMaxn << 1];
	int tote, size, last[kMaxn], sz[kMaxn];
	LL hash[kMaxn], uhash[kMaxn], ans[kMaxn];

	void adde(int u, int v) {
		E[++tote] = (Edge){v, last[u]}, last[u] = tote;
		E[++tote] = (Edge){u, last[v]}, last[v] = tote;
	}
	void dfs1(int u, int fa);
	void dfs2(int u, int fa);
	void calc_hash() {
		dfs1(1, 0);
		dfs2(1, 0);
	}
} A, B;

int n, kInvh, deg[kMaxn];
std::set<LL> val;

namespace FastIO {
	template <typename T>
		void Read(T & x);
}
LL FastPow(LL bs, int ex = MOD - 2) {
	LL ret = 1;
	for (; ex; (bs *= bs) %= MOD, ex >>= 1)
		if (ex & 1) (ret *= bs) %= MOD;
	return ret;
}

int main() {
	using FastIO::Read;
	kInvh = FastPow(kHash);

	Read(n);
	for (int i = 1, u, v; i < n; i++) {
		Read(u), Read(v);
		A.adde(u, v);
	}
	for (int i = 0, u, v; i < n; i++) {
		Read(u), Read(v);
		B.adde(u, v);
		++deg[u], ++deg[v];
	}

	A.size = n, B.size = n + 1;
	A.calc_hash();
	B.calc_hash();
//	A.debug();
//	B.debug();
	for (int i = 1; i <= n; i++) val.insert(A.ans[i]);
	if (deg[1] == 1 && val.count(B.hash[B.E[B.last[1]].to])) {
		puts("1");
		return 0;
	}
	for (int i = 2; i <= n + 1; i++)
		if (deg[i] == 1 && val.count(B.uhash[i])) {
			printf("%d\n", i);
			return 0;
		}
	return 0;
}

void Tree::dfs1(int u, int fa) {
	sz[u] = 1;
	forto(u) {
		if (v == fa) continue;
		dfs1(v, u);
		sz[u] += sz[v];
	}
	static int sub[kMaxn];
	int tots = 0;
	forto(u) {
		if (v == fa) continue;
		sub[tots++] = hash[v];
	}
	std::sort(sub, sub + tots);
	for (int i = 0; i < tots; i++)
		hash[u] = (hash[u] * kHash % MOD + sub[i]) % MOD;
	hash[u] = (hash[u] * kHash + sz[u]) % MOD;
}

void Tree::dfs2(int u, int fa) {
	static PLi sub[kMaxn];
	int tots = 0;
	forto(u) sub[++tots] = PLi(v == fa ? uhash[u] : hash[v], v);
	std::sort(sub + 1, sub + 1 + tots);
	static LL sum[kMaxn];
	sum[0] = 0;
	for (int i = 1; i <= tots; i++) {
		sum[i] = (sum[i - 1] * kHash % MOD + sub[i].fir) % MOD;
		ans[u] = (ans[u] * kHash % MOD + sub[i].fir) % MOD;
	}
	ans[u] = (ans[u] * kHash % MOD + size) % MOD;
	LL sumb = 0, pw = 1;
	for (int i = tots, cur; i > 0; i--) {
		if ((cur = sub[i].sec) != fa) {
			uhash[cur] = (sum[i - 1] * pw % MOD + sumb) % MOD;
			uhash[cur] = (uhash[cur] * kHash % MOD + size - sz[cur]) % MOD;
		}
		(sumb += pw * sub[i].fir % MOD) %= MOD;
		(pw *= kHash) %= MOD;
	}
	forto(u) {
		if (v == fa) continue;
		dfs2(v, u);
	}
}

namespace FastIO {
	template <typename T>
		void Read(T & x) {
			rg char ch = gch();
			for (; !isdigit(ch); ch = gch());
			for (x = 0; isdigit(ch); ch = gch())
				x = (x << 3) + (x << 1) + (ch ^ '0');
		}
}
