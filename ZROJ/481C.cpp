#include <algorithm>
#include <cstdio>
#include <queue>

const int kMaxm = 1e6 + 5;

int n, m, tp, xs[kMaxm];

namespace trie { void Insert(int, int); void Gao(); }

int main() {
	scanf("%d%d%d", &n, &m, &tp);
	for (int i = 1; i <= m; ++i) { scanf("%d", xs + i); xs[i] ^= xs[i - 1]; }
	int noh = ~(1 << n - 1);
	for (int suf, i = 0; i <= m; ++i) { suf = xs[m] ^ xs[i], trie::Insert(xs[i] & noh ^ suf >> 1, xs[i] >> n - 1 ^ suf & 1); }
	trie::Gao();
	return 0;
}

namespace trie {
	const int kMaxv = kMaxm << 5;
	int size, T[kMaxv][2], exs[kMaxv], D[kMaxv], max[kMaxv];
	std::queue<int> que;

	void Insert(int val, int tag) {
	//	assert(tag <= 1);
		int u = 0;
		for (int c, i = n - 2; ~i; --i) {
			if (!T[u][c = val >> i & 1]) T[u][c] = ++size;
			u = T[u][c];
		} exs[u] |= tag << 1;
	}
	void Gao() {
		for (int i = size, v; ~i; --i) {
			if (!(v = T[i][0] + T[i][1])) max[i] = exs[i] != 3; 
			else if (!T[i][0] || !T[i][1]) { D[i] = D[v] + 1, max[i] = max[v] | 1 << D[i]; }
			else { D[i] = D[T[i][0]] + 1, max[i] = std::max(max[T[i][0]], max[T[i][1]]); }
		} que.push(0); 
		int ans = max[0], way = 0;
		printf("%d\n", ans);
		if (!tp) return;
		for (int u; !que.empty(); ) {
			u = que.front(), que.pop();
			if (ans >> D[u] & 1) {
				if (!D[u]) { way += exs[u] != 3; continue; }
				if (!T[u][0] || !T[u][1]) que.push(T[u][0] + T[u][1]);
			} else {
				if (!D[u]) { way += __builtin_popcount(exs[u]); continue; }
				if (T[u][0]) que.push(T[u][0]);
				if (T[u][1]) que.push(T[u][1]);
			}
		} printf("%d\n", way);
	}
}
