#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

#define forto(_) for (int e = back[_], v; ~e; e = prv[e])

const int kMaxn = 2e5 + 5;

typedef int IAr2[kMaxn << 1];

namespace solver1 {
	void Solve();
}

int n, m, src, trg;
int back[kMaxn];
IAr2 A, B, C, prv;

int main() {
	memset(back, 0xff, sizeof back);

	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++) {
		scanf("%d%d%d", A + i, B + i, C + i);
		prv[i] = back[A[i]], back[A[i]] = i;
		A[m + i] = B[i], B[m + i] = A[i], C[m + i] = C[i];
		prv[m + i] = back[B[i]], back[B[i]] = m + i;
	}
	scanf("%d%d", &src, &trg);

	solver1::Solve();

	return 0;
}

namespace solver1 {
	long long dis[kMaxn], dis0[kMaxn];
	int inq[kMaxn];
	std::queue<int> que;

	int Spfa() {
		memset(dis, 0x7f, sizeof dis);
		dis[src] = 0;
		que.push(src), inq[src] = 1;
		for (int u; !que.empty(); que.pop()) {
			u = que.front();
			forto(u) {
				if (dis[v = B[e]] > dis[u] + C[e]) {
					dis[v] = dis[u] + C[e];
					if (!inq[v]) {
						que.push(v), inq[v] = 1;
					}
				}
			}
			inq[u] = 0;
		}
		return dis[trg];
	}
	void Solve() {
		int srt = Spfa(), lng = 0;
		memcpy(dis0, dis, sizeof dis);
		for (int i = 0; i < m * 2; i++) {
			if (dis0[B[i]] != dis0[A[i]] + C[i]) continue;
			C[i] <<= 1;
			if (i < m) C[m + i] <<= 1;
			else C[i - m] <<= 1;
			lng = std::max(lng, Spfa());
			C[i] >>= 1;
			if (i < m) C[m + i] >>= 1;
			else C[i - m] >>= 1;
		}
		printf("%d\n", lng - srt);
	}
}
