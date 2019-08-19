#include <algorithm>
#include <cmath>
#include <cstdio>

const int kMaxn = 1e5 + 10;
const double kEps = 1e-8;

int n, d;
int P[kMaxn], T[kMaxn], id[kMaxn];
char name[kMaxn][12];

inline bool Cmp(int a, int b) {
	return P[a] == P[b] ? T[a] < T[b] : P[a] > P[b];
}

int main() {
	int t;
	for (scanf("%d", &t); t--; ) {
		scanf("%d%d", &n, &d);
		for (int i = 0; i < n; i++) {
			scanf("%s%d%d", name[i], P + i, T + i);
			id[i] = i;
		} double x = d * 0.1 * n;
		x = x - floor(x);
		if (fabs(x - 0.5) > kEps) {
			puts("Quailty is very great");
			continue;
		}
		std::sort(id, id + n, Cmp);
		int k = ceil(d * 0.1 * n);
		puts(name[id[k - 1]]);
	} return 0;
}
