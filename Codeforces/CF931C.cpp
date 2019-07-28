#include <algorithm>
#include <cstdio>

int n;
int A[100010];

int main() {
	scanf("%d", &n);
	int l = 100000, r = -100000;
	for (int i = 0; i < n; i++) {
		scanf("%d", A + i);
		l = std::min(l, A[i]);
		r = std::max(r, A[i]);
	}

	if (r - l <= 1) {
		printf("%d\n", n);
		for (int i = 0; i < n; i++)
			printf("%d%c", A[i], i + 1 == n ? '\n' : ' ');
		return 0;
	}
	int cntl, cntm, cntr;
	cntl = cntm = cntr = 0;
	for (int i = 0; i < n; i++) {
		if (A[i] == l) ++cntl;
		else if (A[i] == r) ++cntr;
		else ++cntm;
	}
	int ans;
	if (cntm / 2 >= std::min(cntl, cntr)) {
		ans = cntl + cntr + (cntm & 1);
		cntl += cntm / 2, cntr += cntm / 2;
		cntm = cntm & 1;
	} else {
		int t = std::min(cntl, cntr);
		cntl -= t, cntr -= t;
		ans = cntl + cntr + cntm;
		cntm += t * 2;
	}
	printf("%d\n", ans);
	for (int i = 0; i < cntl; i++) printf("%d ", l);
	for (int i = 0; i < cntr; i++) printf("%d ", r);
	for (int i = 0; i < cntm; i++) printf("%d ", l + 1);
	putchar('\n');
	return 0;
}
