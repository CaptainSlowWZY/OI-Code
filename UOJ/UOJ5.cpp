#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

#define pb push_back
#define FORV(TP, I, _) for (std::vector<TP>::iterator I = _.begin(); I != _.end(); ++I)

const int kMaxn = 1e6 + 5, kMod = 1e9 + 7;

inline int Mul(int a, int b) { return 1ll * a * b % kMod; }
inline void Upm(int & a, int b) { a = Mul(a, b); }

int n, ans, F[kMaxn], D[kMaxn];
char S[kMaxn];

void Solve();

int main() {
	int t; scanf("%d", &t);
	while (t--) Solve();
	return 0;
}

void Solve() {
	scanf("%s", S); n = strlen(S), F[0] = F[1] = 0;
	for (int i = 1, j; i < n; ++i) {
		D[i] = D[F[i]] + 1;
		for (j = F[i]; j && S[j] != S[i]; j = F[j]);
		F[i + 1] = S[i] == S[j] ? j + 1 : 0;
	} D[n] = D[F[n]] + 1, ans = 1;
	for (int i = 1, j = 0; i < n; ++i) {
		while (j && (S[j] != S[i] || j > i / 2)) j = F[j];
		j += S[j] == S[i];
		while (j > (i + 1) / 2) j = F[j];
		Upm(ans, D[j] + 1);
	}
	printf("%d\n", ans);
}
