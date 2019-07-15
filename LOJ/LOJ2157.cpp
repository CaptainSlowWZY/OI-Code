#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>

const int kMaxn = 5e5 + 10;

int n;
int A[kMaxn];
double DP[kMaxn], ans[kMaxn];

void Solve(int l, int r, int kl, int kr); 

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", A + i);

	Solve(1, n, 1, n);
	for (int i = 1; i <= n; i++) ans[i] = DP[i] - A[i];
	std::reverse(A + 1, A + n + 1);
	Solve(1, n, 1, n);
	for (int i = 1; i <= n; i++)
		ans[i] = std::max(ans[i], DP[n - i + 1] - A[n - i + 1]);
	for (int i = 1; i <= n; i++) 
		printf("%d\n", std::max(0, (int)ceil(ans[i])));
	return 0;
}

inline double Calc(int x, int y) {
	return A[x] + sqrt(abs(y - x));
}

void Solve(int l, int r, int kl, int kr) {
	int mid = l + r >> 1, k = kl;
	for (int i = kl; i <= std::min(kr, mid - 1); i++) {
		if (Calc(i, mid) > Calc(k, mid)) k = i;
	}
	DP[mid] = Calc(k, mid);
	if (l < mid) Solve(l, mid - 1, kl, k);
	if (r > mid) Solve(mid + 1, r, k, kr);
}
