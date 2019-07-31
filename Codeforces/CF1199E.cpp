#pragma GCC optimize(2)
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

#define fir first
#define sec second
#define pb push_back

typedef long long LL;
typedef std::pair<int, int> Pii;

const int kMaxn = 3e5 + 10, kMaxm = 5e5 + 10, kInf = 0x3f3f3f3f;

template <typename T> inline
void UMin(T & x, const T & y) {
	if (x > y) x = y;
}
template <typename T> inline
void UMax(T & x, const T & y) {
	if (x < y) x = y;
}

int n, m;
std::vector<Pii> G[kMaxn];
int deg0[kMaxn], deg[kMaxn], used[kMaxn], eid[kMaxn];
int U[kMaxm], V[kMaxm];
// std::set<Pii> hap;
std::priority_queue<Pii, std::vector<Pii>, std::greater<Pii> > hap;

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= 3 * n; i++) {
			G[i].clear();
			deg0[i] = 0;
		}
		for (int i = 0, u, v; i < m; i++) {
			scanf("%d%d", U + i, V + i);
			u = U[i], v = V[i];
			G[u].pb(Pii(v, i));
			G[v].pb(Pii(u, i));
			++deg0[u], ++deg0[v];
		}

		for (int i = 1; i <= 3 * n; i++) {
			deg[i] = deg0[i];
			hap.push(Pii(deg[i], i));
			used[i] = 0;
		}
	//	memset(used, 0, sizeof used);
		int totm = 0;
		for (; !hap.empty() && totm < n; ) {
		//	Pii cur = *hap.begin(); hap.erase(hap.begin());
			Pii cur = hap.top(); hap.pop();
			if (used[cur.sec]) continue;
		//	printf(" deg %d, u %d\n", cur.fir, cur.sec);
			int mind = kInf, mv = -1, me;
			for (auto e : G[cur.sec]) {
				if (used[e.fir]) continue;
				if (deg[e.fir] < mind) {
					mind = deg[e.fir];
					mv = e.fir;
					me = e.sec;
				}
			}
			if (mv == -1) continue;
			eid[totm++] = me;
			used[cur.sec] = used[mv] = 1;
			for (auto e : G[cur.sec]) {
				if (used[e.fir]) continue;
			/*	auto it = hap.find(Pii(deg[e.fir], e.fir));
				if (it == hap.end()) continue;
				hap.erase(it);
				hap.insert(Pii(--deg[e.fir], e.fir));*/
				--deg[e.fir];
			}
			for (auto e : G[mv]) {
				if (used[e.fir]) continue;
			/*	auto it = hap.find(Pii(deg[e.fir], e.fir));
				if (it == hap.end()) continue;
				hap.erase(it);
				hap.insert(Pii(--deg[e.fir], e.fir));*/
				--deg[e.fir];
			}
		}
	//	hap.clear();
		for (; !hap.empty(); hap.pop());
		if (totm >= n) {
			puts("Matching");
			for (int i = 0; i < n; i++)
				printf("%d ", eid[i] + 1);
			putchar('\n');
			continue;
		} else {
		/*	for (int i = 1; i <= 3 * n; i++) used[i] = 0;
			for (int i = 0; i < totm; i++) {
				used[U[eid[i]]] = used[V[eid[i]]] = 1;
			}*/
			totm = 0;
			puts("IndSet"); // Oh! No IMPOSSIBLE!
			for (int i = 1; i <= 3 * n; i++) {
				if (used[i]) continue;
				printf("%d ", i);
				if (++totm == n) break;
			}
			putchar('\n');
		}
	/*	for (int i = 1; i <= 3 * n; i++) {
			deg[i] = deg0[i];
			hap.insert(Pii(deg[i], i));
		}
		memset(used, 0, sizeof used);
		int tots = 0;
		for (; !hap.empty() && tots < n; ) {
			Pii cur = *hap.begin(); hap.erase(hap.begin());
			if (used[cur.sec]) continue;
		//	printf(" !!deg %d, u %d\n", cur.fir, cur.sec);
			eid[tots++] = cur.sec;
			for (auto ee : G[cur.sec]) used[ee.fir] = 1;
			for (auto ee : G[cur.sec]) {
			//	printf(" clear %d\n", e.fir);
				for (auto e : G[ee.fir]) {
					if (used[e.fir]) continue;
					auto it = hap.find(Pii(deg[e.fir], e.fir));
					if (it == hap.end()) continue;
					hap.erase(it);
					hap.insert(Pii(--deg[e.fir], e.fir));
				}
			}
		}
		hap.clear();
		if (tots >= n) {
			puts("IndSet");
			for (int i = 0; i < n; i++)
				printf("%d ", eid[i]);
			putchar('\n');
			continue;
		} else puts("Impossible");*/
	}
	return 0;
}
