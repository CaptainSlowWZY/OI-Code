#include <cstdio>

const int kMaxn = 5e4 + 5;

int L, n, m;
int D[kMaxn];

bool Check(int gap);

int main() {
	scanf("%d%d%d", &L, &n, &m);
	for (int i = 0; i < n; i++) scanf("%d", D + i);

	int lb = 0, ub = L + 1;
	for (int mid; ub - lb > 1; ) {
		mid = lb + ub >> 1;
		if (Check(mid)) lb = mid;
		else ub = mid;
	} printf("%d\n", lb);
	return 0;
}

bool Check(int gap) {
	int last = 0;
	for (int i = 0, cnt = 0; i < n; i++) {
		if (D[i] - last < gap) {
			if (++cnt > m) return false;
			continue;
		} last = D[i];
		if (i < n && L - D[i + 1] < gap) {
			if ((cnt += n - 1 - i) > m) return false;
			break;
		}
	} return true;
}
