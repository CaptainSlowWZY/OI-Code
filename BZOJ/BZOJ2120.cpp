#include <cstdio>
#include <cmath>
#include <algorithm>

const int kMaxn = 1e4 + 5, kMaxr = 1e3 + 5, kMaxc = 1e6 + 5;

int bl[kMaxn];

struct Query {
	int l, r, v, id;
	bool operator<(const Query & q) const {
		return bl[l] == bl[q.l] ?
			(bl[r] == bl[q.r] ? v < q.v : r < q.r) : 
			l < q.l;
	}
} Q[kMaxn];

int n, m, totq, totc, C[kMaxn], sum[kMaxc], ans[kMaxn];
int orgn[kMaxr], opos[kMaxr], ocol[kMaxr];
char IN[5];

inline void Vld(int p) {
	!(sum[C[p]]++) ? ++totc : 0;
}
inline void InVld(int p) {
	!(--sum[C[p]]) ? --totc : 0;
}

int main() {
	scanf("%d%d", &n, &m);
	int Unsz = pow(n, 2.0 / 3.0);
	for (int i = 1; i <= n; i++) {
		scanf("%d", C + i);
		bl[i] = (i - 1) / Unsz + 1;
	}
	int ver = 0;
	for (int i = 0; i < m; i++) {
		scanf("%s", IN);
		if (IN[0] == 'Q') {
			scanf("%d%d", &Q[totq].l, &Q[totq].r);
			Q[totq].id = totq, Q[totq++].v = ver;
		}
		else {
			++ver;
			scanf("%d%d", opos + ver, ocol + ver);
		}
	}

	std::sort(Q, Q + totq);
	int hd = 0, tl = 0;
	ver = 0;
	for (int i = 0; i < totq; i++) {
	//	printf(" Query %d [%d, %d] after %d\n", Q[i].id, Q[i].l, Q[i].r, Q[i].v);
		for (int p; ver < Q[i].v; ) {
			p = opos[++ver], orgn[ver] = C[p];
		//	printf("  Change %d's col from %d --> %d\n", p, C[p], ocol[ver]);
			if (hd <= opos[ver] && opos[ver] <= tl) {
			//	puts("   Valid");
				if (--sum[C[p]] == 0) --totc;
				if (sum[ocol[ver]]++ == 0) ++totc;
			}
			C[p] = ocol[ver];
		}
		for (int p; ver > Q[i].v; ) {
			p = opos[ver];
			if (hd <= opos[ver] && opos[ver] <= tl) {
				if (--sum[C[p]] == 0) --totc;
				if (sum[orgn[ver]]++ == 0) ++totc;
			}
			C[p] = orgn[ver--];
		}
		while (tl < Q[i].r) Vld(++tl);
		while (tl > Q[i].r) InVld(tl--);
		while (hd < Q[i].l) InVld(hd++);
		while (hd > Q[i].l) Vld(--hd);
		ans[Q[i].id] = totc;
	}

	for (int i = 0; i < totq; i++) printf("%d\n", ans[i]);
	return 0;
}
