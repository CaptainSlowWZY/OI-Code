#include <cstdio>

const int kMaxn = 7e4 + 5, kInf = 0x3f3f3f3f;

struct Oper {
	int l, r, val, id;
} O[kMaxn];

int n, m, toto, totq;
int last[kMaxn], ans[kMaxn];
char IN[5];

void Solve(int ql, int qr, int vl, int vr);

int main() {
	int t;
	for (scanf("%d", &t); t--; ) {
		scanf("%d%d", &n, &m);
		toto = totq = 0;
		for (int i = 1, ai; i <= n; i++) {
			scanf("%d", &ai);
			O[toto++] = (Oper){i, -1, ai, 0};
			last[i] = ai;
		}
		for (int i = 0, l, r, k; i < m; i++) {
			scanf("%s", IN);
			if (IN[0] == 'Q') {
				scanf("%d%d%d", &l, &r, &k);
				O[toto++] = (Oper){l, r, k, totq++};
			}
			else {
				scanf("%d%d", &l, &k);
				O[toto++] = (Oper){l, -2, last[l], 0};
				O[toto++] = (Oper){l, -1, last[l] = k, 0};
			}
		}

		Solve(0, toto, -kInf, kInf);

		for (int i = 0; i < totq; i++) {
			printf("%d\n", ans[i]);
		}
	}

	return 0;
}

namespace bit {
	int T[kMaxn];

	void Add(int p, int d) {
		for (; p <= n; p += p & -p) {
			T[p] += d;
		}
	}
	int Sum(int p) {
		int ret = 0;
		for (; p; p &= p - 1) {
			ret += T[p];
		}
		return ret;
	}
}

void Solve(int ql, int qr, int vl, int vr) {
	if (ql >= qr) return;
	if (vl == vr) {
		for (int i = ql; i < qr; i++) {
			if (O[i].r > 0) {
				ans[O[i].id] = vl;
			}
		}
		return;
	}
	int mid = vl + vr >> 1, b1 = 0, b2 = 0;
	static Oper fr[kMaxn], sc[kMaxn];
	for (int i = ql, cnt; i < qr; i++) {
		using namespace bit;
		if (O[i].r < 0) {
			if (O[i].val <= mid) {
				Add(O[i].l, ~O[i].r ? -1 : 1);
				fr[b1++] = O[i];
			}
			else {
				sc[b2++] = O[i];
			}
		}
		else {
			cnt = Sum(O[i].r) - Sum(O[i].l - 1);
			if (cnt >= O[i].val) {
				fr[b1++] = O[i];
			}
			else {
				O[i].val -= cnt;
				sc[b2++] = O[i];
			}
		}
	}

	for (int i = 0; i < b1; i++) {
		if (fr[i].r > 0) continue;
		if (fr[i].val <= mid) {
			bit::Add(fr[i].l, ~fr[i].r ? 1 : -1);
		}
	}
	for (int i = 0; i < b1; i++) {
		O[ql + i] = fr[i];
	}
	for (int i = 0; i < b2; i++) {
		O[ql + b1 + i] = sc[i];
	}

	Solve(ql, ql + b1, vl, mid);
	Solve(ql + b1, qr, mid + 1, vr);
}
