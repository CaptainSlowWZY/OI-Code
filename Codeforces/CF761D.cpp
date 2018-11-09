#include <cstdio>
#include <algorithm>

const int MAXN = 1e5 + 10;
const int INF = 0x7f7f7f7f;

struct DJB {
	int lb, ub, id, rk;
	bool operator<(const DJB & d) const {
		return rk < d.rk;
	}
} C[MAXN];

int N, L, R, val[MAXN], A[MAXN];

int main() {
	scanf("%d%d%d", &N, &L, &R);
	for (int i = 0; i < N; i++) {
		scanf("%d", A + i);
		C[i].lb = L - A[i], C[i].ub = R - A[i], C[i].id = i;
	}
	for (int i = 0; i < N; i++) scanf("%d", &C[i].rk);
	
	std::sort(C, C + N);
	{
		int i, now = 0, low = C[0].lb;
		for (i = 1; i < N; i++) {
			if (C[i].rk ^ C[now].rk) {
				for (int j = now; j < i; j++) {
					if (low > C[j].ub) return puts("-1"), 0;
					val[C[j].id] = A[C[j].id] + low;
				}
				now = i, low = std::max(low + 1, C[i].lb);
			}
			low = std::max(low, C[i].lb);
		}
		for (int j = now; j < i; j++) {
			if (low > C[j].ub) return puts("-1"), 0;
			val[C[j].id] = A[C[j].id] + low;
		}
	}
	for (int i = 0; i < N; i++) printf("%d ", val[i]);
	putchar('\n');

	return 0;
}
