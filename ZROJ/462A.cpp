#include <cstdio>
#include <bitset>

const int kMaxn = 405;

int n, m;
std::bitset<kMaxn> A[kMaxn];
char S[kMaxn];

bool Solve();

int main() {
	int t; scanf("%d", &t);
	while (t--) puts(Solve() ? "YES" : "NO");
	return 0;
}

bool Solve() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++i) {
		scanf("%s", S); A[i].reset();
		for (int j = 0; j < m; ++j)
			A[i][j] = S[j] == 'Y';
	}
	int sup = 0;
	for (int i = 1; i < n; ++i)
		if ((A[i] & A[0]) == A[0]) ++sup;
	if (sup == 1) return 1;
	if (sup > 1) return 0;
	std::bitset<kMaxn> ca, o, cu;
	for (int i = 1; i < n; ++i) {
		ca = A[i] & A[0], o = A[i] ^ ca, cu.reset();
		for (int j = 1; j < n; ++j) {
			if (i == j) continue;
			if ((A[j] & ca) == ca) cu |= A[j];
		} if ((cu & o) == o) continue;
		return 1;
	} return 0;
}
