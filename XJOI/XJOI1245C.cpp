#include <algorithm>
#include <cstdio>
#include <cstring>

const int kMaxn = 1e5 + 5, kMaxm = 1005, kInf = 0x3f3f3f3f;

struct Clas {
	int t, s, c;
	bool operator<(const Clas & a) const {
		return t < a.t;
	}
} C[kMaxm];
struct Work {
	int a, q;
	bool operator<(const Work & w) const {
		return q < w.q;
	}
} W[kMaxn];

int t, m, n;
int per[105], DP[kMaxm][105];

template <typename T> inline
void UMin(T & x, T y) { if (x > y) x = y; }
template <typename T> inline
void UMax(T & x, T y) { if (x < y) x = y; }

int main() {
	scanf("%d%d%d", &t, &m, &n);
	for (int i = 0; i < m; i++)
		scanf("%d%d%d", &C[i].t, &C[i].s, &C[i].c);
	for (int i = 0; i < n; i++)
		scanf("%d%d", &W[i].a, &W[i].q);

	std::sort(C, C + m); std::sort(W, W + n);
	per[0] = kInf;
	for (int i = 1, j = 0; i <= 100; i++) {
		per[i] = per[i - 1];
		for (; j < n && W[j].q <= i; j++)
			UMin(per[i], W[j].a);
	}
	memset(DP, 0xff, sizeof DP);
	C[m].t = t + 1;
	for (int i = 0; i <= m; i++)
		DP[i][1] = (C[i].t - 1) / per[1];
	for (int i = 0; i < m; i++) {
		for (int j = 1; j <= 100; j++) {
			if (!(~DP[i][j])) continue;
		/*	printf(" DP[%d][%d] = %d\n",
					i, j, DP[i][j]); */
			for (int k = i + 1; k <= m; k++) {
				UMax(DP[k][j], DP[i][j]);
				if (C[i].t + C[i].s <= C[k].t) {
				//	printf(" i%d -> k%d(t = %d)\n", i, k, C[k].t);
					UMax(DP[k][C[i].c], DP[i][j] +
						(C[k].t - C[i].t - C[i].s) / per[C[i].c]);
				}
				UMax(DP[k][j], DP[i][j] + (C[k].t - C[i].t) / per[j]);
			}
		}
	} int ans = 0;
	for (int i = 1; i <= 100; i++)
		UMax(ans, DP[m][i]);
	printf("%d\n", ans);
}
