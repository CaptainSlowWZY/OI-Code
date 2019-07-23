// inver
#include <cstdio>
#include <algorithm>

const int kMaxn = 5010;

int n, A[kMaxn];

namespace bit {
	int D[kMaxn];

	void Clear() {
		for (int i = 0; i <= n; i++) D[i] = 0;
	}
	int Sum(int p) {
		int ret = 0;
		for (; p; p &= p - 1) ret += D[p];
		return ret;
	}
	void Add(int p) {
		for (; p <= n; p += p & -p) ++D[p];
	}
}

int main() {
	while (~scanf("%d", &n)) {
		for (int i = 1; i <= n; i++) scanf("%d", A + i);

		bit::Clear();
		int tot = 0;
		for (int i = 1; i <= n; i++) {
			tot += i - 1 - bit::Sum(A[i]);
			bit::Add(A[i]);
		}

		int ans = tot;
		for (int i = 1; i <= n; i++) {
			tot -= A[i] - 1;
			tot += n - A[i];
			ans = std::min(ans, tot);
		}

		printf("%d\n", ans);
	}

	return 0;
}
