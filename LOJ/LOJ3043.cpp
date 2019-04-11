// ZJOI 2019
#include <cstdio>

#ifdef DEBUG
	#define db(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define db(format, ...) 0
#endif

const int kMaxn = 1e5 + 10, MOD = 998244353;

typedef long long LL;

namespace smt {
	const LL & Modify(int l, int r, int ql, int qr, LL & pow2);
}
template <typename T> inline
void Add(T & x, LL y) { (x += y) >= MOD ? x -= MOD : 0; }
template <typename T> inline
void Mul(T & x, LL y) { (x *= y) %= MOD; }

int n, m;

int main() {
	scanf("%d%d", &n, &m);

	LL pow2 = 1, ans = 0;
	for (int op, l, r; m--; ) {
		scanf("%d", &op);
		if (op == 1) {
			scanf("%d%d", &l, &r);
			db("*** modify [%d, %d]\n", l, r);
			ans = smt::Modify(1, n, l, r, pow2);
			Mul(pow2, 2);
		} else {
			db("*** query%c", '\n');
			printf("%lld\n", ans);
		}
	}
	
	return 0;
}

namespace smt {
	struct Node {
		LL sum, cnt, f;	// values
		LL cmul;	// tag for cnt
		LL fmul, fadd;	// tag for f
		Node() { cmul = fmul = 1; }
		void debug() const {
			db("### DEBUG for Node%c", '\n');
			db("    sum %10lld, cnt %10lld, f %10lld\n", sum, cnt, f);
			db("    cmul %10lld\n", cmul);
			db("    fmul %10lld, fadd %10lld\n", fmul, fadd);
		}
	} T[kMaxn << 1];

	inline int Id(int l, int r) { return l + r | l != r; }
	void PushDown(int l, int r) {
		int rt = Id(l, r), mid = l + r >> 1, 
			ls = Id(l, mid), rs = Id(mid + 1, r);
		db(" push_down [%d, %d]\n", l, r);
	//	T[rt].debug();
		if (T[rt].cmul != 1) {
			Mul(T[ls].cnt, T[rt].cmul);
			Mul(T[ls].sum, T[rt].cmul);
			Mul(T[ls].cmul, T[rt].cmul);
			Mul(T[rs].cnt, T[rt].cmul);
			Mul(T[rs].sum, T[rt].cmul);
			Mul(T[rs].cmul, T[rt].cmul);
			T[rt].cmul = 1;
		}
		if (T[rt].fmul != 1) {
			Mul(T[ls].f, T[rt].fmul);
			Mul(T[ls].fmul, T[rt].fmul), Mul(T[ls].fadd, T[rt].fmul);
			Mul(T[rs].f, T[rt].fmul);
			Mul(T[rs].fmul, T[rt].fmul), Mul(T[rs].fadd, T[rt].fmul);
			T[rt].fmul = 1;
		}
		if (T[rt].fadd) {
			Add(T[ls].f, T[rt].fadd), Add(T[ls].fadd, T[rt].fadd);
			Add(T[rs].f, T[rt].fadd), Add(T[rs].fadd, T[rt].fadd);
			T[rt].fadd = 0;
		}
	}
	const LL & Modify(int l, int r, int ql, int qr, LL & pow2) {
		int rt = Id(l, r);
		db(" modify [%d, %d], [ql %d, qr %d], pow2 %lld\n",
				l, r, ql, qr, pow2);
		if (r < ql || qr < l) {
			db("   [l, r] & [ql, qr] = none%c", '\n');
			T[rt].sum = (T[rt].sum - T[rt].cnt) * 2 % MOD;
			Add(T[rt].sum, MOD), Mul(T[rt].cmul, 2);
			Add(T[rt].cnt, T[rt].f), Add(T[rt].sum, T[rt].cnt);
			Mul(T[rt].f, 2), Mul(T[rt].fmul, 2), Mul(T[rt].fadd, 2);
		//	T[rt].debug();
			return T[rt].sum;
		}
		if (ql <= l && r <= qr) {
			db("   [l, r] in [ql, qr] %c", '\n');
			Add(T[rt].f, pow2), Add(T[rt].fadd, pow2);
			Mul(T[rt].cmul, 2);
			T[rt].sum = (T[rt].sum - T[rt].cnt) * 2 % MOD;
			Add(T[rt].sum, MOD);
			Add(T[rt].cnt, pow2), Add(T[rt].sum, T[rt].cnt);
		//	T[rt].debug();
			return T[rt].sum;
		}
		PushDown(l, r);
		int mid = l + r >> 1;
		return T[rt].sum = (T[rt].cnt + Modify(l, mid, ql, qr, pow2) +
							Modify(mid + 1, r, ql, qr, pow2)) % MOD;
	}
}
