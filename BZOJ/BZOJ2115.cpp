// BZOJ 2115
// WC 2011
#include <cstdio>

#define rg register
#define gch getchar
#define forto(_) for (rg int v, e = last[_]; e; e = E[e].next)

typedef long long LL;

const int LgLL = 59;
const int MAXN = 5e4 + 10;
const int MAXM = 1e5 + 10;

struct LBasis {
	LL bs[LgLL + 5];

	void insert(LL x);
	LL max_xor(LL x) const;
} B;
struct Edge {
	int to, next;
	LL cost;
	Edge(int t_ = 0, LL c_ = 0, int n_ = 0) : to(t_), cost(c_), next(n_) {}
} E[MAXM << 1];

int N, M, tote, last[MAXN], vis[MAXN];
LL _xord[MAXN];

namespace FastIO {
	template <typename T>
		void read(T & x);
}

inline void add_edge(int u, int v, LL c) {
	E[++tote] = (Edge){v, c, last[u]}, last[u] = tote;
	E[++tote] = (Edge){u, c, last[v]}, last[v] = tote;
}
void dfs(int u, int fa);

int main() {
	using FastIO::read;

	read(N), read(M);
	for (int i = 0, x, y; i < M; i++) {
		read(x), read(y);
		LL z;
		read(z);
		add_edge(x, y, z);
	}

	_xord[1] = 0;
	dfs(1, 0);

	printf("%lld\n", B.max_xor(_xord[N]));

	return 0;
}

void dfs(int u, int fa) {
	vis[u] = 1;
	forto(u) {
		if ((v = E[e].to) == fa) continue;
		if (vis[v]) {
			B.insert(_xord[u] ^ _xord[v] ^ E[e].cost);
			continue;
		}
		_xord[v] = _xord[u] ^ E[e].cost;
		dfs(v, u);
	}
}

void LBasis::insert(LL x) {
	for (int i = LgLL; i >= 0; i--)
		if (x >> i & 1) {
			if (bs[i]) x ^= bs[i];
			else {
				for (int j = i - 1; j >= 0; j--)
					if (bs[j] && x >> j & 1) x ^= bs[j];
				bs[i] = x;
				for (int j = i + 1; j <= LgLL; j++)
					if (bs[j] >> i & 1) bs[j] ^= x;
				break;
			}
		}
}

LL LBasis::max_xor(LL x) const {
	for (int i = LgLL; i >= 0; i--)
		if ((x ^ bs[i]) > x) x ^= bs[i];
	return x;
}

namespace FastIO {
	template <typename T>
		void read(T & x) {
			rg char ch = gch();
			for (; ch < '0' || ch > '9'; ch = gch());
			for (x = 0; ch >= '0' && ch <= '9'; ch = gch())
				x = (x << 1) + (x << 3) + (ch ^ '0');
		}
}
