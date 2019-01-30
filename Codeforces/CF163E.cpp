// Codeforces 163 E
#include <cstdio>
#include <cctype>
#include <queue>
#include <vector>

const int LEN = 1e6 + 10;
const int MAXK = 1e5 + 10;

char S[LEN];
int N, K;

namespace AC {
	int sz, T[LEN][26], fail[LEN], pos[MAXK], able[MAXK];
	void insert(const char * st, int id);
	void constructer();
	int match(const char * st);
	void disable(int id);
	void enable(int id);
}

int main() {
	AC::sz = 1;

	scanf("%d%d", &N, &K);
	for (int i = 1; i <= K; i++) {
		scanf("%s", S);
		AC::insert(S, i);
	}
	AC::constructer();

	for (int i = 0; i < N; i++) {
		scanf("%s", S);
		if (S[0] == '?') printf("%d\n", AC::match(S + 1));
		else {
			int person = 0;
			for (int i = 1; isdigit(S[i]); i++) person = person * 10 + (S[i] ^ '0');
			if (S[0] == '-') AC::disable(person);
			else AC::enable(person);
		}
	}

	return 0;
}

namespace AC {
	void insert(const char * st, int id) {
		int rt = 0;
		able[id] = 1;
		for (int i = 0, ch; st[i]; i++) {
			if (!T[rt][ch = st[i] - 'a']) T[rt][ch] = sz++;
			rt = T[rt][ch];
		}
		pos[id] = rt;
	}

	namespace FailT {
		std::vector<int> G[LEN];
		int dfs_clock, idfn[LEN], odfn[LEN];

		inline void add_edge(int u, int v) {
			G[u].push_back(v);
		}
		void dfs(int u) {
			idfn[u] = ++dfs_clock;
			for (auto v : G[u]) dfs(v);
			odfn[u] = dfs_clock;
		}

		namespace BIT {
			int dat[LEN];

			void _add(int p, int delta) {
				for (; p <= dfs_clock; p += p & -p) dat[p] += delta;
			}
			inline void add(int fir, int lst, int delta) {
				_add(fir, delta);
				_add(lst + 1, -delta);
			}
			int query(int p) {
				int ret = 0;
				for (; p > 0; p &= p - 1) ret += dat[p];
				return ret;
			}
		}

		void init() {
			for (int i = 1; i <= K; i++) BIT::add(idfn[pos[i]], odfn[pos[i]], 1);
		}
		inline int query(int u) {
			return BIT::query(idfn[u]);
		}
	}

	void constructer() {
		std::queue<int> que;
		for (int i = 0; i < 26; i++)
			if (T[0][i]) {
				FailT::add_edge(0, T[0][i]);
				que.push(T[0][i]);
			}
		while (!que.empty()) {
			int u = que.front(); que.pop();
			for (int i = 0; i < 26; i++) {
				int & v = T[u][i];
				if (v) {
					fail[v] = T[fail[u]][i];
					FailT::add_edge(fail[v], v);
					que.push(v);
				}
				else v = T[fail[u]][i];
			}
		}
		FailT::dfs(0);
		FailT::init();
	}
	int match(const char * st) {
		int ret = 0, rt = 0;
		for (int i = 0; st[i]; i++) {
			rt = T[rt][st[i] - 'a'];
			ret += FailT::query(rt);
		}
		return ret;
	}
	void disable(int id) {
		if (able[id]) {
			able[id] = 0;
			int u = pos[id];
			FailT::BIT::add(FailT::idfn[u], FailT::odfn[u], -1);
		}
	}
	void enable(int id) {
		if (!able[id]) {
			able[id] = 1;
			int u = pos[id];
			FailT::BIT::add(FailT::idfn[u], FailT::odfn[u], 1);
		}
	}
}
