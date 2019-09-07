#include <algorithm>
#include <cstdio>

const int kLen = 1e6 + 5, kMod = 1e9 + 7;

char N[kLen];
int m, len, val[kLen], sum[kLen];

inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + kMod : a; }

namespace smt {
	struct Node {
		int sum, cnt, tag;
	} T[kLen << 1];

	inline int Id(int l, int r) { return l + r | l != r; }
	void Build(int l, int r);
	void Turn(int l, int r, int ql, int qr);
}

int main() {
	scanf("%s%d", N, &m);
	while (N[len]) N[len++] ^= '0';
	val[1] = 0, val[2] = 1;
	for (int i = 3; i <= len; i++)
		val[i] = (val[i - 1] << 1) % kMod;
	std::reverse(val + 1, val + len + 1);
	for (int i = 1; i <= len; i++)
		sum[i] = (sum[i - 1] + val[i]) % kMod;
	using namespace smt;
	Build(1, len);
	printf("%d\n", Add(T[Id(1, len)].sum,
		N[len - 1] ? 1 : T[Id(1, len)].cnt ^ 1));
	for (int i = 0, l, r; i < m; i++) {
		scanf("%d%d", &l, &r);
		if (l > r) std::swap(l, r);
		if (r == len) N[len - 1] ^= 1;
		Turn(1, len, l, r);
	//	printf(" last = %d, even ? %d, sum ? %d\n",
	//			N[len - 1], T[Id(1, len)].cnt ^ 1, T[Id(1, len)].sum);
		printf("%d\n", Add(T[Id(1, len)].sum,
					N[len - 1] ? 1 : T[Id(1, len)].cnt ^ 1));
	} return 0;
}

namespace smt {
#define LSON Id(l, mid)
#define RSON Id(mid + 1, r)
	void Build(int l, int r) {
		int cur = Id(l, r);
		if (l == r) {
			T[cur] = (Node){N[l - 1] * val[l], N[l - 1], 0};
			return;
		} int mid = l + r >> 1;
		Build(l, mid); Build(mid + 1, r);
		T[cur].sum = Add(T[LSON].sum, T[RSON].sum);
		T[cur].cnt = T[LSON].cnt ^ T[RSON].cnt;
	}
	void Reverse(int l, int r) {
		int cur = Id(l, r);
		T[cur].sum = Sub(Sub(sum[r], sum[l - 1]), T[cur].sum);
		T[cur].cnt = (r - l + 1 & 1) ^ T[cur].cnt;
		T[cur].tag ^= 1;
	}
	void PushDown(int l, int mid, int r) {
		int u = Id(l, r);
		if (!T[u].tag) return;
		Reverse(l, mid); Reverse(mid + 1, r);
		T[u].tag = 0;
	}
	void Turn(int l, int r, int ql, int qr) {
		int cur = Id(l, r);
		if (ql <= l && r <= qr) return Reverse(l, r);
		int mid = l + r >> 1; PushDown(l, mid, r);
		if (ql <= mid) Turn(l, mid, ql, qr);
		if (qr > mid) Turn(mid + 1, r, ql, qr);
		T[cur].sum = Add(T[LSON].sum, T[RSON].sum);
		T[cur].cnt = T[LSON].cnt ^ T[RSON].cnt;
	}
}
