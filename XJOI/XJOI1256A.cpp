// tetris
#include <algorithm>
// #include <cassert>
#include <cctype>
// #include <cmath>
#include <cstdio>
// #include <cstdlib>
#include <cstring>
// #include <ctime>
#include <map>
#include <queue>
#include <set>
#include <vector>

#define fir first
#define sec second
#define pb push_back
#define pch putchar
#define rg register
#define SZ(_) (int)_.size()
#define SORT(_) std::sort(_.begin(), _.end())
#define LB(_, __) std::lower_bound(_.begin(), _.end(), __)
#define UB(_, __) std::upper_bound(_.begin(), _.end(), __)

typedef long long LL;
typedef std::pair<int, int> Pii;
typedef std::pair<LL, int> Pli;
typedef std::pair<int, LL> Pil;
typedef std::pair<LL, LL> Pll;
typedef std::vector<int> Vi;
typedef std::vector<LL> Vl;
typedef std::map<int, int> Mii;
typedef std::map<LL, int> Mli;
typedef std::map<int, LL> Mil;
typedef std::map<LL, LL> Mll;
typedef std::set<int> Si;
typedef std::set<LL> Sl;

const int kInf = 0x3f3f3f3f, kMod = 1e9 + 7;
const LL kInf64 = 0x3f3f3f3f3f3f3f3f;
// const double kPie = acos(-1), kEps = 1e-9;

template <typename T> inline
void UMin(T & x, const T & y) { if (x > y) x = y; }
template <typename T> inline
void UMax(T & x, const T & y) { if (x < y) x = y; }
inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + kMod : a; }
inline int Mul(int a, int b) { return 1ll * a * b % kMod; }
int FPow(int bs, int ex = kMod - 2) {
	int res = 1;
	for (; ex; bs = Mul(bs, bs), ex >>= 1)
		if (ex & 1) res = Mul(res, bs);
	return res;
}

struct Matrix {
	int r, c, a[16][16];
	Matrix() {}
	Matrix(int r_, int c_) : r(r_), c(c_) {
		for (int i = 0; i < r; ++i)
			for (int j = 0; j < c; ++j) a[i][j] = 0;
	}
	int *operator[](int r) { return a[r]; }
	Matrix operator*(const Matrix & m) const {
		Matrix res(r, m.c);
		for (int i = 0; i < r; ++i)
			for (int j = 0; j < m.c; ++j)
				for (int k = 0; k < c; ++k)
					res[i][j] = Add(res[i][j],
						Mul(a[i][k], m.a[k][j]));
		return res;
	}
	friend Matrix FPow(const Matrix & m, LL ex) {
		Matrix res(m.r, m.c), bs = m;
		for (int i = 0; i < m.r; ++i) res[i][i] = 1;
		for (; ex; bs = bs * bs, ex >>= 1)
			if (ex & 1) res = res * bs;
		return res;
	}
	void debug() const {
		printf("     ");
		for (int i = 0; i < c; ++i) printf("%3d", i + 1);
		pch('\n');
		for (int i = 0; i < r; ++i) {
			printf("%5d", i + 1);
			for (int j = 0; j < c; ++j) printf("%3d", a[i][j]);
			pch('\n');
		} pch('\n');
	}
};

int id[5][3];
LL n;

int main() {
//	Pii S[3] = {{1, 3}, {3, 3}, {3, 1}};
	int gap = 5, msz = 0;
	for (int i = 0; i < gap; ++i)
		for (int j = 0; j < 3; ++j) id[i][j] = msz++;
	Matrix T(msz, msz);
	++T[id[0][0]][id[1][2]]; ++T[id[0][0]][id[0][1]];
	++T[id[0][1]][id[3][1]]; ++T[id[0][1]][id[1][1]];
	++T[id[0][1]][id[2][0]]; ++T[id[0][1]][id[2][2]];
	++T[id[0][2]][id[1][0]]; ++T[id[0][2]][id[0][1]];
	for (int i = 1; i < gap; ++i) {
		++T[id[i][0]][id[i - 1][0]];
		++T[id[i][1]][id[i - 1][1]];
		++T[id[i][2]][id[i - 1][2]];
	}
//	T.debug();
//	FPow(T, 2).debug();
	Matrix O(msz, 1);
	O[id[0][1]][0] = 1;
	while (~scanf("%lld", &n)) {
		Matrix ans = FPow(T, n) * O;
		printf("%d\n", ans[id[0][1]][0]);
	} return 0;
}
