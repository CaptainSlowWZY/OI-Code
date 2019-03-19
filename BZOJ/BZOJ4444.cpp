#include <cstdio>
#include <algorithm>

const int kMaxn = 2e5 + 5, kLgN = 20;

struct Segment {
	int l, r, id;
	bool operator<(const Segment & s) const {
		return l < s.l;
	}
} seg[kMaxn << 1];

int n, m;
int next[kMaxn << 1][kLgN], ans[kMaxn], R[kMaxn];

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		Segment & cur = seg[i];
		cur.id = i;
		scanf("%d%d", &cur.l, &cur.r);
		if (cur.l > cur.r) cur.r += m;
		seg[i + n] = (Segment){cur.l + m, cur.r + m, 0};
	}

	std::sort(seg + 1, seg + 1 + n + n);
	for (int i = 1, l, r; i <= n + n; i++) {
		l = i, r = n + n + 1;
		for (int mid; r - l > 1; ) {
			mid = l + r >> 1;
			if (seg[mid].l <= seg[i].r) l = mid;
			else r = mid;
		}
		next[i][0] = l;
	//	printf(" next %d (seg [%d, %d]) %d\n",
	//			i, seg[i].l, seg[i].r, l);
	}
	for (int i = 1; i < kLgN; i++) {
		for (int j = 1; j <= n + n; j++) {
			next[j][i] = next[next[j][i - 1]][i - 1];
		}
	}

	for (int i = 1; i <= n; i++) {
		int & ret = ans[seg[i].id], u = i;
	//	printf(" id = %d right = %d\n", seg[i].id, seg[i].l + m);
		for (int j = kLgN - 1; j >= 0; j--) {
			if (!next[u][j]) continue;
		//	printf(" R_seg[next[%d][%d] = %d] %d\n",
		//			u, j, next[u][j], seg[next[u][j]].r);
			if (seg[next[u][j]].r < seg[i].l + m) {
				ret |= 1 << j;
				u = next[u][j];
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		printf("%d%c", ans[i] + 2, i == n ? '\n' : ' ');
	}
	return 0;
}
