// Codeforces 86 C
#include <cstdio>
#include <algorithm>
#include <queue>

const int MAXN = 1005;
const int MOD = 1e9 + 9;

int N, M, RFL[30];
char seq[15];

namespace AC {
	int sz;
	void insert(const char * st);
	void constructer();
	int calc();
}

int main() {
	char st[] = "ACGT";
	for (int i = 0; st[i]; i++) RFL[st[i] - 'A'] = i;
	AC::sz = 1;

	scanf("%d%d", &N, &M);
	for (int i = 0; i < M; i++) {
		scanf("%s", seq);
		AC::insert(seq);
	}

	AC::constructer();

	printf("%d\n", AC::calc());

	return 0;
}

namespace AC {
	const int LEN = 105;

	int T[LEN][4], mxlen[LEN], fail[LEN], DP[MAXN][LEN][11];

	void insert(const char * st) {
		int i, rt, ch;
		for (i = rt = 0, ch; st[i]; i++) {
			if (!T[rt][ch = RFL[st[i] - 'A']]) T[rt][ch] = sz++;
			rt = T[rt][ch];
		}
		mxlen[rt] = i;
	}

	void constructer() {
		std::queue<int> que;
		for (int i = 0; i < 4; i++)
			if (T[0][i]) que.push(T[0][i]);
		while (!que.empty()) {
			int u = que.front(); que.pop();
			for (int i = 0; i < 4; i++) {
				int & v = T[u][i];
				if (v) {
					fail[v] = T[fail[u]][i];
					mxlen[v] = std::max(mxlen[v], mxlen[fail[v]]);
					que.push(v);
				}
				else v = T[fail[u]][i];
			}
		}
	}

	inline void add(int & x, int y) {
		(x += y) >= MOD ? x -= MOD : 0;
	}

	int calc() {
		DP[0][0][0] = 1;
		for (int i = 0; i <= N; i++)
			for (int u = 0; u < sz; u++)
				for (int j = 0; j < 10; j++) {
					if (!DP[i][u][j]) continue;
					for (int ch = 0; ch < 4; ch++) {
						int v = T[u][ch];
						if (mxlen[v] >= j + 1) add(DP[i + 1][v][0], DP[i][u][j]);
						else add(DP[i + 1][v][j + 1], DP[i][u][j]);
					}
				}
		int ret = 0;
		for (int i = 0; i < sz; i++) add(ret, DP[N][i][0]);
		return ret;
	}
}
