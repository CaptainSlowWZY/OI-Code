// HDU 4358
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

#ifdef DEBUG_MD
	#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define debug(format, ...)
#endif
#define pb push_back

const int MAXN = 1e5 + 10;

typedef int Arr[MAXN];

struct Edge {
	int to, next;
} E[MAXN << 1];
struct Query {
	int id, l, r;
	bool operator<(const Query & q) const {
		return r < q.r;
	}
} qry[MAXN];

int N, K, Q, totn, tote, dfs_clock;
Arr last, vrt, bgn, end, num, W, ans;
std::vector<int> pos[MAXN];

namespace FastIO {
	template <typename T>
		void read(T & x);
	template <typename T>
		void write(T x);
	template <>
		void write<const char *>(const char *str) {
			for (int i = 0; str[i]; ++i) putchar(str[i]);
		}
	template <typename T>
		inline void writeln(T x) {
			write(x), putchar('\n');
		}
}
void solve();

int main() {
	int t;
	for (FastIO::read(t); t--; ) solve();

	return 0;
}

namespace BIT {
	Arr T;	

	inline void init() { memset(T, 0, sizeof T); }
	void add(int p, int d) {
		for (; p <= N; p += p & -p) T[p] += d;
	}
	int query(int p) {
		int ret = 0;
		for (; p > 0; p &= p - 1) ret += T[p];
		return ret;
	}
	inline void add(int l, int r, int d) { add(l, d), add(r + 1, -d); }
}

void dfs(int u, int fa) {
	debug(" dfs (u: %d, fa: %d)\n", u, fa);
	bgn[u] = ++dfs_clock;
	vrt[dfs_clock] = W[u];
	for (int v, e = last[u]; e; e = E[e].next) {
		if ((v = E[e].to) == fa) continue;
		dfs(v, u);
	}
	end[u] = dfs_clock;
}

inline void add_edge(int u, int v) {
	E[++tote] = (Edge){v, last[u]}, last[u] = tote;
	E[++tote] = (Edge){u, last[v]}, last[v] = tote;
}

inline int get_id(int val) {
	return std::lower_bound(num, num + totn, val) - num;
}

void solve() {
	totn = tote = dfs_clock = 0;
	memset(last, 0, sizeof last);
	using FastIO::read;

	read(N), read(K);
	for (int i = 1; i <= N; i++) read(W[i]), num[totn++] = W[i];
	for (int i = 1, ui, vi; i < N; i++) {
		read(ui), read(vi);
		debug("adding edge (%d, %d)\n", ui, vi);
		add_edge(ui, vi);
	}
	dfs(1, 0);
#ifdef DEBUG_MD
	for (int i = 1; i <= N; i++) debug(" vectex%d: [%d, %d]\n", i, bgn[i], end[i]);
#endif
	read(Q);
	for (int i = 0, u; i < Q; i++) {
		read(u);
		debug(" query_%d, u: %d, [%d, %d]\n", i, u, bgn[u], end[u]);
		qry[i] = (Query){i, bgn[u], end[u]};
	}

	std::sort(num, num + totn);
	totn = std::unique(num, num + totn) - num;
	for (int i = 0; i < totn; i++) pos[i].clear(), pos[i].pb(0);
	std::sort(qry, qry + Q);
#ifdef DEBUG_MD
	for (int i = 0; i < Q; i++) debug("  id: %d, [%d, %d]\n", qry[i].id, qry[i].l, qry[i].r);
#endif
	BIT::init();
	for (int i = 1, iq = 0; i <= N && iq < Q; i++) {
		std::vector<int> & now = pos[get_id(W[i])];
		now.pb(i);
		int cnt = now.size() - 1;
		if (cnt >= K) {
			BIT::add(now[cnt - K] + 1, now[cnt - K + 1], 1);
			if (cnt > K) BIT::add(now[cnt - K - 1] + 1, now[cnt - K], -1);
		}
		for (; iq < Q && qry[iq].r == i; ++iq) ans[qry[iq].id] = BIT::query(qry[iq].l);
	}
	
	static int ks = 0;
	if (ks) putchar('\n');
	FastIO::write("Case #");
	FastIO::write(++ks);
	putchar(':'), putchar('\n');
	for (int i = 0; i < Q; i++) FastIO::writeln(ans[i]);
}

namespace FastIO {
	template <typename T>
		void read(T & x) {
			register char ch = getchar();
			for (; ch < '0' || ch > '9'; ch = getchar());
			for (x = 0; ch >= '0' && ch <= '9'; x = (x << 3) + (x << 1) + (ch ^ '0'), ch = getchar());
		}
	
	template <typename T>
		void write(T x) {
			if (!x) return (void)putchar('0');
			if (x < 0) x = -x, putchar('-');
			int arr[20], len = 0;
			for (; x; x /= 10) arr[len++] = x % 10;
			while (len) putchar(arr[--len] ^ '0');
		}
}

// AC!!!
