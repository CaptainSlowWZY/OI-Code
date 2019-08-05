#include <algorithm>
#include <cstdio>
#include <vector>

#ifdef DEBUG
	#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define debug(format, ...) 0
#endif
#define pb push_back

const int kMaxp = 6e4 + 10;

struct Point {
	int x[4], val, id, tag;
	int & operator[](int y) { return x[y]; }
	bool operator<(const Point & p) const {
		return x[0] == p.x[0] ? id < p.id : x[0] < p.x[0];
	}
	void Debug() {
		printf(" (");
		for (int i = 0; i < 4; i++) printf("%d ", x[i]);
		printf(") val %d, id %d, tag %d\n", val, id, tag);
	}
} P[kMaxp];

int n, m, max1;
int ans[kMaxp >> 1];
double P0[kMaxp][4];
std::vector<double> cor[4];

void Solve1(int, int);

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 4; j++) {
			scanf("%lf", &P0[i][j]);
			cor[j].pb(P0[i][j]);
		}
	} scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < 4; j++) {
			scanf("%lf", &P0[n + i][j]);
			cor[j].pb(P0[n + i][j]);
		}
	}
	for (int j = 0; j < 4; j++) {
		auto & v = cor[j];
		std::sort(v.begin(), v.end());
		v.erase(std::unique(v.begin(), v.end()), v.end());
		for (int i = 0; i < n + m; i++) {
			P[i][j] = std::lower_bound(v.begin(), v.end(),
					P0[i][j]) - v.begin() + 1;
		}
	}
	max1 = cor[3].size();
	for (int i = 0; i < n; i++) {
		P[i].val = 1, P[i].id = 0;
	}
	for (int i = 0; i < m; i++) {
		P[n + i].val = 0, P[n + i].id = i + 1;
	}
#ifdef DEBUG
	for (int i = 0; i < n + m; i++) {
		printf(" (%d, %d, %d, %d), val %d, id %d\n",
				P[i][0], P[i][1], P[i][2], P[i][3], P[i].val, P[i].id);
	}
#endif
	std::sort(P, P + n + m);
	Solve1(0, n + m);
	for (int i = 1; i <= m; i++) printf("%d\n", ans[i]);
	return 0;
}

namespace bit {
	int T[kMaxp];
	void Add(int p, int d) {
		if (!d) return;
		for (; p <= max1; p += p & -p) T[p] += d;
	}
	int Query(int p) {
		int res = 0;
		for (; p; p &= p - 1) res += T[p];
		return res;
	}
}

Point P2[kMaxp];

void Solve2(int l, int r) {
	if (r - l <= 1) return;
	int mid = l + r >> 1;
	Solve2(l, mid); Solve2(mid, r);
#ifdef DEBUG
	debug("    #Solve2[%d, %d)\n", l, r);
	for (int t = l; t < r; t++) {
		debug("     P[%2d]:", t);
		P2[t].Debug();
	}
#endif
	int i = l, j = mid, k = l;
	static Point buf[kMaxp];
	while (i < mid && j < r) {
		if (P2[i][2] <= P2[j][2]) {
			if (!P2[i].tag) {
				bit::Add(P2[i][3], P2[i].val);
				debug("      add (%d)-> pos %d\n", P2[i].val, P2[i][3]);
			}
			buf[k++] = P2[i++];
		} else {
			if (P2[j].tag) {
				ans[P2[j].id] += bit::Query(P2[j][3]);
				debug("      query(%d) + %d -> %d\n", P2[j][3], bit::Query(P2[j][3]), P2[j].id);
			}
			buf[k++] = P2[j++];
		}
	}
	while (j < r) {
		if (P2[j].tag) {
			ans[P2[j].id] += bit::Query(P2[j][3]);
			debug("      query(%d) + %d -> %d\n", P2[j][3], bit::Query(P2[j][3]), P2[j].id);
		}
		buf[k++] = P2[j++];
	}
	for (int t = l; t < i; t++) {
		if (!P2[t].tag) {
			bit::Add(P2[t][3], -P2[t].val);
			debug("      add (%d)-> pos %d\n", P2[t].val, P2[t][3]);
		}
	}
	while (i < mid) buf[k++] = P2[i++];
	for (i = l; i < r; i++) P2[i] = buf[i];
}

void Solve1(int l, int r) {
	if (r - l <= 1) return;
	int mid = l + r >> 1;
	Solve1(l, mid); Solve1(mid, r);
#ifdef DEBUG
	debug(" #Solve1[%d, %d)\n", l, r);
	for (int t = l; t < r; t++) {
		debug("  P[%2d]:", t);
		P[t].Debug();
	}
#endif
	int i = l, j = mid, k = l;
	while (i < mid && j < r) {
		if (P[i][1] <= P[j][1]) {
			P[i].tag = 0, P2[k++] = P[i++];
		} else {
			P[j].tag = 1, P2[k++] = P[j++];
		}
	}
	while (i < mid) { P[i].tag = 0, P2[k++] = P[i++]; }
	while (j < r) { P[j].tag = 1, P2[k++] = P[j++]; }
	for (i = l; i < r; i++) P[i] = P2[i];
	Solve2(l, r);
}
