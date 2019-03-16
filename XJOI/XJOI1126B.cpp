#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <queue>

const int kMaxn = 1e6 + 10;

typedef long long LL;

int n, A[kMaxn];

namespace fast_io {
	template <typename T>
		void Read(T & x) {
			register char ch = getchar();
			register bool f = false; x = 0;
			for (; !isdigit(ch); f |= (ch == '-'), ch = getchar());
			for (; isdigit(ch); ch = getchar())
				x = (x << 3) + (x << 1) + (ch ^ '0');
			f ? x = -x : 0;
		}
}
inline int Calc(int d) {
	return std::min(d, n - d);
}
namespace solver1 {
	void Solve();
}
namespace solver2 {
	void Solve();
}
namespace solver3 {
	void Solve();
}

int main() {
	fast_io::Read(n);

	if (n <= 9) solver1::Solve();
	else if (n <= 100) solver2::Solve();
	else solver3::Solve();
//	solver3::Solve();

	return 0;
}

namespace solver3 {
	LL sum[kMaxn];

	void Solve() {
		for (int i = 0, pi; i < n; i++) {
			fast_io::Read(pi);
			++A[pi - 1];
		}
		for (int i = 0; i < n; i++) {
			A[i] = 1 - A[i];
			sum[i] = sum[i - 1] + A[i];
		}
		std::sort(sum, sum + n);
		LL ans = 0, mid = sum[n >> 1];
		for (int i = 0; i < n; i++) {
			ans += std::abs(sum[i] - mid);
		}
		printf("%lld\n", ans);
	}
}

#define forto(_) for (int e = last[_], v = E[e].to; e; v = E[e = E[e].next].to)
#define forback(_) for (int _ = T; _ ^ S; _ = pre[_])

namespace solver2 {
	const int kMaxv = 105, kMaxe = 1e3, kInf = 0x7f7f7f7f;
	typedef int IAr[kMaxv];

	struct Edge {
		int to, capt, cost, next;
	} E[kMaxe << 1];

	int S, T, tote;
	LL dist[kMaxn];
	IAr last, in_que, pre, pree;

	inline void AddEdge(int u, int v, int cap, int cst) {
		E[++tote] = (Edge){v, cap, cst, last[u]}, last[u] = tote;
		E[++tote] = (Edge){u, 0, -cst, last[v]}, last[v] = tote;
	}
	bool SPFA() {
		memset(pre, 0xff, sizeof pre);
		memset(dist, 0x7f, sizeof dist);
		std::queue<int> que;
		for (dist[S] = 0, que.push(S), in_que[S] = 1; !que.empty(); ) {
			int u = que.front(); que.pop();
			forto(u) {
				if (E[e].capt > 0 && dist[v] > dist[u] + E[e].cost) {
					dist[v] = dist[u] + E[e].cost;
					pre[v] = u, pree[v] = e;
					if (!in_que[v]) {
						que.push(v);
						in_que[v] = 1;
					}
				}
			}
			in_que[u] = 0;
		}
		return ~pre[T];
	}
	LL MinCostFlow() {
		LL sumc = 0;
		while (SPFA()) {
			LL minc = kInf;
			forback(u) {
				minc = std::min<LL>(minc, E[pree[u]].capt);
			}
			sumc += minc * dist[T];
			forback(u) {
				E[pree[u]].capt -= minc;
				E[pree[u] ^ 1].capt += minc;
			}
		}
		return sumc;
	}
	void Solve() {
		for (int i = 0, pi; i < n; i++) {
			fast_io::Read(pi);
			++A[pi - 1];
		}
		T = (S = n) + 1;
		tote = 1;
		for (int i = 0; i < n; i++) {
			AddEdge(i, (i + 1) % n, kInf, 1);
			AddEdge((i + 1) % n, i, kInf, 1); 
			if (A[i] > 1) AddEdge(S, i, A[i] - 1, 0);
			if (A[i] < 1) AddEdge(i, T, 1 - A[i], 0);
		}
		printf("%lld\n", MinCostFlow());
	}
}

// for n <= 9
namespace solver1 {
	const int kMaxn = 15;

	int P[kMaxn];

	void Solve() {
		for (int i = 0; i < n; i++) {
			fast_io::Read(A[i]);
			P[i] = i + 1;
		}
		LL ans = 1e15, ret;
		do {
			ret = 0;
			for (int i = 0; i < n; i++) {
				ret += Calc(std::abs(A[i] - P[i]));
			}
			ans = std::min(ans, ret);
		} while (std::next_permutation(P, P + n));

		printf("%lld\n", ans);
	}
}
