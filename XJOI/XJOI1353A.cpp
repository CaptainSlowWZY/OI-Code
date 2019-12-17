#include <algorithm>
#include <cmath>
#include <cstdio>

typedef long double Db;

const int kMaxn = 5e4 + 5;
const Db k2Pi = 2 * acos(-1);

int n;
Db A[kMaxn], ans[kMaxn];

namespace solver1 { void Solve(); }
namespace solver2 { void Solve(); }

int main() {
	scanf("%d", &n);
	solver2::Solve();
	for (int i = 0; i <= n; ++i) printf("%.12Lf\n", ans[i]);
	return 0;
}

namespace solver1 {
	void Solve() {
		for (int i = 0; i < n; ++i) scanf("%Lf", A + i);
		for (int i = 1; i <= n; ++i) {
			Db cur = 1;
			for (int j = 0; j < i; ++j) cur *= A[j];
			ans[i] = cur *= 1 - A[i];
			for (int j = i; j < n; ++j) {
				cur = cur / (1 - A[j]) * A[j];
				cur = cur / A[j - i] * (1 - A[j - i]);
				if (j - i) cur = cur / (1 - A[j - i - 1]);
				if (j + 1 < n) cur *= 1 - A[j + 1];
				ans[i] += cur;
			}
		}
	}
}

namespace solver2 {
	const int kLen = 1 << 17;

	struct Comp {
		Db re, im;
		Comp(Db _r = 0, Db _i = 0) : re(_r), im(_i) {}
		Comp operator+(const Comp & c) const { return {re + c.re, im + c.im}; }
		Comp operator-(const Comp & c) const { return {re - c.re, im - c.im}; }
		Comp operator*(const Comp & c) const { return {re * c.re - im * c.im, re * c.im + c.re * im}; }
		Comp operator/(Db k) const { return {re / k, im / k}; }
	} ome[kLen], B[kLen], C[kLen];

	void Dnt(Comp a[], int n) {
		for (int i = 0, j = 0; i < n; ++i) {
			if (i > j) std::swap(a[i], a[j]);
			for (int l = n >> 1; (j ^= l) < l; l >>= 1);
		}
		for (int i = 2, h, d = kLen >> 1; i <= n; i <<= 1, d >>= 1) {
			h = i >> 1;
			for (int j = 0; j < n; j += i) for (int k = 0, o = 0; k < h; ++k, o += d) {
				Comp t = a[j + h + k] * ome[o];
				a[j + h + k] = a[j + k] - t, a[j + k] = a[j + k] + t;
			}
		}
	}
	void Mul(Comp b[], int db, Comp c[], int dc) {
		int n = 1;
		for (; n < db + dc; n <<= 1);
		for (int i = db; i < n; ++i) b[i] = 0;
		for (int i = dc; i < n; ++i) c[i] = 0;
		Dnt(b, n); Dnt(c, n);
		for (int i = 0; i < n; ++i) b[i] = b[i] * c[i];
		std::reverse(b + 1, b + n); Dnt(b, n);
		for (int i = 0; i < n; ++i) b[i] = b[i] / n;
		//      for (int i = 0; i < n; ++i) printf("%.3lf ", b[i]); puts("");
	}
	void Solve(int l, int r) {
		if (l > r) return;
		if (l == r) {
			ans[1] += A[l] * (1 - A[l - 1]) * (1 - A[l + 1]);
			return;
		}
		int mid = l + r >> 1, db = 1, dc = 1;
		//      B[0] = 1 - A[mid], C[0] = 1 - A[mid + 1];
		B[0] = C[0] = 0;
		Db prd = 1;
		for (int i = mid; i >= l; --i) { prd *= A[i], B[db++] = (1 - A[i - 1]) * prd; }
		prd = 1;
		for (int i = mid + 1; i <= r; ++i) { prd *= A[i], C[dc++] = (1 - A[i + 1]) * prd; }
		/*      printf(" [%d, %d], db %d, dc %d\n", l, r, db, dc);
				for (int i = 0; i < db; ++i) printf("%.3lfx^%d ", B[i].re, i); puts("");
				for (int i = 0; i < dc; ++i) printf("%.3lfx^%d ", C[i].re, i); puts(""); */
		Mul(B, db, C, dc);
		for (int i = 1; i < db + dc; ++i) ans[i] += B[i].re;
		Solve(l, mid); Solve(mid + 1, r);
	}
	void Solve() {
		for (int i = 1; i <= n; ++i) scanf("%Lf", A + i);
		for (int i = 0; i < kLen; ++i) ome[i] = {cos(k2Pi / kLen * i), sin(k2Pi / kLen * i)};
		Solve(1, n);
	}
}
