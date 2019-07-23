#include <cstdio>
#include <cstring>
#include <utility>
#include <vector>

typedef std::pair<int, int> Pii;

const int kMaxn = 105, MOD = 998244353;

int n, m;
int DP[2][kMaxn][kMaxn][kMaxn];
std::vector<Pii> C[kMaxn];

inline void Add(int & x, int y) {
	(x += y) >= MOD ? x -= MOD : 0;
}
bool Judge(int p1, int p2, int p3, int p4);
void Clear(int (*arr)[kMaxn][kMaxn], int last);

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++) C[i].clear();
		for (int i = 0, l, r, x; i < m; i++) {
			scanf("%d%d%d", &l, &r, &x);
			C[r].push_back(Pii(l, x));
		}

		int (*prv)[kMaxn][kMaxn] = DP[0],
			(*nxt)[kMaxn][kMaxn] = DP[1];
		Clear(prv, 1);
		prv[0][0][0] = 1;
		for (int i = 1; i <= n; i++) {
			Clear(nxt, i);
			for (int p1 = 0; p1 < i; p1++) {
				for (int p2 = 0; p2 <= p1; p2++) {
					for (int p3 = 0; p3 <= p2; p3++) {	
						if (!prv[p1][p2][p3]) continue;
						Add(nxt[i - 1][p1][p2], prv[p1][p2][p3]);
						Add(nxt[i - 1][p1][p3], prv[p1][p2][p3]);
						Add(nxt[i - 1][p2][p3], prv[p1][p2][p3]);
						Add(nxt[p1][p2][p3], prv[p1][p2][p3]);
					}
				}
			}
			for (int p1 = 0; p1 < i; p1++) {
				for (int p2 = 0; p2 <= p1; p2++) {
					for (int p3 = 0; p3 <= p2; p3++) {
						if (Judge(p3, p2, p1, i)) continue;
						nxt[p1][p2][p3] = 0;
					}
				}
			}
			std::swap(prv, nxt);
		}
		int ans = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j <= i; j++) {
				for (int k = 0; k <= j; k++)
					Add(ans, prv[i][j][k]);
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}

void Clear(int (*arr)[kMaxn][kMaxn], int last) {
	for (int i = 0; i <= last; i++) {
		for (int j = 0; j <= i; j++) {
			for (int k = 0; k <= j; k++) arr[i][j][k] = 0;
		}
	}
}

bool Judge(int p1, int p2, int p3, int p4) {
	for (int i = 0, cnt; i < C[p4].size(); i++) {
		cnt = 0;
		if (p1 >= C[p4][i].first) ++cnt;
		if (p2 >= C[p4][i].first) ++cnt;
		if (p3 >= C[p4][i].first) ++cnt;
		if (p4 >= C[p4][i].first) ++cnt;
		if (cnt != C[p4][i].second) return false;
	}
	return true;
}
