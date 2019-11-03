#include <algorithm>
#include <cstdio>
#include <vector>

#define ALL(_) _.begin(), _.end()
#define SZ(_) (int)_.size()

typedef std::vector<int> Vi;

const int kMaxn = 1e6 + 5, kLg = 13, kMod = 998244353;

inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + kMod : a; }
inline int Mul(int a, int b) { return 1ll * a * b % kMod; }
inline void Upa(int & a, int b) { a = Add(a, b); }
inline void Ups(int & a, int b) { a = Sub(a, b); }
inline void Upm(int & a, int b) { a = Mul(a, b); }

int n;
int sam[kMaxn], F[kMaxn][kLg][2], pw[kLg], sum[kLg];
Vi pos[4];
char S[kMaxn];

int main() {
	scanf("%d%s", &n, S + 1);
	S[0] = S[n + 1] = 32;
	for (int i = n; i; --i)
		sam[i] = (S[i] -= 'A') == S[i + 1] ? sam[i + 1] : i;
	for (int i = 1; i <= n; ++i) pos[S[i]].push_back(i);
	for (int i = pw[0] = 1; i < kLg; ++i) pw[i] = pw[i - 1] * 3;
	int lgg = kLg - 1;
	F[0][0][0] = 1;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < 2; ++j) {
			sum[0] = F[i][0][j];
			for (int k = 1; k < kLg; ++k)
				sum[k] = Add(sum[k - 1], F[i][k][j]);
		//	printf(" i = %d, j = %d, sum[lgg] %d\n", i, j, sum[lgg]);
			for (int c = 0; c < 4; ++c) {
				if (c == S[i] || pos[c].empty()) continue;
				Vi & psc = pos[c];
				int cur = std::upper_bound(ALL(psc), i) - psc.begin();
			//	printf("  next_pos %d, cur %d(at %d)\n", c, cur, psc[cur]);
				for (int k = 0, jj; k < kLg; ++k) {
					if ((jj = cur + pw[k]) > SZ(psc)) break;
				//	printf("   x %d, -> (%d, %d, %d)\n", k, psc[jj - 1], k, 0);
					Upa(F[psc[jj - 1]][k][0], sum[lgg]);
				}
			} 
			if (S[i] > 3) continue;
			for (int k = 0, jj; k < kLg; ++k) {
				Vi & psc = pos[S[i]];
				int cur = std::upper_bound(ALL(psc), i) - psc.begin();
				if (sam[i + 1] < n && k) {
					int nxt = std::upper_bound(psc.begin() + cur,
							psc.end(), sam[i + 1]) - psc.begin();
					if (nxt != SZ(psc) && (jj = nxt + pw[k]) <= SZ(psc))
						Upa(F[psc[jj - 1]][k][0], sum[k - 1]);
				} if ((jj = cur + pw[k]) > SZ(psc)) break;
				Upa(F[psc[jj - 1]][k][0], Sub(sum[lgg], sum[k]));
				if (!j) Upa(F[psc[jj - 1]][k][j + 1],
						Sub(sum[k], k ? sum[k - 1] : 0));
			}
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; ++i) 
		for (int j = 0; j < kLg; ++j) 
			for (int k = 0; k < 2; ++k) Upa(ans, F[i][j][k]);
	printf("%d\n", ans); return 0;
}
