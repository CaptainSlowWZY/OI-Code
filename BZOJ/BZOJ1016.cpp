// BZOJ 1016
#include <bits/stdc++.h>

const int MAXN = 105;
const int MAXM = 1005;
const int MOD = 31011;

typedef int IntAr[MAXN];

struct Edge {
	int u, v, c;
	bool operator<(const Edge & e) const { return c < e.c; }
} E[MAXM];

int N, M, totc;
IntAr fa, copy, crt, cost, num;

int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
void init_u(int arr[]) {
	for (int i = 1; i <= N; i++) arr[i] = i;
}
bool Kruskal();

int main() {
	scanf("%d%d", &N, &M);
	for (int i = 0; i < M; i++) scanf("%d%d%d", &E[i].u, &E[i].v, &E[i].c);

	if (!Kruskal()) return puts("0"), 0;
	init_u(crt);
	int ans = 1;
	for (int i = 0, curc = 0; i < M && curc < totc; i++, curc++) {
		for (; E[i].c ^ cost[curc]; i++);
		std::vector<int> ee;
		for (int j = i; j < M && E[j].c == E[i].c; j++) ee.push_back(j);
		int sz = (int)ee.size(), cntw = 0;
		memcpy(copy + 1, crt + 1, sizeof(int) * N);
		for (int comb = (1 << num[curc]) - 1, lim = 1 << sz; comb < lim; ) {
			memcpy(fa + 1, copy + 1, sizeof(int) * N);
			int fail = 0;
			for (int j = 0; j < sz; j++)
				if (comb >> j & 1) {
					int u1 = find(E[ee[j]].u), v1 = find(E[ee[j]].v);
					if (u1 == v1) { fail = 1; break; }
					fa[u1] = v1;
				}
			if (!fail) {
				if (++cntw == 1) memcpy(crt + 1, fa + 1, sizeof(int) * N);
			}
			// updata subset
			int x = comb & -comb, y = comb + x;
			comb = (((comb & ~y) / x) >> 1) | y;
		}
		(ans *= cntw % MOD) %= MOD;
	}

	printf("%d\n", ans);
	return 0;
}

bool Kruskal() {
	std::sort(E, E + M);
	int cnte = 0;
	init_u(fa);
	for (int i = 0; i < M; i++) {
		int u1 = find(E[i].u), v1 = find(E[i].v);
		if (u1 ^ v1) {
			fa[u1] = v1;
			if (!totc || E[i].c ^ cost[totc - 1]) cost[totc++] = E[i].c;
			++num[totc - 1], ++cnte;
		}
	}
	return cnte + 1 == N;
}
