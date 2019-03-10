#include <cstdio>
#include <cmath>
#include <cctype>
#include <algorithm>
#include <complex>

const int kLen = (1 << 19) + 10;
const long double kPie = std::acos(-1.0L), kEPS = 1e-12;

typedef long long LL;
typedef long double LD;
typedef LL Poly[kLen];

class Comp {
private:
	LD re, im;
public:
	Comp(LD re_ = 0, LD im_ = 0) :
		re(re_), im(im_) {}
	LD real() const { return re; }
	Comp operator+(const Comp & c) const {
		return Comp(re + c.re, im + c.im);
	}
	Comp & operator+=(const Comp & c) {
		return *this = this->operator+(c);
	}
	Comp operator-(const Comp & c) const {
		return Comp(re - c.re, im - c.im);
	}
	Comp operator*(const Comp & c) const {
		return Comp(re * c.re - im * c.im, re * c.im + im * c.re);
	}
	Comp & operator*=(const Comp & c) {
		return *this = this->operator*(c);
	}
};

int n, m;
LL MOD;
Poly a1, a2, ret;

void FFT(Poly A, int lena, Poly B, int lenb, Poly ret);

int main() {
	scanf("%d%d%lld", &n, &m, &MOD);

	for (int i = 0; i <= n; i++) scanf("%lld", a1 + i);
	for (int i = 0; i <= m; i++) scanf("%lld", a2 + i);
	FFT(a1, n, a2, m, ret);
	for (int i = 0; i <= n + m; i++) printf("%lld ", ret[i]);
	putchar('\n');

	return 0;
}

void DFT(Comp a[], int n, int f = 1) {
	//	bit-reverse
	for (int i = 0, j = 0; i < n; i++) {
		if (i > j) std::swap(a[i], a[j]);
		for (int l = n >> 1; (j ^= l) < l; l >>= 1);
	}

	for (int i = 2, m; i <= n; i <<= 1) {
		m = i >> 1;
		Comp omega(std::cos(kPie * 2 / i), std::sin(kPie * 2 / i) * f);
		for (int j = 0; j < n; j += i) {
			Comp o = 1;
			for (int k = 0; k < m; k++, o *= omega) {
				Comp tmp = a[j + m + k] * o;
				a[j + m + k] = a[j + k] - tmp;
				a[j + k] += tmp;
			}
		}
	}
}

void FFT(Poly A, int dega, Poly B, int degb, Poly ret) {
	static Comp a[kLen], aa[kLen], b[kLen], bb[kLen], buf1[kLen], buf2[kLen], buf3[kLen];
	int n = 1;
	for (; n <= dega + degb; n <<= 1);

	for (int i = 0; i < n; i++) {
		A[i] %= MOD;
		a[i] = A[i] >> 15, aa[i] = A[i] & 0x7fff;
	}
	for (int i = 0; i < n; i++) {
		B[i] %= MOD;
		b[i] = B[i] >> 15, bb[i] = B[i] & 0x7fff;
	}
	DFT(a, n), DFT(b, n), DFT(aa, n), DFT(bb, n);
	for (int i = 0; i < n; i++) {
		buf1[i] = a[i] * b[i];
		buf2[i] = a[i] * bb[i] + aa[i] * b[i];
		buf3[i] = aa[i] * bb[i];
	}
	DFT(buf1, n, -1), DFT(buf2, n, -1), DFT(buf3, n, -1);
	for (int i = 0; i < n; i++) {
		ret[i] = ((llround(buf1[i].real() / n) % MOD) << 30) % MOD;
		ret[i] = (ret[i] + ((llround(buf2[i].real() / n) % MOD) << 15) % MOD) % MOD;
		ret[i] = (ret[i] + llround(buf3[i].real() / n) % MOD) % MOD;
		ret[i] = (ret[i] + MOD) % MOD;
	}
}