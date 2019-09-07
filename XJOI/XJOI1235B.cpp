#include <cassert>
#include <cstdio>
#include <cstring>

const int kMod = 1e9 + 7;

inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline int Mul(int a, int b) { return 1ll * a * b % kMod; }
inline void Adds(int & a, int b) { (a += b) >= kMod ? a -= kMod : 0; }

struct Matrix {
	int r, c, a[125][125];
	Matrix(int r_ = 0, int c_ = 0) :
		r(r_), c(c_) { memset(a, 0, sizeof a); }
	void resize(int r_, int c_) { r = r_, c = c_; }
	int * operator[](int x) { return a[x]; }
	const int * operator[](int x) const { return a[x]; }
	Matrix operator*(const Matrix & m) const;
	Matrix FPow(int ex) const;
} A, T;

char L[15], R[15];
int n, iden, ab, bc, ca, tot;
int id[15][15]; 

int main() {
	scanf("%s%s%d%d%d%d", L, R,
		&ab, &bc, &ca, &tot);
	int cnt0, cnt1, cnt2;
	cnt0 = cnt1 = cnt2 = 0;
	for (; L[n]; ++n) {
		if (L[n] == 'a') {
			if (R[n] == 'a') ++cnt0;
			else if (R[n] == 'b') {
				++cnt1; tot -= ab;
			} else {
				++cnt2; tot -= ab + bc;
			}
		} else if (L[n] == 'b') {
			if (R[n] == 'a') {
				++cnt2; tot -= bc + ca;
			} else if (R[n] == 'b') ++cnt0;
			else {
				++cnt1; tot -= bc;
			}
		} else {
			if (R[n] == 'a') {
				++cnt1; tot -= ca;
			} else if (R[n] == 'b') {
				++cnt2; tot -= ca + ab;
			} else ++cnt0;
		}
	}
	for (int i = 0; i <= n; i++) {
		for (int j = 0; i + j <= n; j++)
			id[i][j] = iden++;
	} ++iden;
	T.resize(iden, iden);
	for (int i = 0; i <= n; i++) {
		for (int j = 0, o; i + j <= n; j++) {
			o = id[i][j];
			if (i) Adds(T[o][id[i - 1][j]], i);
			if (j) Adds(T[o][id[i + 1][j - 1]], j);
			if (i + j < n) Adds(T[o][id[i][j + 1]], n - i - j);
		}
	} T[iden - 1][iden - 1] = T[id[n][0]][iden - 1] = 1;
	T = T.FPow(cnt1 + cnt2 * 2 + tot / (ab + bc + ca) * 3 + 1);
	printf("%d\n", T[id[cnt0][cnt1]][iden - 1]);
	return 0;
}

Matrix Matrix::operator*(const Matrix & m) const {
	Matrix res(r, m.c);
	assert(c == m.r);
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < m.c; j++) {
			for (int k = 0; k < c; k++)
				Adds(res[i][j], Mul(a[i][k], m[k][j]));
		}
	} return res;
}

Matrix Matrix::FPow(int ex) const {
	Matrix res(r, r), bs = *this;
	assert(r == c);
	for (int i = 0; i < r; i++) res[i][i] = 1;
	for (; ex; bs = bs * bs, ex >>= 1)
		if (ex & 1) res = res * bs;
	return res;
}
