#pragma GCC optimize(2)
#include <cstdio>
#include <vector>

#define fir first
#define sec second

typedef std::vector<int> vec;
typedef std::pair<int, int> Pii;

const int kMod = 1e9 + 9;
const int kC[] = {1, 4, 6, 4, 1};

class Matrix {
private:
	std::vector<vec> m;
	int r, c;
public:
	Matrix() {}
	Matrix(int r_, int c_) : r(r_), c(c_) {
		m = std::vector<vec>(r);
		for (int i = 0; i < r; i++) m[i] = vec(c);
	}
	vec & operator[](int x) { return m[x]; }
	Matrix operator*(const Matrix & b) const;
	friend Matrix FPow(Matrix m, int ex);
} trans[31];

int n, k, index;
int id[11][11];
Pii P[60];

int main() {
	for (int i = 1; i <= 10; i++) {
		for (int j = 1; j <= i; j++)
			P[id[i][j] = index++] = Pii(i, j);
	}
	Matrix ts(index, index);
	for (int i = 1; i <= 10; i++) {	// limit
		for (int j = 1; j <= i; j++) { // hight
			if (j < i) ++ts[id[i][j + 1]][id[i][j]];
			if (j >= i - 4) ts[id[j][1]][id[i][j]] += kC[i - j];
		}
	} trans[0] = ts;
	for (int i = 1; i <= 30; i++)
		trans[i] = trans[i - 1] * trans[i - 1];
	while (~scanf("%d%d", &n, &k) && n + k) {
		if (n == 1) { puts("4"); continue; }
		long long ans = 0;
		for (int h = 1; h <= k && h <= n; h++) {
			Matrix org(index, 1);
			org[id[h][h]][0] = 1;
			org = FPow(ts, n - h) * org;
			for (int i = 0; i < index; i++) {
				if (!org[i][0] || P[i].sec > 4 ||
					P[i].fir - P[i].sec > 4) continue;
			//	I know someone named Um_nik would come to HE my code.
			//	I'm ready for you now.
			//	printf(" (%d, %d), ans %d\n", P[i].fir, P[i].sec, org[i][0]);
				(ans += 1ll * org[i][0] * kC[P[i].fir - P[i].sec]
				 % kMod * kC[P[i].sec] % kMod) %= kMod;
			}
		}
		printf("%lld\n", ans);
	} return 0;
}

Matrix Matrix::operator*(const Matrix & b) const {
	Matrix res(r, b.c);
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < b.c; j++) {
			for (int k = 0; k < c; k++)
				(res[i][j] += 1ll * m[i][k] * b.m[k][j] % kMod) %= kMod;
		}
	} return res;
}

Matrix FPow(Matrix bs, int ex) {
	Matrix res(bs.r, bs.c);
	for (int i = 0; i < res.r; i++) res[i][i] = 1;
	for (int i = 0; i <= 30; i++) {
		if (ex >> i & 1) res = res * trans[i];
	} return res;
}
