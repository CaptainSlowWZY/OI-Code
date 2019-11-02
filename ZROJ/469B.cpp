#include <cstdio>
#include <cstring>

const int kMod = 998244353;

inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + kMod : a; }
inline int Mul(int a, int b) { return 1ll * a * b % kMod; }
inline void Upa(int & a, int b) { a = Add(a, b); }

struct Matrix {
	int A[27][27];
	Matrix() { memset(A, 0, sizeof A); }
	Matrix(int ch) {
		memset(A, 0, sizeof A);
		for (int i = 0; i < 27; ++i)
			A[ch][i] = A[i][i] = 1;
	}
	int *operator[](int c) { return A[c]; }
	Matrix operator*(const Matrix & m) const;
	int value() const;
} R;

int m;
char C[2005];

int main() {
	scanf("%d%s", &m, C);
	R = Matrix(C[m - 1] - 'a');
	for (int i = m - 2; ~i; --i)
		R = R * Matrix(C[i] - 'a') * R;
	printf("%d\n", R.value());
	return 0;
}
Matrix Matrix::operator*(const Matrix & m) const {
	Matrix res;
	for (int i = 0; i < 27; ++i)
		for (int j = 0; j < 27; ++j) 
			for (int k = 0; k < 27; ++k)
				Upa(res[i][j], Mul(A[i][k], m.A[k][j]));
	return res;
}

int Matrix::value() const {
	int res = 0;
	for (int i = 0; i < 26; ++i) Upa(res, A[i][26]);
	return res;
}
