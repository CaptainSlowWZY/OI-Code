#include <cstdio>
#include <algorithm>

const int kMaxn = 3e5 + 5;

int n, m;
int A[kMaxn];

bool Check(int x);

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) scanf("%d", A + i);

	int lb = -1, ub = m - 1;
	for (int mid; ub - lb > 1; ) {
		mid = lb + ub >> 1;
		if (Check(mid)) ub = mid;
		else lb = mid;
	}

	printf("%d\n", ub);
	return 0;
}

bool Check(int x) {
	int last = -100;
	for (int i = 0; i < n; i++) {
		if (A[i] + x < m) {	// [Ai, Ai + x]
			if (A[i] + x >= last) last = std::max(A[i], last);
			else return false;
		} else {	// [0, Ai + x - m] & [Ai, m - 1]
			if (A[i] + x - m >= last) last = std::max(last, 0);
			else last = std::max(A[i], last);
		}
	}
	return true;
}
