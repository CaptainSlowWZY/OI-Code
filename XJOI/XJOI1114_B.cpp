#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>

#define pb push_back
#define fir first
#define sec second
#define rg register
#define gch getchar

const int MOD = 1e9 + 7, kMaxn = 1e5 + 10, kHash = 23;

typedef long long LL;
typedef int Int_arr[kMaxn];
typedef LL LL_arr[kMaxn];

int n, m;
Int_arr fa, on_loop, fail;
LL_arr hash, S, way, fac, faci;
std::vector<int> loop, G[kMaxn];

namespace FastIO {
	template <typename T>
		void Read(T & x);
}
template <typename T>
inline void Add(T & x, LL y) { x = (x + y) % MOD; }
template <typename T>
inline void Mult(T & x, LL y) { x = x * y % MOD; }
LL FastPow(LL bs, int ex = MOD - 2) {
	LL ret = 1;
	for (; ex; (bs *= bs) %= MOD, ex >>= 1)
		if (ex & 1) (ret *= bs) %= MOD;
	return ret;
}
LL Comb(LL n, LL k) {
	LL ret = 1;
	for (LL i = 0; i < k; i++) Mult(ret, n - i);
	return ret * faci[k] % MOD;
}
void Dfs(int u);

int main() {
	using FastIO::Read;

	Read(n), Read(m);
	for (int i = 1; i <= n; i++) {
		Read(fa[i]);
		G[fa[i]].pb(i);
	}
	
	fac[0] = fac[1] = 1;
	for (int i = 2; i <= n; i++) fac[i] = fac[i - 1] * i % MOD;
	faci[n] = FastPow(fac[n]);
	for (int i = n - 1; i >= 0; i--) faci[i] = faci[i + 1] * (i + 1) % MOD;

	int rover = 1;
	for (int i = 1; i <= n; i++) rover = fa[rover];
	loop.pb(rover), on_loop[rover] = 1;
	for (int u = fa[rover]; u != rover; u = fa[u]) {
		loop.pb(u), on_loop[u] = 1;
	}
	int loopsz = loop.size();
//	printf(" loop size = %d\n", loopsz);
	for (int i = 0, v; i < loopsz; i++) {
//		printf(" on loop is %d\n", loop[i]);
		Dfs(v = loop[i]);
//		printf("	ways = %lld, hash val = %lld\n", way[v], hash[v]);
		S[i] = hash[v];
	}
	fail[0] = fail[1] = 0;
	for (int i = 1, j; i < loopsz; i++) {
		for (j = fail[i]; j && S[i] != S[j]; j = fail[j]);
		fail[i + 1] = S[i] == S[j] ? j + 1 : 0;
	}
	LL ans;
	if (!fail[loopsz] || loopsz % (loopsz - fail[loopsz])) {
		ans = 1;
		for (int i = 0; i < loopsz; i++) Mult(ans, way[loop[i]]);
		printf("%lld\n", ans);
		return 0;
	}
	else {
		int perlen = loopsz - fail[loopsz], len = loopsz / perlen;
//		printf("perlen = %d, len = %d\n", perlen, len);
		LL perway = 1;
		for (int i = 0; i < perlen; i++) Mult(perway, way[loop[i]]);
//		printf("perway = %lld\n", perway);
		ans = 0;
		for (int i = 1; i <= len; i++) Add(ans, FastPow(perway, std::__gcd(i, len)));
//		printf("ans = %lld\n", ans);
		Mult(ans, FastPow(len));
		Add(ans, MOD);
		printf("%lld\n", ans);
	}

	return 0;
}

void Dfs(int u) {
	std::map<int, LL> cnt, sub;
	way[u] = m, hash[u] = 23333;
	for (auto v : G[u]) {
		if (on_loop[v]) continue;
		Dfs(v);
		++cnt[hash[v]];
		sub[hash[v]] = way[v];
	}
	for (std::map<int, LL>::iterator it1 = cnt.begin(); it1 != cnt.end(); ++it1) {
		Mult(way[u], Comb(it1->sec + sub[it1->fir] - 1, it1->sec));
		hash[u] = (hash[u] * kHash % MOD + it1->fir * 29 + it1->sec) % MOD;
	}
	hash[u] = (hash[u] * kHash % MOD + 8761) % MOD;
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
