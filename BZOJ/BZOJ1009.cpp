// BZOJ 1009
#include <cstdio>
#include <cstring>

const int MAXM = 22;

int N, M, MOD, fail[MAXM], T[MAXM];
char T0[MAXM];

struct Matrix {
	int r, c, dat[MAXM][MAXM];
	Matrix(int r_ = 1, int c_ = 1) : r(r_), c(c_) {
		memset(dat, 0, sizeof dat);
	}
	void resize(int r_, int c_) { r = r_; c = c_; }
	void operator*=(const Matrix & m);
	Matrix fast_pow(int ex);
} mans, TM;

inline void add(int & x, int y) { (x += y) >= MOD ? x -= MOD : 0; }

int main() {
	scanf("%d%d%d%s", &N, &M, &MOD, T0);
	
	for (int i = 0; i < M; i++) T[i] = T0[i] ^ '0';
	// init fail
	for (int i = 1, j; i < M; i++) {
		for (j = fail[i]; j && T[j] ^ T[i]; j = fail[j]);
		fail[i + 1] = T[i] == T[j] ? j + 1 : 0;
	}
	// init transport-matrix
	TM.resize(M, M);
	for (int i = 0; i < M; i++)
		for (int j = 0, k; j <= 9; j++) {
			for (k = i; k && j ^ T[k]; k = fail[k]);
			T[k] == j ? ++k : 0;
			if (k < M) (++TM.dat[i][k]) %= MOD;
		}
/*	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) printf("%4d", TM.dat[i][j]);
		putchar('\n');
	}*/
	mans.resize(1, M);
	mans.dat[0][0] = 1;
	TM = TM.fast_pow(N);
	mans *= TM; 
	int ans = 0;
	for (int i = 0; i < M; i++) add(ans, mans.dat[0][i]);
	
	printf("%d\n", ans);
	return 0;
}

void Matrix::operator*=(const Matrix & m) {
	Matrix ret(r, c);
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			for (int k = 0; k < c; k++)
				add(ret.dat[i][j], dat[i][k] * m.dat[k][j] % MOD);
	*this = ret;
}

Matrix Matrix::fast_pow(int ex) {
	Matrix ret(r, c), bs = *this;
	for (int i = 0; i < r; i++) ret.dat[i][i] = 1;
	for (; ex; bs *= bs, ex >>= 1)
		if (ex & 1) ret *= bs;
	return ret;
}
