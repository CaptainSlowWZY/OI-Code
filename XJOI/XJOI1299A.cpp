#include <algorithm>
#include <cstdio>

const double kEps = 1e-8;
const int kMaxn = 305;

int n, H[kMaxn];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", H + i);
	int ans = 0;
	for (int i = 1; i < n; ++i) {
		for (int j = i + 1; j <= n; ++j) {
			double k = (double)(H[j] - H[i]) / (j - i), b = H[i] - k * i;
			int fail = 0;
			for (int t = i + 1; t < j; ++t)
				if (t * k + b < H[t] + kEps) { fail = 1; break; }
			if (!fail) ++ans;
		}
	} printf("%d\n", ans); return 0;
}
