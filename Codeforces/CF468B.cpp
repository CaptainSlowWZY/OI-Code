// Codeforces 468 B
// Round #268 (Div. 1)
#include <cstdio>
#include <map>
const int MAXN = 1e5 + 10;

int N, A, B, P[MAXN];
std::map<int, int> match;

bool dfs(int, int, int);

int main() {
	scanf("%d%d%d", &N, &A, &B);
	for (int i = 0; i < N; i++) {
		scanf("%d", &P[i]);
		match[P[i]] = -1;
	}
	
	for (int i = 0; i < N; i++) {
		if (~match[P[i]]) continue;
		if (!(dfs(P[i], A, 0) || dfs(P[i], B, 1))) return puts("NO"), 0;
	}
	puts("YES");
	for (int i = 0; i < N; i++) printf("%d ", match[P[i]]);	
	putchar('\n');
	return 0;
}

bool dfs(int u, int sd, int f) {
	if (!match.count(sd - u)) return false;
	if ((u << 1) == sd) return match[u] = f, true;

	int & now = match[sd - u];
	if (now == -1 || now == f || dfs(A + B - (sd << 1) + u, sd, f))
		return match[u] = now = f, true;
	return false;
}

// AC!!!
