#include <cstdio>
#include <cstring>

typedef long long LL;

const int kU = (1 << 15) + 5, kMaxn = 16;
const LL kInf64 = 0x3f3f3f3f3f3f3f3f;

int n, U;
int W[kMaxn][kMaxn];
LL F[kU][kMaxn], G[kU][kMaxn];

template <typename T> inline
void UMin(T & x, const T & y) { if (x > y) x = y; }

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n - 1; ++i)
		for (int j = i + 1; j < n; ++j) {
			scanf("%d", W[i] + j); W[j][i] = W[i][j];
		}
	memset(F, 0x3f, sizeof F); memset(G, 0x3f, sizeof G);
	for (int i = 0, s; i < n; ++i)
		for (int j = F[s = 1 << i][i] = 0; j < n; ++j)
			G[s][j] = LL(n - 1) * W[i][j];
	U = 1 << n;
	for (int s = 3, sz; s < U; ++s) {
		sz = __builtin_popcount(s);
		for (int i = 0; i < n; ++i) if (s >> i & 1) {
			for (int t = s - 1; t != s; t = t - 1 & s) {	
				if (t >> i & 1) continue;
//				printf(" F[s ^ t = %d][%d] = %lld, G[%d][%d] = %lld\n",
//						s ^ t, i, F[s ^ t][i], t, i, G[t][i]);
				UMin(F[s][i], F[s ^ t][i] + G[t][i]);
			}
			for (int j = 0; j < n; ++j)
				UMin(G[s][j], F[s][i] + LL(n - sz) * sz * W[i][j]);
		}
	}
	LL ans = kInf64;
	for (int i = 0; i < n; ++i) UMin(ans, F[U - 1][i]);
	printf("%lld\n", ans);
	return 0;
}
