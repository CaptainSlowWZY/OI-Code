#include <cstdio>
#include <cmath>
#include <cctype>
#include <algorithm>
// #include <complex>

const int kLen = (1 << 18) + 10, MOD = 1e9 + 7;
const long double kPie = acos(-1), kEPS = 1e-10;

typedef long long LL;
typedef long double LD;
// typedef std::complex<LD> Comp;
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

int N, L, R;
Poly A, fac, ifac, S;

namespace fast_io {
	template <typename T>
		void Read(T & x) {
			register char ch = getchar(); x = 0;
			for (; !isdigit(ch); ch = getchar());
			for (; isdigit(ch); ch = getchar())
				x = (x << 3) + (x << 1) + (ch ^ '0');
		}
}
void Solve(int r);
void NextLine(int r);
LL Inv(int r);
LL FPow(LL bs, int ex = MOD - 2) {
	LL ret = 1;
	for (; ex; (bs *= bs) %= MOD, ex >>= 1)
		if (ex & 1) (ret *= bs) %= MOD;
	return ret;
}

void Debug(LL a[], int len, int sp = 2) {
	for (int i = 0; i < sp; i++) putchar(' ');
	for (int i = 0; i < len; i++) printf("%lld ", a[i]);
	putchar('\n');
}

int main() {
	using fast_io::Read;
	
	Read(N), Read(L), Read(R);
	for (int i = 1; i <= N; i++) Read(A[i]);

	fac[0] = 1;
	for (LL i = 1; i <= L; i++) fac[i] = fac[i - 1] * i % MOD;
	ifac[L] = FPow(fac[L]);
	for (LL i = L - 1; i >= 0; i--) ifac[i] = ifac[i + 1] * (i + 1) % MOD;
	Solve(L - 1);
	// Debug(S, L);

	LL prv = Inv(L - 1), nxt;
	for (int i = L; i <= R; i++, prv = nxt) {
		NextLine(i);
		nxt = Inv(i);
		printf("%lld ", ((nxt - prv) % MOD + MOD) % MOD);
	}
	putchar('\n');
	return 0;
}

LL Inv(int n) {
	LL ret = 0;
	for (int i = 1; i <= n; i++) {
		(ret += (n - i & 1 ? -1ll : 1ll) * S[i] % MOD * A[i] % MOD) %= MOD;
	}
	return ret;
}

void NextLine(int r) {
	for (int i = r; i; i--) {
		S[i] = (LL(r - 1) * S[i] % MOD + S[i - 1]) % MOD;
	}
	if (r > 0) S[0] = 0;
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

void FFT(Poly A, Poly B, int deg, Poly ret) {
	static Comp a[kLen], aa[kLen], b[kLen], bb[kLen], buf1[kLen], buf2[kLen], buf3[kLen];
	int n = 1;
	for (; n <= deg + deg; n <<= 1);

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

// solve \prod\limits_{i=0}^{r-1}(x+i)
void Solve(int r) {
	static Poly fr, sc, buf;
	// printf(" Solve %d\n", r);
	if (r <= 1) return (void)(S[r] = 1);
	if (r & 1) {
		Solve(r - 1);
		NextLine(r);
	}
	else {
		int mid = r >> 1;
		Solve(mid);
		// printf("   Solved mid %d\n", mid);
		// Debug(S, mid + 1, 5);
		for (int i = 0; i <= mid; i++) fr[i] = S[i] * fac[i] % MOD;
		LL pow = 1;
		for (int i = 0; i <= mid; i++) {
			sc[i] = pow * ifac[i] % MOD;
			(pow *= mid) %= MOD;
		}
		std::reverse(sc, sc + mid + 1);
		// puts("Mult!");
		// Debug(fr, mid + 1);
		// Debug(sc, mid + 1);
		FFT(fr, sc, mid, buf);
		for (int i = 0; i <= mid; i++) {
			sc[i] = buf[i + mid] * ifac[i] % MOD;
			fr[i] = S[i];
		}
		FFT(fr, sc, mid, S);
		// printf("   cur:\n");
		// Debug(S, r + 1, 5);
	}
}