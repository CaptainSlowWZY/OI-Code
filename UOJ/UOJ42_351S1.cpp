// UOJ Contest 43 Problem 351 
// Solution 1
#pragma GCC diagnostic error "-std=c++11"
#include <cstdio>
#include <utility>
#include <vector>

#ifdef DEBUG_MD
	#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define debug(format, ...) 0
#endif
#define rg register
#define gch getchar
#define pch putchar
#define forsn(u) for (int v, e = last[u]; e; e = E[e].next)
#define fir first
#define sec second
#define pb push_back

const int MAXN = 5e5 + 10;
const int MOD = 998244353;

typedef long long LL;
typedef std::pair<int, int> Pii;
typedef int IntAr[MAXN];

struct Edge {
	int to, next;
} E[MAXN << 1];

int N, tote, totsz, totlf, tot;
IntAr last, fac, inv, sigma, nxt, dgr;
std::vector<int> slv;

namespace FastIO {
	template <typename T>
		void read(T & x);
	template <typename T>
		void write(T x);
	template <typename T>
		inline void writeln(T x) {
			write(x), pch('\n');
		}
}
void init();
Pii dfs(int u, int fa);
void dfs(int u, int fa, int dep);
LL fast_pow(LL bs, int ex) {
	LL ret = 1;
	for (; ex; (bs *= bs) %= MOD, ex >>= 1) if (ex & 1) (ret *= bs) %= MOD;
	return ret;
}
inline LL get_inv(LL x) {
	return fast_pow(x, MOD - 2);
}
inline void add_edge(int u, int v) {
	E[++tote] = (Edge){v, last[u]}, last[u] = tote;
	E[++tote] = (Edge){u, last[v]}, last[v] = tote;
	++dgr[u], ++dgr[v];
}
inline LL C(int n, int r) {
	return (LL)fac[n] * inv[r] % MOD * inv[n - r] % MOD;
}

int main() {
	using FastIO::read;

	read(N);
	for (int i = 1, ui, vi; i < N; i++) {
		read(ui), read(vi);
		add_edge(ui, vi);
	}

	for (int i = 1; i <= N; i++)
		if (dgr[i] == 1) ++totlf;
	int rt = dfs(1, 0).sec;
	debug("rt(%d)\n", rt);
	Pii tmp = dfs(rt, 0);
	debug("tmp(first=%d, second=%d)\n", tmp.fir, tmp.sec);
	int u = rt, d = tmp.fir >> 1;
	for (; d--; u = nxt[u]);
	debug("u=%d\n", u);
	if (tmp.fir & 1) {
		tot = 0;
		dfs(u, nxt[u], tmp.fir >> 1);
		slv.pb(tot), totsz += tot;
		tot = 0;
		dfs(nxt[u], u, tmp.fir >> 1);
		slv.pb(tot), totsz += tot;
	}
	else {
		d = (tmp.fir >> 1) - 1;
		forsn(u) {
			tot = 0;
			dfs(v = E[e].to, u, d);
			if (!tot) continue;
			slv.pb(tot), totsz += tot;
		}
	}
	init();
	LL ans = 0;
	debug("totsz=%d\n", totsz);
	for (auto sz : slv) {
		debug("  sz(%d)\n", sz);
		for (int i = 0; i < sz; i++)
			(ans += C(sz, i) * fac[totsz - sz + i - 1] % MOD * (totsz - sz) % MOD * sigma[sz - i + 1] % MOD * fac[sz - i]) %= MOD;
		debug("  ans=%lld\n", ans);
	}
	(ans *= inv[totsz]) %= MOD;

	printf("%lld\n", ans);
	return 0;
}

void init() {
	fac[0] = 1;
	debug(" INIT...%c", '\n');
	for (LL i = 1; i <= totsz; i++) fac[i] = i * fac[i - 1] % MOD;
	inv[totsz] = get_inv(fac[totsz]);
	debug(" Fact DONE!%c", '\n');
	for (LL i = totsz - 1; i >= 0; i--) inv[i] = (i + 1) * inv[i + 1] % MOD;
	for (int i = totsz; i > 0; i--) sigma[i] = (sigma[i + 1] + totlf * get_inv(i) % MOD) % MOD;
#ifdef DEBUG_MD
	for (int i = 0; i <= totsz; i++) debug(" %d!=%d, (%d!)^(-1)=%d\n", i, fac[i], i, inv[i]);
	debug("=====	END   =====%c", '\n');
	for (int i = 1; i <= totsz; i++) debug("sigma_%d=%d\n", i, sigma[i]);
	debug("=====	END   =====%c", '\n');
#endif
}

Pii dfs(int u, int fa) {
	Pii ret(0, u);
	nxt[u] = 0;
	forsn(u) {
		if ((v = E[e].to) == fa) continue;
		Pii tmp = dfs(v, u);
		++tmp.fir;
		if (tmp > ret) {
			ret = tmp;
			nxt[u] = v;
		}
	}
	return ret;
}

void dfs(int u, int fa, int dep) {
	debug("dfs2 : u(%d), fa(%d), dep(%d)\n", u, fa, dep);
	if (!dep) return (void)++tot;
	forsn(u) {
		if ((v = E[e].to) == fa) continue;
		dfs(v, u, dep - 1);
	}
}

namespace FastIO {
	template <typename T>
		void read(T & x) {
			rg char ch = gch();
			for (; ch < '0' || ch > '9'; ch = gch());
			for (x = 0; ch >= '0' && ch <= '9'; x = (x << 3) + (x << 1) + (ch ^ '0'), ch = gch());
		}
	template <typename T>
		void write(T x) {
			if (!x) return (void)pch('0');
			if (x < 0) x = -x, pch('-');
			rg int arr[20], len = 0;
			for (; x; x /= 10) arr[len++] = x % 10;
			while (len) pch(arr[--len] ^ '0');
		}
}
