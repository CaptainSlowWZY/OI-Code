#include <bits/stdc++.h>

const int MAXN = 4e5 + 10;
const int MOD = 1e9 + 7;

typedef long long LL;

int N, Q, totp, A[MAXN], D[64], P[64], flag[305];
LL C[MAXN];

namespace T1 {
	int QL, QR;
	LL X;

	LL build(int l, int r);
	LL _Q(int l, int r);
	inline LL query(int l, int r) {
		QL = l, QR = r;
		return _Q(1, N);
	}
	LL _UPD(int l, int r);
	inline void update(int l, int r, LL x) {
		QL = l, QR = r, X = x;
		_UPD(1, N);
	}
}
namespace T2 {
	int QL, QR;
	LL DELTA;

	LL build(int l, int r);
	LL _Q(int l, int r);
	inline LL query(int l, int r) {
		QL = l, QR = r;
		return _Q(1, N);
	}
	LL _UPD(int l, int r);
	inline void update(int l, int r, LL d) {
		QL = l, QR = r, DELTA = d;
		_UPD(1, N);
	}
}
void init();

int main() {
	init();
	scanf("%d%d", &N, &Q);
	for (int i = 1; i <= N; i++) {
		scanf("%d", A + i);		
		for (int j = 0; j < totp; j++)
			if (A[i] % P[j] == 0) C[i] |= 1LL << j;
	}

	T1::build(1, N);
	T2::build(1, N);
	char IN[20];
	for (int l, r, x; Q--; ) {
		scanf("%s", IN);
		if (IN[0] == 'M') {
			scanf("%d%d%d", &l, &r, &x);
			T1::update(l, r, x);
			LL y = 0;
			for (int j = 0; j < totp; j++)
				if (x % P[j] == 0) y |= 1LL << j;
			T2::update(l, r, y);
		}
		else {
			scanf("%d%d", &l, &r);
			LL x1 = T1::query(l, r), x2 = T2::query(l, r);
			for (int j = 0; j < totp; j++)
				if (x2 >> j & 1) (x1 *= D[j]) %= MOD;
			printf("%lld\n", x1);
		}
	}
	return 0;
}

LL fast_pow(LL bs, int ex = MOD - 2) {
	LL ret = 1;
	for (; ex; (bs *= bs) %= MOD, ex >>= 1)
		if (ex & 1) (ret *= bs) %= MOD;
	return ret;
}

namespace T1 {
	struct Node {
		LL prd, tag;
	} T[MAXN << 1];

	inline int id(int l, int r) {
		return l + r | l != r;
	}
	LL build(int l, int r) {
		int cur = id(l, r);
		T[cur].tag = 1;
		if (l == r) {
			return T[cur].prd = A[l] % MOD;
		}
		int mid = l + r >> 1;
		return T[cur].prd = build(l, mid) * build(mid + 1, r) % MOD;
	}
	void push_down(int l, int r) {
		int cur = id(l, r);
		if (T[cur].tag > 1) {
			int mid = l + r >> 1, ls = id(l, mid), rs = id(mid + 1, r);
			(T[ls].prd *= fast_pow(T[cur].tag, mid - l + 1)) %= MOD;
			(T[ls].tag *= T[cur].tag) %= MOD;
			(T[rs].prd *= fast_pow(T[cur].tag, r - mid)) %= MOD;
			(T[rs].tag *= T[cur].tag) %= MOD;
			T[cur].tag = 1;
		}
	}		
	LL _Q(int l, int r) {
		if (QR < l || QL > r) return 1;
		int cur = id(l, r);
		if (QL <= l && r <= QR) return T[cur].prd;
		push_down(l, r);
		int mid = l + r >> 1;
		return _Q(l, mid) * _Q(mid + 1, r) % MOD;
	}
	LL _UPD(int l, int r) {
		int cur = id(l, r);
		if (QR < l || QL > r) return T[cur].prd;
		if (QL <= l && r <= QR) {
			(T[cur].tag *= X) %= MOD;
			return (T[cur].prd *= fast_pow(X, r - l + 1)) %= MOD;
		}
		push_down(l, r);
		int mid = l + r >> 1;
		return T[cur].prd = _UPD(l, mid) * _UPD(mid + 1, r) % MOD;
	}
}

namespace T2 {
	struct Node {
		LL val, tag;
	} T[MAXN << 1];

	inline int id(int l, int r) {
		return l + r | l != r;
	}
	LL build(int l, int r) {
		int cur = id(l, r);
		T[cur].tag = 0;
		if (l == r) {
			return T[cur].val = C[l];
		}
		int mid = l + r >> 1;
		return T[cur].val = build(l, mid) | build(mid + 1, r);
	}
	void push_down(int l, int r) {
		int cur = id(l, r);
		if (T[cur].tag) {
			int mid = l + r >> 1, ls = id(l, mid), rs = id(mid + 1, r);
			T[ls].val |= T[cur].tag, T[ls].tag |= T[cur].tag;
			T[rs].val |= T[cur].tag, T[rs].tag |= T[cur].tag;
			T[cur].tag = 0;
		}
	}	
	LL _Q(int l, int r) {
		if (QR < l || QL > r) return 0;
		int cur = id(l, r);
		if (QL <= l && r <= QR) return T[cur].val;
		push_down(l, r);
		int mid = l + r >> 1;
		return _Q(l, mid) | _Q(mid + 1, r);
	}
	LL _UPD(int l, int r) {
		int cur = id(l, r);
		if (QR < l || QL > r) return T[cur].val;
		if (QL <= l && r <= QR) {
			T[cur].tag |= DELTA;
			return T[cur].val |= DELTA;
		}
		push_down(l, r);
		int mid = l + r >> 1;
		return T[cur].val = _UPD(l, mid) | _UPD(mid + 1, r);
	}
}

void init() {
	for (int i = 2; i <= 300; i++) {
		if (!flag[i]) P[totp++] = i;
		for (int j = 0; j < totp && i * P[j] <= 300; j++) {
			flag[i * P[j]] = 1;
			if (i % P[j] == 0) break;
		}
	}
	for (int i = 0; i < totp; i++) D[i] = LL(P[i] - 1) * fast_pow(P[i]) % MOD;
}
