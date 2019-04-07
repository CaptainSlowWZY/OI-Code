// POI2005 SZA-Template
#include <cstdio>
#include <cstring>
#include <algorithm>

#define forto(_) for (int e = last[_], v = E[e].to; e; \
	v = E[e = E[e].next].to)

const int kLen = 5e5 + 10;

struct Edge {
	int to, next;
} E[kLen];

char S[kLen];
int mxgp, len, tote, ans;
int fail[kLen], last[kLen], tag[kLen], nxt[kLen], prv[kLen];

inline void AddEdge(int u, int v) {
	E[++tote] = (Edge){v, last[u]}, last[u] = tote;
}
void Dfs(int u);

int main() {
	scanf("%s", S);

	len = strlen(S);
	fail[0] = fail[1] = 0;
	AddEdge(0, 1);
	for (int i = 1, j; i < len; i++) {
		for (j = fail[i]; j && S[j] ^ S[i]; j = fail[j]);
		fail[i + 1] = S[i] == S[j] ? j + 1 : 0;
		AddEdge(fail[i + 1], i + 1);
	}
	tag[len] = 1;
	for (int i = len; i > 0; i = fail[i]) tag[fail[i]] = 1;
	prv[0] = nxt[len] = 0;
	for (int i = 0; i <= len; i++) {
		prv[i] = i - 1;
		nxt[i] = i + 1;
	}
	mxgp = 1;
	Dfs(0);

	printf("%d\n", ans);
	return 0;
}

void Erase(int u) {
	nxt[prv[u]] = nxt[u];
	prv[nxt[u]] = prv[u];
	mxgp = std::max(mxgp, nxt[u] - prv[u]);
	forto(u) Erase(v);
}

void Dfs(int u) {
	if (mxgp <= u) return (void)(ans = u);
	int son = -1;
	forto(u) {
		if (tag[v]) {
			son = v;
			continue;
		}
		Erase(v);
	}
	if (~son) Dfs(son);
}
