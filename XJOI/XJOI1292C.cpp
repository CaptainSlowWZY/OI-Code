#include <algorithm>
#include <cctype>
#include <cstdio>
#include <vector>

#define fi first
#define se second
#define pb push_back
#define SZ(_) (int)_.size()
#define IN inline

typedef std::pair<int, int> Pii;

const int kMaxn = 5e5 + 5, kMod = 998244353;

IN int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
IN int Sub(int a, int b) { return (a -= b) < 0 ? a + kMod : a; }
IN int Mul(int a, int b) { return 1ll * a * b % kMod; }
IN void Upa(int & a, int b) { a = Add(a, b); }
IN void Ups(int & a, int b) { a = Sub(a, b); }
IN void Upm(int & a, int b) { a = Mul(a, b); }
int FPow(int bs, int ex = kMod - 2) {
	int res = 1;
	for (; ex; Upm(bs, bs), ex >>= 1) if (ex & 1) Upm(res, bs);
	return res;
}

int n, q;
char S[kMaxn << 1];

namespace solver1 { void Solve(); }

int main() {
	scanf("%d%d%s", &n, &q, S);
	solver1::Solve();
	return 0;
}

namespace solver1 {
	struct Info { int tp, prd, c0; } B[kMaxn];
	std::vector<int> expr;
	std::vector<Pii> num[kMaxn];
	int erra, cntb, ans, tot, R[kMaxn];

	void Solve() {
		int x = 0;
		for (int i = 0; S[i]; ++i) {
			if (isdigit(S[i])) x = (x << 3) + (x << 1) + (S[i] ^ '0');
			else {
				expr.pb(x);
				if (S[i] == '+') x = -1; if (S[i] == '-') x = -2;
				if (S[i] == '*') x = -3; if (S[i] == '/') x = -4;
				expr.pb(x); x = 0;
			}
		} expr.pb(x); B[0] = (Info){1, 1, 0};
	/*	for (int i = 0; i < SZ(expr); ++i) {
			if (expr[i] >= 0) printf("%d", expr[i]);
			else {
				if (expr[i] == -1) putchar('+');
				if (expr[i] == -2) putchar('-');
				if (expr[i] == -3) putchar('*');
				if (expr[i] == -4) putchar('/');
			}
		} putchar('\n');
		return; */
	//	for (int i = 0; i < SZ(expr); ++i) printf("%d ", expr[i]);
	//	puts("");
/*		{
			int a = 1, m = 1, x = 1, sum = 0;
			for (int i = 0; i < SZ(expr); ++i) {	
				if (expr[i] >= 0) {
					if (m) Upm(x, expr[i]); else Upm(x, FPow(expr[i]));
				} else if (expr[i] > -3) {
					if (a) Upa(sum, x); else Ups(sum, x);
					a = expr[i] == -1, x = 1, m = 1;
				} else m = expr[i] == -3;
			} if (a) Upa(sum, x); else Ups(sum, x);
			printf(" ans_correct = %d\n", sum);
		} */
		for (int i = 0, flm = 1; i < SZ(expr); ++i) {	
			if (expr[i] >= 0) {
				++tot, num[cntb].pb(Pii(expr[i], flm));
				if (flm) {
					if (expr[i]) Upm(B[cntb].prd, expr[i]);
					else ++B[cntb].c0;
				} else if (expr[i]) Upm(B[cntb].prd, FPow(expr[i])); else ++erra;
			} else if (expr[i] > -3) {
				R[cntb] = tot, flm = 1;
			//	printf(" block%d sign %d\n", cntb + 1, expr[i]);
				B[++cntb] = (Info){expr[i] == -1, 1, 0};
			} else flm = expr[i] == -3;
		} R[cntb++] = tot, ans = 0;
		for (int i = 0; i < cntb; ++i) {
		//	printf("_block %c %d, cnt0 = %d\n", B[i].tp ? '+' : '-', B[i].prd, B[i].c0);
			if (B[i].c0) continue;
			if (B[i].tp) Upa(ans, B[i].prd); else Ups(ans, B[i].prd);
		}
//		printf(" ans = %d\n", ans);
	//	printf("tot block %d\n", cntb);
		for (int c0, x, y, k, err, res, reb; q--; ) {
			scanf("%d%d", &x, &y);
		//	printf(" change %d --> %d\n", x, y);
			k = std::lower_bound(R, R + cntb, x) - R;
/*			printf(" R[%d] = %d\n", k, R[k]);
			printf(" k = %d, id = %d, SZ = %d\n", k, SZ(num[k]) - 1 - (R[k] - x), SZ(num[k]));*/
			Pii cur = num[k][SZ(num[k]) - (R[k] - x) - 1];
			err = erra - (!cur.fi && !cur.se) + (!y && !cur.se);
			if (err) { puts("Invalid"); continue; }
			res = ans, reb = B[k].c0 ? 0 : B[k].prd, c0 = B[k].c0 - (!cur.fi && cur.se);
//			printf("  at block %d (%d, %d, %d)\n", k, B[k].tp, B[k].prd, B[k].c0);
			if (B[k].tp) Ups(res, reb); else Upa(res, reb);
/*			printf(" res = %d\n", res);
			for (int i = 0; i < SZ(num[k]); ++i)
				printf("   id %d: %c%d\n", i, num[k][i].se ? '*' : '/', num[k][i].fi);
			printf("  cur %c%d\n", cur.se ? '*' : '/', cur.fi);*/
			if (c0) reb = 0;
			else {
				reb = B[k].prd;
				if (cur.fi) Upm(reb, cur.se ? FPow(cur.fi) : cur.fi);
				Upm(reb, cur.se ? y : FPow(y));
//				printf(" reb = %d\n", reb);
			} printf("%d\n", B[k].tp ? Add(res, reb) : Sub(res, reb));
		}
	}
}
