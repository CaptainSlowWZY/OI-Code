// batch
#include <cstdio>
#include <cstring>
#include <algorithm>

const int kMaxn = 1e4 + 5;
const long long kInf64 = 0x3f3f3f3f3f3f3f3f;

namespace solver1 {
	void Solve();
}
namespace solver2 {
	void Solve();
}

int n, S;
int T[kMaxn], F[kMaxn];

int main() {
	scanf("%d%d", &n, &S);
	for (int i = 1; i <= n; i++) scanf("%d%d", T + i, F + i);

	for (int i = 1; i <= n; i++) F[i] += F[i - 1];
	for (int i = 1; i <= n; i++) T[i] += T[i - 1];
	if (n <= 500) solver1::Solve();
	else solver2::Solve();

	return 0;
}

template <typename T> inline
void UMin(T & x, T y) {
	x > y ? x = y : 0;
}

namespace solver1 {
	long long DP[510][510];

	void Solve() {
		memset(DP, 0x3f, sizeof DP);
		DP[0][0] = 0;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j <= i; j++) {
				if (DP[i][j] == kInf64) continue;
				for (int k = i + 1; k <= n; k++) {
					UMin(DP[k][j + 1], DP[i][j] + 
							1ll * (F[k] - F[i]) * 
							(S * (j + 1) + T[k]));
				}
			}
		}

		long long ans = kInf64;
		for (int i = 1; i <= n; i++) UMin(ans, DP[n][i]);
		
		printf("%lld\n", ans);
	}
}

namespace solver2 {
	long long DP[2][kMaxn];
	long long *prv = DP[0], *nxt = DP[1];
	int que[kMaxn];

	inline bool Better(int k, int j, long long c, int ti) {
		return 1ll * (F[j] - F[k]) * ti > 
			prv[j] - F[j] * c - prv[k] + F[k] * c;
	}
	inline double Slope(int k, int j, long long c) {
		return double(prv[j] - F[j] * c - prv[k] + F[k] * c) / 
			(F[j] - F[k]);
	}
	void Solve() {
		long long ans = kInf64, c;
		memset(DP, 0x3f, sizeof DP);
		DP[0][0] = 0;
		for (int j = 1, hd, tl; j <= n; j++) {
			que[hd = 0] = j - 1, tl = 1;
			c = 1ll * S * j;
			for (int i = j, k; i <= n; i++) {
				while (hd + 1 < tl && Better(que[hd], que[hd + 1], 
							c, T[i])) ++hd;
				k = que[hd];
			/*	printf(" DP[%d][%d] <-- DP[%d][%d]\n",
						j, i, j - 1, k);*/
				nxt[i] = prv[k] + 1ll * (F[i] - F[k]) * (c + T[i]);
				while (hd + 1 < tl &&
						Slope(que[tl - 2], que[tl - 1], c) > 
						Slope(que[tl - 1], i, c)) --tl;
				que[tl++] = i;
			}
			UMin(ans, nxt[n]);
		/*	for (int i = j; i <= n; i++) {
				printf(" DP[%d][%d] = %lld\n", j, i, nxt[i]);
			}*/
			std::swap(prv, nxt);
		}
		printf("%lld\n", ans);
	}
}
