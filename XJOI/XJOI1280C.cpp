#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

typedef long long LL;

const int kLen = 1e6 + 5;
const LL kInf64 = 0x3f3f3f3f3f3f3f3f;

template <typename T> inline
void UMin(T & x, const T & y) { if (x > y) x = y; }
template <typename T> inline
void UMax(T & x, const T & y) { if (x < y) x = y; }

int n;
char S[kLen];

namespace acm {
	void Insert(char st[]);
	LL Gao();
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%s", S);
		acm::Insert(S);
	} printf("%lld\n", acm::Gao());
	return 0;
}

namespace acm {
	typedef int IAr[kLen];
	int sz;
	int T[kLen][26];
	IAr val, fa, fail, ideg;
	LL DP[kLen];
	std::queue<int> que;

	void Insert(char st[]) {
		int u = 0;
		for (int c, i = 0; st[i]; ++i) {
			if (!T[u][c = st[i] - 'a']) 
				fa[T[u][c] = ++sz] = u;
			u = T[u][c], ++val[u];
		}
	}
	LL Gao() {
		for (int i = 0; i < 26; ++i) {
			if (!T[0][i]) continue;
			que.push(T[0][i]); fail[T[0][i]] = 0;
		}
		while (!que.empty()) {
			int u = que.front(); que.pop();
			for (int i = 0; i < 26; ++i) {
				int & v = T[u][i];
				if (v) {
					fail[v] = T[fail[u]][i];
					que.push(v);
				} else v = T[fail[u]][i];
			}
		}
		for (int i = 1; i <= sz; ++i) {
			++ideg[fa[i]], ++ideg[fail[i]];
		}
		for (int i = 1; i <= sz; ++i)
			if (!ideg[i]) { que.push(i); DP[i] = 0; }
		while (!que.empty()) {
			int u = que.front(); que.pop();			
			UMax(DP[fa[u]], DP[u] + val[u]);
			if (!--ideg[fa[u]]) que.push(fa[u]);
			UMax(DP[fail[u]], DP[u] + val[u]);
			if (!--ideg[fail[u]]) que.push(fail[u]);
		} return DP[0];
	}
}
