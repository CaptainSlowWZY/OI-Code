#include <algorithm>
#include <cstdio>
#include <vector>

#define fi first
#define se second
#define pb push_back
#define SZ(_) (int)_.size()
#define F8R(X0, Y0, NX, NY) for (int k = 0, NX, NY; k < 8; ++k) if ((NX = X0 + kDx[k]) >= 0 && NX < n && (NY = Y0 + kDy[k]) >= 0 && NY < m)

const int kMaxn = 5, kMaxm = 9, kMod = 12345678, kU = 1 << 8;
const int kDx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int kDy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + kMod : a; }
inline int Mul(int a, int b) { return 1ll * a * b % kMod; }
inline void Upa(int & a, int b) { a = Add(a, b); }
inline void Ups(int & a, int b) { a = Sub(a, b); }
inline void Upm(int & a, int b) { a = Mul(a, b); }
int FPow(int bs, int ex = kMod - 2) {
	int res = 1;
	for (; ex; bs = Mul(bs, bs), ex >>= 1)
		if (ex & 1) res = Mul(res, bs);
	return res;
}

typedef int Mat[kMaxn][kMaxm];
typedef std::pair<int, int> Pii;

int n, m, ans, ar, tot0;
int fac[30], C[30][30], F[30][kU], can[kU];
Pii X[30];
Mat A, cov, flag;
char line[kMaxm];

void Dfs();
void Tag(int, int, int);

int main() {
	scanf("%d%d", &n, &m); ar = n * m;
	for (int i = C[0][0] = fac[0] = 1; i <= ar; ++i) {
		for (int j = C[i][0] = 1; j <= i; ++j) C[i][j] = Add(C[i - 1][j], C[i - 1][j - 1]);
		fac[i] = Mul(fac[i - 1], i);
	}
	for (int i = 0; i < n; ++i) {
		scanf("%s", line);
		for (int j = 0; j < m; ++j) if (A[i][j] = line[j] == 'X') { Tag(i, j, 1); ++tot0; }
	} Dfs(); printf("%d\n", ans);
	return 0;
}

void Tag(int x, int y, int f) {
	F8R(x, y, nx, ny) cov[nx][ny] += f;
	cov[x][y] += f, A[x][y] = f > 0;
}

void Calc() {
	int cntx;
	for (int i = cntx = 0; i < n; ++i) for (int j = 0; j < m; ++j) if (A[i][j]) X[cntx++] = Pii(i, j);
	int ux = 1 << cntx;
	for (int mas = 0; mas < ux; ++mas) {
		for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) flag[i][j] = 1;
		for (int i = 0; i < cntx; ++i) if (!(mas >> i & 1)) {
			F8R(X[i].fi, X[i].se, nx, ny) flag[nx][ny] = 0;
			flag[X[i].fi][X[i].se] = 0;
		}
		for (int i = can[mas] = 0; i < n; ++i) for (int j = 0; j < m; ++j) can[mas] += flag[i][j];
//		printf(" cnt[%d] = %d\n", mas, can[mas]);
	} F[0][0] = 1;
	for (int i = 1; i <= ar; ++i) for (int mas = 0; mas < ux; ++mas) {
		F[i][mas] = 0;
		Upa(F[i][mas], Mul(F[i - 1][mas], std::max(can[mas] - i + 1, 0)));
		for (int j = 0; j < cntx; ++j) if (mas >> j & 1) Upa(F[i][mas], F[i - 1][mas ^ 1 << j]);
//		printf("   F[%d][%d] = %d\n", i, mas, F[i][mas]);
	} if (cntx - tot0 & 1) Ups(ans, F[ar][ux - 1]); else Upa(ans, F[ar][ux - 1]);
//	printf(" cntx = %d, F[ar][ux - 1] = %d\n", cntx, F[ar][ux - 1]);
}

void Dfs() {
	Calc();
	for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) if (!cov[i][j]) { Tag(i, j, 1); Dfs(); Tag(i, j, -1); }
}
