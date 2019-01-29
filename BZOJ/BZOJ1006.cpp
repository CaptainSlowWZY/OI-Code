// BZOJ 1006
#include <cstdio>
#include <algorithm>
#include <queue>

#define forto(_) for (int e = last[_], v = E[e].to; e; v = E[e = E[e].next].to)

const int MAXN = 1e4 + 10;
const int MAXM = 1e6 + 10;

typedef std::queue<int> Bucket;
typedef int IntAr[MAXN];

struct Edge {
	int to, next;
} E[MAXM << 1];

Bucket B[MAXN];
int N, M, tote;
IntAr last, eng, num, flag, PEO, col;

inline void add_edge(int u, int v) {
	E[++tote] = (Edge){v, last[u]}, last[u] = tote;
	E[++tote] = (Edge){u, last[v]}, last[v] = tote;
}

int main() {
	scanf("%d%d", &N, &M);
	for (int i = 0, ui, vi; i < M; i++) {
		scanf("%d%d", &ui, &vi);
		add_edge(ui, vi);
	}

	for (int i = 1; i <= N; i++) B[0].push(i);
	int top = 0;

	// MCS
	for (int i = N; i > 0; i--) {
		int u = -1;
		for (; top >= 0 && u == -1; --top) {
			for (; !B[top].empty() && u == -1; B[top].pop()) {
				int v = B[top].front();
				if (eng[v] == top && !num[v]) {
					u = v;
					break;
				}
			}
			if (~u) break;
		}
		PEO[N - i] = u, num[u] = i;
		forto(u) {
			if (num[v]) continue;
			if (++eng[v] > top) top = eng[v];
			B[eng[v]].push(v);
		}
	}

	// color
	int ans = 0;
	for (int i = 0; i < N; i++) {
		int u = PEO[i];
		forto(u) flag[col[v]] = u;
		for (int j = 1; j <= N; j++)
			if (flag[j] ^ u) {
				col[u] = j;
				ans = std::max(ans, j);
				break;
			}
	}

	printf("%d\n", ans);

	return 0;
}
