// BZOJ 3198
// [SDOI2013] Spring
#include <cstdio>
#include <cstring>
#include <utility>
#include <vector>

#ifdef LOCAL
	#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define debug(format, ...)
#endif
#define pb push_back
#define fir first
#define sec second

typedef std::vector<int> Veci;
typedef long long LL;
typedef std::pair<LL, int> Pli;
typedef std::vector<Pli> Vecpli;

const int MAXN = 100005;
const int HASH_BASE = 6666667;

int N, K, A[MAXN][6], C[7][7];

namespace Hash {
	const int MOD = 100003;
	Vecpli tb[MOD + 5];
	LL sum;

	void init() {
		for (int i = 0; i < MOD; i++) tb[i].clear();
		sum = 0;
	}
	inline void insert(LL k) {
		Vecpli & now = tb[(k % MOD + MOD) % MOD];
		for (int i = 0, sz = now.size(); i < sz; i++)
			if (now[i].fir == k) {
				sum += now[i].sec++;
				return;
			}
		now.pb(Pli(k, 1));
	}
	inline LL count() {
		return sum;
	}
}
namespace FastIO {
	template <typename T>
		void read(T & x) {
			x = 0; register char ch = getchar();
			for (; ch < '0' || ch > '9'; ch = getchar());
			for (; ch >= '0' && ch <= '9'; x = (x << 3) + (x << 1) + (ch ^ '0'), ch = getchar());
		}
}

void init();

int main() {
	init();

	using FastIO::read;

	read(N), read(K);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < 6; j++) read(A[i][j]);
	LL ans = 0;
	for (int mask = (1 << 6) - 1; mask >= 0; --mask)
		if (__builtin_popcount(mask) >= K) {
			Veci v;
			for (int i = 0; i < 6; i++)
				if (mask >> i & 1) v.pb(i);
			Hash::init();
			for (int i = 0; i < N; i++) {
				LL key = 0;
				for (int j = 0, sz = v.size(); j < sz; j++) key = key * HASH_BASE + A[i][v[j]];
				Hash::insert(key);
			}
			ans += (v.size() - K & 1 ? -1LL : 1) * C[v.size()][K] * Hash::count();
		}
	printf("%lld\n", ans);
	return 0;
}

void init() {
	C[0][0] = 1;
	for (int i = 1; i <= 6; i++) {
		C[i][0] = 1;
		for (int j = 1; j <= 6; j++) C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
	}
}

// AC!!!
