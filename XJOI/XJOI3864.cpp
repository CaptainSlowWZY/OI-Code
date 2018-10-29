// XJOI 3864
#include <cstdio>
#include <cmath>
#include <utility>
#include <algorithm>

#ifdef DEBUG_MD
	#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define debug(format, ...) 0
#endif
#define fir first
#define sec second

typedef std::pair<int, int> Pii;
typedef std::pair<double, int> Pdi;

const int MAXN = 55;

int N, M;
Pii C[MAXN], V[MAXN];
Pdi D[MAXN << 1];

inline double sqr(double x) { return x * x; }
inline double dist(const Pii & p1, const Pii & p2) {
	return sqrt(sqr(p1.fir - p2.fir) + sqr(p1.sec - p2.sec));
}

int main() {
	scanf("%d%d", &N, &M);
	for (int i = 0; i < N; i++) scanf("%d", &C[i].fir);
	for (int i = 0; i < N; i++) scanf("%d", &C[i].sec);
	for (int i = 0; i < M; i++) scanf("%d", &V[i].fir);
	for (int i = 0; i < M; i++) scanf("%d", &V[i].sec);

	double ans = 0;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) D[j] = Pdi(dist(C[j], V[i]), 1);
		for (int j = 0; j < M; j++) D[N + j] = Pdi(dist(V[j], V[i]), 0);
		std::sort(D, D + N + M);
		for (int j = 1; j < N + M; j++) {
			if (D[j].sec) {
				ans += D[j].fir / (double)j;
				break;
			}
			ans += D[j].fir / (double)((j + 1) * j);
		}
	}

	printf("%.12f\n", ans);
	return 0;
}

// AC!!!
