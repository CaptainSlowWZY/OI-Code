// SPOJ LCMSUM
#include <cstdio>
#include <cassert>

#ifdef DEBUG_MD
	#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define debug(format, ...) 0
#endif

typedef long long LL;

const int INIT_LIM = 1e6;

LL g[INIT_LIM + 10];
int totp, P[INIT_LIM + 10], phi[INIT_LIM + 10], ex[INIT_LIM + 10];

void init();

int main() {
	init();

	int t, N;
	for (scanf("%d", &t); t--; ) {	
		scanf("%d", &N);
		debug("g[N] = %lld\n", g[N]);
		printf("%lld\n", (g[N] + 1) * N / 2);
	}

	return 0;
}

LL fast_pow(LL bs, int ex_) {
	LL ret = 1;
	for (; ex_; bs *= bs, ex_ >>= 1)
		if (ex_ & 1) ret *= bs;
	return ret;
}

inline LL calc_g(LL p, int ex_) {
	return (p * fast_pow(p, ex_ << 1) - 1) / (p + 1) + 1;
}

void init() {
	g[1] = phi[1] = 1;
	// f(n) = n phi(n), so f is productive. 
	// g = f * 1, g is productive, too.
	// array f and g should be LL
	// ex[n] is a_1, while n = p1^a1 p2^a2 ...
	for (int i = 2; i <= INIT_LIM; i++) {
		debug("i = %d\n", i);
		if (!phi[i]) {
			P[totp++] = i, ex[i] = 1, phi[i] = i - 1;
			g[i] = 1LL + (LL)i * phi[i];
		}
		LL pd;
		for (int j = 0; j < totp && (pd = (LL)i * P[j]) <= INIT_LIM; j++) {
			if (i % P[j] == 0) {
				phi[pd] = phi[i] * P[j], ex[pd] = ex[i] + 1;
				g[pd] = calc_g(P[j], ex[pd]) * g[pd / fast_pow(P[j], ex[pd])];
				break;
			}
			phi[pd] = phi[i] * (P[j] - 1), ex[pd] = 1;
			g[pd] = g[i] * g[P[j]];
		}
	}
}
