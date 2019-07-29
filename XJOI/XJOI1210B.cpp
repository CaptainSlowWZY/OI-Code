#include <algorithm>
#include <cstdio>
#include <cstring>

#define forto(fr, ie, too) for (int ie = back[fr], too = E[ie].to; ie; \
		too = E[ie = E[ie].next].to)

const int kMaxn = 1e5 + 10, kInf = 0x3f3f3f3f;

struct Edge {
	int to, cost, vld, tag, next;
} E[kMaxn << 1];

int n, tote = 1;
int back[kMaxn];

inline void AddEdge(int u, int v, int c) {
	E[++tote] = (Edge){v, c, 0, 0, back[u]}, back[u] = tote;
	E[++tote] = (Edge){u, c, 0, 0, back[v]}, back[v] = tote;
}
bool Check(int);

int main() {
	scanf("%d", &n);
	int lb = kInf, ub = -kInf;
	for (int i = 0, u, v, c; i < n; i++) {
		scanf("%d%d%d", &u, &v, &c);
		AddEdge(u, v, c);
		lb = std::min(lb, c);
		ub = std::max(ub, c);
	}

//	printf(" [%d, %d]\n", lb, ub);
	if ((n & 1) || !Check(lb)) {
		puts("no answer");
		return 0;
	}
	++ub;
	for (int mid; ub - lb > 1; ) {
		mid = (lb + ub) / 2;
		if (Check(mid)) lb = mid;
		else ub = mid;
	}
	printf("%d\n", lb);
	return 0;
}

bool Check(int x) {
//	printf(" check %d\n", x);
	int cnte = 0;
	static int deg[kMaxn];
	memset(deg, 0, sizeof deg);
	for (int i = 1; i <= n; i++) {
		forto(i, e, v) {
			if (E[e].vld = (E[e].cost >= x)) {
				++deg[i], ++deg[v], ++cnte;
			}
			E[e].tag = 0;
		}
	}

	if (cnte / 2 < n / 2) return false;
	int hd = 0, tl = 0, rem = n;
	static int que[kMaxn], vis[kMaxn], match[kMaxn];
	for (int i = 1; i <= n; i++) {
		vis[i] = match[i] = 0;
		if (!(deg[i] >>= 1)) return false;
		if (deg[i] == 1) {
		//	if (x == 2) printf(" inq %d\n", i);
			que[tl++] = i, vis[i] = 1;
		}
	}
	for (int u; hd < tl && rem; ) {
		if (match[u = que[hd++]]) continue;
		if (!deg[u]) return false;
		forto(u, e, v) {
			if (!E[e].vld || E[e].tag) continue;
			E[e].tag = E[e ^ 1].tag = 1;
		//	if (x == 2) printf("   %d match %d\n", u, v);
			match[u] = match[v] = 1, rem -= 2, vis[v] = 1;
			forto(v, ee, vv) {
				if (!E[ee].vld || E[ee].tag) continue;
			//	if (x == 2) printf("   %d-> %d\n", v, vv);
				E[ee].tag = E[ee ^ 1].tag = 1;
				if ((--deg[vv]) == 1 && !vis[vv]) {
					que[tl++] = vv, vis[vv] = 1;
				}
			}
			break;
		}
	}
	if (!rem) return true;
	int lpsz = 0;
	for (int i = 1; i <= n; i++) {
		if (match[i]) continue;
		if (deg[i] == 2) ++lpsz;
		else return false;
	}
	return !(lpsz & 1);
}
