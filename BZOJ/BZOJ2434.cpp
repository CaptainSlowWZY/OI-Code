// NOI 2011
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <queue>

const int kLen = 1e5 + 10;

namespace acm {
	void construct(const char * st);
	void Solve();
}

struct Qry {
	int x, y, id;
	bool operator<(const Qry & q) const {
		return y < q.y;
	}
} qur[kLen];

char IN[kLen];
int m, ans[kLen];

int main() {
	scanf("%s%d", IN, &m);
	acm::construct(IN);
	
	for (int i = 0; i < m; i++) {
		scanf("%d%d", &qur[i].x, &qur[i].y);
		qur[i].id = i;
	}

	std::sort(qur, qur + m);
	acm::Solve();

	for (int i = 0; i < m; i++) printf("%d\n", ans[i]);
	return 0;
}

namespace acm {
	struct Edge {
		int to, next;
	} E[kLen];
	typedef int IAr[kLen];

	int sz = 1, tote, tots;
	int T[kLen][26];
	IAr end, prv, last, fail, idfn, odfn;

	inline void AddEdge(int u, int v) {
		E[++tote] = (Edge){v, last[u]}, last[u] = tote;
	}
	void Dfs(int u) {
		static int dfs_clock = 0;
		idfn[u] = ++dfs_clock;
		for (int e = last[u], v = E[e].to; e;
				v = E[e = E[e].next].to) {
			Dfs(v);
		}
		odfn[u] = dfs_clock;
	}
	void construct(const char * st) {
		int cur = 0;
		for (int i = 0, ch; st[i]; i++) {
			if (islower(st[i])) {
				if (!T[cur][ch = st[i] - 'a']) {
					prv[T[cur][ch] = sz++] = cur;
				}
				cur = T[cur][ch];
			} else if (st[i] == 'B') {
				cur = prv[cur];
			} else {
				end[++tots] = cur;
			}
		}

		std::queue<int> que;
		for (int i = 0; i < 26; i++) {
			if (!T[0][i]) continue;
			que.push(T[0][i]);
			AddEdge(0, T[0][i]);
		}
		for (int u; !que.empty(); ) {
			u = que.front(); que.pop();
			for (int i = 0; i < 26; i++) {
				int & nxt = T[u][i];
				if (nxt) {
					fail[nxt] = T[fail[u]][i];
					AddEdge(fail[nxt], nxt);
					que.push(nxt);
				} else nxt = T[fail[u]][i];
			}
		}

		Dfs(0);
	}
	namespace bit {
		int T[kLen];

		void Add(int p, int del = 1) {
			for (; p <= sz; p += p & -p) T[p] += del;
		}
		int Query(int p) {
			int ret = 0;
			for (; p; p &= p - 1) ret += T[p];
			return ret;
		}
	}
	void Solve() {
		for (int cur = 0, i = 0, j = 0, curs = 0; IN[i]; i++) {
			if (IN[i] == 'B') {
				bit::Add(idfn[cur], -1);
				cur = prv[cur];
			} else if (IN[i] == 'P') {
				++curs;
				for (int edx; j < m && qur[j].y == curs; j++) {
					edx = end[qur[j].x];
					ans[qur[j].id] = bit::Query(odfn[edx]) -
									bit::Query(idfn[edx] - 1);
				}
			} else {
				cur = T[cur][IN[i] - 'a'];
				bit::Add(idfn[cur]);
			}
		}
	}
}
