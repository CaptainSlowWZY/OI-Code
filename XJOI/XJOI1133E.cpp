// aka 51nod 1446
#pragma GCC optimize(2)
#include <cstdio>
#include <algorithm>
#include <vector>

const int kMaxn = 45, MOD = 1e9 + 7;

int n, limit, totg, val[kMaxn];
long long M[kMaxn][kMaxn], limc[kMaxn];
int C[kMaxn][kMaxn], F[kMaxn];
std::vector<long long> sum[kMaxn];

inline void AddEdge(int u, int v) {
	++M[u][u], ++M[v][v];
	--M[u][v], --M[v][u];
}
template <typename T> inline
void Add(T & x, long long y) { (x += y) %= MOD; }
long long Det();

int main() {
	C[0][0] = 1;
	for (int i = 1; i <= 40; i++) {
		for (int j = C[i][0] = 1; j <= i; j++) {
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
		}
	}

	scanf("%d%d", &n, &limit);
	totg = 0;
	for (int i = 0; i < n; i++) {
		scanf("%d", val + i);
		if (~val[i]) val[totg++] = val[i];
	}

	int half = (totg - 1 >> 1) + 1, uh = 1 << half;
	//	printf(" totgood %d, half is %d\n", totg, half);
	for (int mask = 0; mask < uh; mask++) {
		long long sumc = 0;
		for (int i = 0; i < half; i++) {
			if (mask >> i & 1) sumc += val[i];
			if (sumc > limit) break;
		}
		if (sumc > limit) continue;
		sum[__builtin_popcount(mask)].push_back(sumc);
	}
	for (int i = 0; i <= half; i++) {
		std::sort(sum[i].begin(), sum[i].end());
	}
	for (int mask = (1 << totg - half) - 1; mask >= 0; mask--) {
		int cnt = 0;
		long long sumc = 0;
		for (int i = half; i < totg; i++) {
			if (mask >> i - half & 1) {
				if ((sumc += val[i]) > limit) break;
				++cnt;
			}
		}
		if (sumc > limit) continue;
		/*	printf(" mask = %d, cnt = %d, sumc = %d\n",
			mask, cnt, sumc);*/
		for (int i = 0; i <= half; i++) {
			/*	printf("  with other side choose %d, %d ways\n",
				i, std::upper_bound(sum[i].begin(), sum[i].end(),
				limit - sumc) - sum[i].begin());*/
			Add(limc[i + cnt], 
					std::upper_bound(sum[i].begin(), sum[i].end(),
						limit - sumc) - sum[i].begin());
		}
	}

	/*	for (int i = 0; i <= totg; i++) {
		printf(" choose %d unlimited is %lld ways\n",
		i, (limc[i] + MOD) % MOD);
		}*/

	for (int i = 0; i <= totg; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				M[j][k] = 0;
			}
		}
		for (int j = 0; j < totg; j++) {
			for (int k = totg; k < n; k++) {
				AddEdge(j, k);
			}
		}
		for (int j = i; j < totg; j++) {
			for (int k = j + 1; k < totg; k++) {
				AddEdge(j, k);
			}
		}
		for (int j = totg; j < n; j++) {
			for (int k = j + 1; k < n; k++) {
				AddEdge(j, k);
			}
		}
		F[i] = Det();
	}

	long long ans = 0;
	for (int i = 0; i <= totg; i++) {
		long long gi = 0;
		for (int j = i; j <= totg; j++) {
			Add(gi, (j - i & 1 ? -1ll : 1ll) * 
					C[totg - i][j - i] * F[j] % MOD);
		}
		Add(ans, gi * limc[totg - i] % MOD);
	}
	ans = (ans + MOD) % MOD;

	printf("%lld\n", ans);
	return 0;
}

long long FPow(long long bs, int ex = MOD - 2) {
	long long ret = 1;
	for (; ex; (bs *= bs) %= MOD, ex >>= 1) {
		if (ex & 1) (ret *= bs) %= MOD;
	}
	return ret;
}

long long Det() {
	int n0 = n - 1;
	for (int i = 0; i < n0; i++) {
		if (!M[i][i]) {
			for (int j = i + 1; j < n0; j++) {
				if (M[j][i]) {
					for (int k = i; k < n0; k++) {
						std::swap(M[i][k], M[j][k]);
					}
					break;
				}
			}
			if (!M[i][i]) return 0;
		}
		long long invi = FPow(M[i][i]);
		for (int j = i + 1; j < n0; j++) {
			long long tmp = -M[j][i] * invi % MOD;
			for (int k = i; k < n0; k++) {
				Add(M[j][k], tmp * M[i][k] % MOD);
			}
		}
	}
	long long ans = 1;
	for (int i = 0; i < n0; i++) (ans *= M[i][i]) %= MOD;
	return ans;
}
