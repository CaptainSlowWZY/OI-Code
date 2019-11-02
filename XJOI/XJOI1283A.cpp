#include <algorithm>
#include <cctype>
#include <cstdio>
#include <queue>

#define rg register
#define gch getchar
#define pch putchar
#define fi first
#define se second
#define pb push_back
#define ppb pop_back
#define SZ(_) (int)_.size()

typedef std::pair<int, int> Pii;

const int kMaxn = 16, kMaxm = 301, kMod = 1e9 + 7;
const int kDx[] = {-1, 0, 0, 1}, kDy[] = {0, -1, 1, 0};

template <typename T> inline
void UMin(T & x, const T & y) { if (x > y) x = y; }
inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + kMod : a; }
inline int Mul(int a, int b) { return 1ll * a * b % kMod; }
inline void Upa(int & a, int b) { a = Add(a, b); }
inline void Upm(int & a, int b) { a = Mul(a, b); }
inline void operator*=(Pii & a, const Pii & b) {
	Upm(a.fi, b.fi); a.se += b.se;
}

int n, m;
int vis[kMaxn << 1][kMaxn], ans[kMaxm];
Pii A[kMaxn][kMaxn];
std::vector<Pii> que, fig;

namespace fast_io { template <typename T> void Read(T &); }
void Dfs();

int main() {
	using fast_io::Read;
	Read(n); Read(m);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			Read(A[i][j].fi); Read(A[i][j].se);
		}
	}
	for (int i = 1; i <= 2 * n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (i > n || j > 1) vis[i][j] = 1;
		}
	} que.pb({n, 1}); Dfs();
	for (int i = 0; i <= m; ++i)
		printf("%d%c", ans[i], " \n"[i == m]);
	return 0;
}

void Gao() {
	int x0 = n;
	for (auto & p : fig) UMin(x0, p.fi);
	Pii res = {1, 0};
	for (auto & p : fig) res *= A[p.fi - x0][p.se - 1];
	Upa(ans[res.se], res.fi);
}

void Dfs() {
	if (SZ(fig) == n) return Gao();
	if (que.empty()) return;
	Pii la = que.back();
	que.ppb(); Dfs();
	fig.pb(la);
	int cnt = 0;
	for (int i = 0, nx, ny; i < 4; ++i) {
		nx = la.fi + kDx[i], ny = la.se + kDy[i];
		if (vis[nx][ny]) {
			que.pb({nx, ny}); vis[nx][ny] = 0; ++cnt;
		}
	} 
	for (Dfs(); cnt--; que.ppb())
		vis[que.back().fi][que.back().se] = 1;
	fig.ppb(); que.pb(la);
}

namespace fast_io {
	template <typename T>
		void Read(T & x) {
			rg char ch = gch(); x = 0;
			for (; !isdigit(ch); ch = gch());
			for (; isdigit(ch); ch = gch())
				x = (x << 1) + (x << 3) + (ch ^ '0');
		}
}
