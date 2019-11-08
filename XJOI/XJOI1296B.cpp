#include <cstdio>
#include <cassert>
#include <map>

const int kMaxn = 1e5 + 5;

int n, k;
int A[kMaxn], L[kMaxn], pw[11];
std::map<int, int> cnt[11];

inline int Sub(int a, int b) { return (a -= b) < 0 ? a + k : a; }
inline int Mul(int a, int b) { return 1ll * a * b % k; }

int main() {
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; ++i) {
		scanf("%d", A + i);
		for (int x = A[i]; x; x /= 10) ++L[i];
	//	assert(L[i] <= 10);
		++cnt[L[i]][Sub(k, A[i] %= k) % k];
	}
	for (int i = pw[0] = 1; i <= 10; ++i) pw[i] = Mul(pw[i - 1], 10);
	long long ans = 1ll * n * (n - 1);
	for (int i = 0; i < n; ++i) {
		--cnt[L[i]][Sub(k, A[i]) % k];
		for (int t, j = 1; j <= 10; ++j) {
			t = Mul(A[i], pw[j]);
			if (!cnt[j].count(t)) continue;
			ans -= cnt[j][t];
		} ++cnt[L[i]][Sub(k, A[i]) % k];
	} printf("%lld\n", ans); return 0;
}
