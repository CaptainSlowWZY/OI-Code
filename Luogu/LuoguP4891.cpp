#pragma GCC optimize(2, "Ofast")
#include <cstdio>
#include <cmath>
#include <cctype>
#include <algorithm>

namespace fast_io {
	template <typename T>
		void Read(T & x) {
			register char ch = getchar();
			register bool f = false; x = 0;
			for (; !isdigit(ch); f |= (ch == '-'), ch = getchar());
			for (; isdigit(ch); ch = getchar())
				x = (x << 3) + (x << 1) + (ch ^ '0');
			f ? x = -x : 0;
		}
	template <typename T>
		void Print(T x) {
			if (!x) return (void)(putchar('0'));
			if (x < 0) x = -x, putchar('-');
			register int arr[20], len = 0;
			for (; x; arr[len++] = x % 10, x /= 10);
			while (len) putchar(arr[--len] ^ '0');
		}
	template <>
		void Print(const char * buff) {
			for (register int i = 0; buff[i]; ++i) putchar(buff[i]);
		}
	template <typename T>
		inline void Println(T x) {
			Print(x), putchar('\n');
		}
}

typedef long long LL;

const int kBlsz = 500, kBlc = 205, kMaxn = 1e5 + 10, MOD = 1e9 + 7;

int n, q, totbl, res = 1;
int bl[kMaxn], C[kMaxn], B[kMaxn];
int max[kBlc], ans[kBlc], tag[kBlc];
int sor[kBlc][kBlsz + 10], prd[kBlc][kBlsz + 10];

template <typename T> inline
void Mult(T & x, LL y) {
	x = x * y % MOD;
}
void Rebuild(int id);
void Cover(int id, int val);

int main() {
	using fast_io::Read;
	
	Read(n), Read(q);
	for (int i = 1, ai, cur; i <= n; i++) {
		Read(ai);
		cur = bl[i] = (i - 1) / kBlsz + 1;
		C[i] = std::max(C[i - 1], ai);
		max[cur] = C[i], ans[cur] = 1;
	}
	totbl = bl[n];
	for (int i = 1, cur; i <= n; i++) {
		Read(B[i]);
		cur = bl[i];
		sor[cur][++sor[cur][0]] = B[i];
		Mult(ans[cur], std::min(C[i], B[i]));
	}
	for (int i = 1, size; i <= totbl; i++) {
		size = sor[i][0];
		std::sort(sor[i] + 1, sor[i] + 1 + size);
		prd[i][0] = 1;
		for (int j = 1; j <= size; j++) {
			prd[i][j] = (LL)prd[i][j - 1] * sor[i][j] % MOD;
		}
		Mult(res, ans[i]);
	}
	res = (res + MOD) % MOD;

	for (int tp, x, y; q--; ) {
		Read(tp), Read(x), Read(y);
		if (tp) {
			B[x] = y;
			Rebuild(bl[x]);
		} else {
			if (y < C[x]) {
				fast_io::Println(res);
				continue;
			}
			C[x] = y;
			Rebuild(bl[x]);
			int cur = bl[x] + 1;
			for (; cur <= totbl && max[cur] < y; ++cur) {
				Cover(cur, y);
			}
			if (cur <= totbl) Rebuild(cur);
		}
		fast_io::Println(res);
	}
	return 0;
}

LL FPow(LL bs, int ex = MOD - 2) {
	LL ret = 1;
	for (; ex; Mult(bs, bs), ex >>= 1)
		if (ex & 1) Mult(ret, bs);
	return ret;
}

void Rebuild(int id) {
	tag[id] = std::max(tag[id], max[id - 1]);
	int l = (id - 1) * kBlsz + 1;
	res = res * FPow(ans[id]) % MOD;
	ans[id] = 1;
	for (int i = l; i < l + sor[id][0]; i++) {
		sor[id][i - l + 1] = B[i];
		C[i] = std::max(std::max(C[i - 1], C[i]), tag[id]);
		Mult(ans[id], std::min(B[i], C[i]));
	}
	res = (LL)res * ans[id] % MOD;
	res = (res + MOD) % MOD;
	max[id] = C[l + sor[id][0] - 1];
	std::sort(sor[id] + 1, sor[id] + 1 + sor[id][0]);
	for (int i = 1; i <= sor[id][0]; i++) {
		prd[id][i] = (LL)prd[id][i - 1] * sor[id][i] % MOD;
	}
}

void Cover(int id, int val) {
	max[id] = tag[id] = val;
	int p = std::upper_bound(sor[id] + 1, sor[id] + 1 + sor[id][0], val)
			- sor[id];
	res = res * FPow(ans[id]) % MOD;
	ans[id] = (LL)prd[id][p - 1] * FPow(val, sor[id][0] - p + 1) % MOD;
	res = (LL)res * ans[id] % MOD;
	res = (res + MOD) % MOD;
}
