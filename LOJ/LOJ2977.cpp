#include <algorithm>
#include <cstdio>
#include <queue>
#include <random>

#define fi first
#define se second

const int kMaxn = 235, kInf = 0x3f3f3f3f, kDx[4] = {-1, 0, 0, 1}, kDy[4] = {0, -1, 1, 0};

typedef std::pair<int, int> Pii;
typedef int Mat[kMaxn][kMaxn];

int n, m, k, cntv, u;
int val[kMaxn], mc[kMaxn];
Pii ans, F[kMaxn][kMaxn][(1 << 5) + 5], M[kMaxn][kMaxn];
Mat C0, A, inq, C;
std::queue<Pii> Q;
std::mt19937 gen(19260817);

template <typename T> inline
void UMin(T & x, const T & y) { if (x > y) x = y; }
Pii operator+(const Pii & a, const Pii & b) { return {a.fi + b.fi, a.se + b.se}; }
Pii operator-(const Pii & a, const Pii & b) { return {a.fi - b.fi, a.se - b.se}; }
void Gao();

int main() {
	int t; scanf("%d", &t);
	while (t--) {
		scanf("%d%d%d", &n, &m, &k); u = (1 << k) - 1, cntv = 0;
		for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) scanf("%d", C0[i] + j);
		for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) { scanf("%d", A[i] + j); val[cntv++] = A[i][j]; }
		std::sort(val, val + cntv); cntv = std::unique(val, val + cntv) - val, ans = {kInf - 5, kInf};
		for (int t = 233; t--; ) Gao();
		if (ans.fi == kInf) puts("-1 -1");
		else printf("%d %d\n", ans.fi, ans.se);
	} return 0;
}

Pii Check(int mid) {
	for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
		for (int s = 0; s <= u; ++s) F[i][j][s] = {kInf, kInf};
		if (~C0[i][j]) {
			M[i][j] = {1, A[i][j] <= mid ? -1 : 1}; F[i][j][1 << C[i][j]] = M[i][j];
		}
	}
	for (int s = 1; s <= u; ++s) {
		for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
			for (int t = s & s - 1; t != s; t = t - 1 & s) UMin(F[i][j][s], F[i][j][t] + F[i][j][s ^ t] - M[i][j]);
			if (F[i][j][s].fi < kInf) { Q.push(Pii(i, j)); inq[i][j] = 1; }
		}
		while (!Q.empty()) {
			Pii u = Q.front(); Q.pop();
			for (int nx, ny, k = 0; k < 4; ++k) {
				nx = u.fi + kDx[k], ny = u.se + kDy[k];
				if (nx >= 0 && nx < n && ny >= 0 && ny < m && ~C0[nx][ny] && F[u.fi][u.se][s] + M[nx][ny] < F[nx][ny][s]) {
					F[nx][ny][s] = F[u.fi][u.se][s] + M[nx][ny];
					if (!inq[nx][ny]) { Q.push(Pii(nx, ny)); inq[nx][ny] = 1; }
				}
			} inq[u.fi][u.se] = 0;
		}
	}
	Pii res = {kInf, kInf};
	for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) UMin(res, F[i][j][u]);
	return res;
}

void Gao() {
	for (int i = n * m; i; --i) mc[i] = gen() % k;
	for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) if (~C0[i][j]) C[i][j] = mc[C0[i][j]];
	int fr = 0, lt = cntv - 1;
	Pii res = {kInf, kInf};
	for (int mid; fr <= lt; ) {
		mid = fr + lt >> 1;
		Pii t = Check(val[mid]);
		if (t.fi > ans.fi) break;
		if (t.se <= 0) { res = {t.fi, val[mid]}, lt = mid - 1; } else fr = mid + 1;
	} UMin(ans, res);
}
