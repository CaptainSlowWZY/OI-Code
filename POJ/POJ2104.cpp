#include <cstdio>

const int kMaxn = 1e5 + 10, kInf = 0x3f3f3f3f;

struct Query {
	int l, r, val, id;
} Q[kMaxn + 5000];

int n, m, totq, ans[5005];

void Solve(int ql, int qr, int vl, int vr);

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1, ai; i <= n; i++) {
		scanf("%d", &ai);
		Q[totq++] = (Query){i, -1, ai, 0};
	}
	for (int i = 0, l, r, k; i < m; i++) {
		scanf("%d%d%d", &l, &r, &k);
		Q[totq++] = (Query){l, r, k, i};
	}

	Solve(0, totq, -kInf, kInf);

	for (int i = 0; i < m; i++) printf("%d\n", ans[i]);
	return 0;
}

namespace bit {
	int T[kMaxn];

	void Add(int p, int del = 1) {
		for (; p <= n; p += p & -p) {
			T[p] += del;
		}
	}
	int Query(int p) {
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
			if (~Q[i].r) {
				ans[Q[i].id] = vl;
			}
		}
		return;
	}
	int vm = vl + vr >> 1, b1 = 0, b2 = 0;
	static Query fr[kMaxn + 5000], sc[kMaxn + 5000];
	for (int i = ql, cnt; i < qr; i++) {
		if (~Q[i].r) {
			cnt = bit::Query(Q[i].r) - bit::Query(Q[i].l - 1);
			if (cnt >= Q[i].val) {
				fr[b1++] = Q[i];
			}
			else {
				Q[i].val -= cnt;
				sc[b2++] = Q[i];
			}
		}
		else {
			if (Q[i].val <= vm) {
				bit::Add(Q[i].l);
				fr[b1++] = Q[i];
			}
			else {
				sc[b2++] = Q[i];
			}
		}
	}

	for (int i = 0; i < b1; i++) {
		if (fr[i].r == -1) {
			bit::Add(fr[i].l, -1);
		}
		Q[ql + i] = fr[i];
	}
	for (int i = 0; i < b2; i++) {
		Q[ql + b1 + i] = sc[i];
	}

	Solve(ql, ql + b1, vl, vm);
	Solve(ql + b1, qr, vm + 1, vr);
}
