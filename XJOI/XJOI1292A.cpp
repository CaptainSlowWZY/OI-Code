#pragma GCC optimize(2)
#include <cstdio>
#include <map>

const int kMaxn = 1e6 + 5, kMod = 998244353;

inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline void Upa(int & a, int b) { a = Add(a, b); }

int n, m;
int A[kMaxn], F[kMaxn];
std::map<int, int> mp;

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0, xi; i < m; ++i) {
		scanf("%d", &xi); ++A[xi];
	}
	for (int i = 1; i <= n; ++i) A[i] += A[i - 1];
	mp[0] = F[0] = 1;
	for (int i = 1; i <= n; ++i) {
		if (mp.count(i - A[i])) Upa(F[i], mp[i - A[i]]);
		if (A[i] == A[i - 1]) {
			Upa(F[i], F[i - 1]); Upa(mp[i - A[i]], F[i - 1]);
		}
	} printf("%d\n", F[n]);
	return 0;
}
