// AtCoder Grand Contest 016 D
#pragma GCC diagnostic error "-std=c++11"
#include <cstdio>
#include <vector>
#include <map>

#define fir first
#define sec second
#define pb push_back

const int MAXN = 1e5 + 10;

typedef std::map<int, int> MyMp;
typedef int IntAr[MAXN];

int N, S, T, tote;
IntAr dgr, A, B, vis;
MyMp Mp;
std::vector<int> G[MAXN];

namespace FastIO {
	template <typename T>
		void read(T & x) {
			x = 0; register char ch = getchar();
			for (; ch < '0' || ch > '9'; ch = getchar());
			for (; ch >= '0' && ch <= '9'; x = (x << 3) + (x << 1) + (ch ^ '0'), ch = getchar());
		}
}
inline void add_edge(int u, int v) {
	++tote, ++dgr[u], --dgr[v];
	G[u].pb(v);
}
void dfs(int u) {
	vis[u] = 1;
	for (auto v : G[u])
		if (!vis[v]) dfs(v);
}

int main() {
	using FastIO::read;
	read(N);
	int _xor = 0;
	for (int i = 0; i < N; i++) {
		read(A[i]);
		_xor ^= A[i], Mp[A[i]] = 0;
	}
	for (int i = 0; i < N; i++) {
		read(B[i]);
		Mp[B[i]] = 0;
	}
	Mp[_xor] = 0;
	int rk = 0;
	for (MyMp::iterator it = Mp.begin(); it != Mp.end(); ++it) it->sec = ++rk;
	for (int i = 0; i < N; i++) A[i] = Mp[A[i]], B[i] = Mp[B[i]];
	S = _xor = Mp[_xor];
	for (int i = 0; i < N; i++)
		if (A[i] ^ B[i]) add_edge(B[i], A[i]);
	int ans = 0;
	if (dgr[S] == 1) {
		T = -1;
		for (int i = 1; i <= rk; i++)
			if (i ^ _xor && dgr[i] == -1) {
				if (~T) return puts("-1"), 0;
				T = i;
			}
		add_edge(T, S), --ans;
	}
	else {
		T = S;
		for (int i = 1; i <= rk; i++)
			if (dgr[i]) return puts("-1"), 0;
	}
	for (int i = 1; i <= rk; i++) {
		if (G[i].size() && !vis[i]) {
			++ans;
			dfs(i);
		}
	}
	ans += tote;
	if (vis[S]) --ans;
	printf("%d\n", ans);
	return 0;
}

// AC!!!
