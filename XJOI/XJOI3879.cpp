// XJOI 3879
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#include <cstdio>
#include <cstring>
#include <cctype>

#ifdef DEBUG_MD
	#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define debug(format, ...) 0
#endif

typedef long long LL;

const int TOTP = 4;
const int MD[] = {(int)1e9 + 7, 2333, 19260817, 19550701, /*(int)1e9 + 9, (int)1e8 + 7,*/ 100007377, 100000037, 19491001};
const int T1 = 1e9 + 7;
const int T2 = 2e9 + 7;

int N;
char buff[300];

struct Matrix {
	static const int MRSIZE = 55;
	int dat[MRSIZE][MRSIZE], r, c, mod;

	Matrix() : r(0), c(0) {
		memset(dat, 0, sizeof dat);
	}
	Matrix(int n_) : r(n_), c(n_) {
		memset(dat, 0, sizeof dat);
	}
	Matrix(int r_, int c_) : r(r_), c(c_) {
		memset(dat, 0, sizeof dat);
	}

	void resize(int r_, int c_) { r = r_; c = c_; }
	void resize(int n_) { r = c = n_; }
	void set_mod(int md_) { mod = md_; }
	void set_indentity();
	Matrix operator*(const Matrix & m) const;
	Matrix fast_pow(int ex) const;
	int sum() const {
		int ret = 0;
		for (int i = 1; i <= r; i++)
			for (int j = 1; j <= c; j++) (ret += dat[i][j]) %= mod;
		return ret;
	}

	void print() const {
		debug("This matrix is %d * %d, in mod %d\n", r, c, mod);
		for (int i = 1; i <= r; i++)
			for (int j = 1; j <= c; j++) debug("%d%c", dat[i][j], j == c ? '\n' : ' ');
#ifdef DEBUG_MD
		puts("-----  END  -----");
#endif
	}
} A, t[TOTP][2];

int read(char *&fir) {
	int x = 0;
	for (; *fir && !isdigit(*fir); ++fir);
	if (!(*fir)) return -1;
	for (; *fir && isdigit(*fir); x = (x << 3) + (x << 1) + (*fir ^ '0'), ++fir);
	return x;
}

int main() {
	scanf("%d", &N);
	getchar();
	A.resize(N);
	for (int i = 1; i <= N; i++) {
		fgets(buff, 300, stdin);
		int len = strlen(buff);
		buff[len-- - 1] = '\0';
		char *fir = buff;
		for (; fir != buff + len; ) {
			int tmp = read(fir);

			debug(" -> %d ", tmp);

			if (~tmp) ++A.dat[i][tmp];
			else break;
		}

#ifdef DEBUG_MD
		putchar('\n');
#endif

	}

	Matrix s(1, N);
	s.dat[1][1] = 1;
	int finf = 0;
	for (int i = 0; i < TOTP; i++) {
		debug(" in mod p_%d\n", i);
		t[i][0].set_mod(MD[i]), t[i][1].set_mod(MD[i]), A.set_mod(MD[i]), s.set_mod(MD[i]);

#ifdef DEBUG_MD
		s.print(), A.print();
#endif

		t[i][0] = s * A.fast_pow(T1);

		debug("  finish ^%d\n", T);

		t[i][1] = s * A.fast_pow(T2);

		debug("  finish ^%d\n", T2);

		if (t[i][0].sum() != t[i][1].sum()) {
			finf = 1;
			break;
		}
	}

	if (finf) puts("-1");
	else printf("%d\n", t[0][0].sum());
	
	return 0;
}

Matrix Matrix::operator*(const Matrix & m) const {
	if (c != m.r) return Matrix();
	Matrix ret(r, m.c);
	ret.set_mod(this->mod);
	for (int i = 1; i <= r; i++)
		for (int j = 1; j <= m.c; j++)
			for (int k = 1; k <= c; k++) (ret.dat[i][j] += (LL)dat[i][k] * m.dat[k][j] % mod) %= mod;
	return ret;
}

void Matrix::set_indentity() {
	if (r != c) return;
	memset(dat, 0, sizeof dat);
	for (int i = 1; i <= r; i++) dat[i][i] = 1;
}

Matrix Matrix::fast_pow(int ex) const {
	if (r != c) return Matrix();
	Matrix ret(r), bs = *this;
	ret.set_indentity();
	ret.set_mod(this->mod);
	for (; ex; bs = bs * bs, ex >>= 1) if (ex & 1) ret = ret * bs;
	return ret;
}
