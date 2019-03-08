// BZOJ 3527
// ZJOI 2014
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <complex>

typedef std::complex<double> Comp;

const int kMaxn = (1 << 18) + 10;
const double kPie = acos(-1);

int n, len;
double q[kMaxn], p[kMaxn], E[kMaxn];
Comp omg[kMaxn], comg[kMaxn];

inline double Sqr(double x) { return x * x; }
void F1(Comp ret[]) {
	for (int i = 0; i <= n; i++) E[i] = ret[i].real() / (double)len;
}
void F2(Comp ret[]) {
	for (int i = 0; i <= n; i++) E[i] -= ret[n - i + 1].real() / (double)len;
}
void FFT(double A_[], double B_[], void (*Calc)(Comp ret[]));

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%lf", q + i);

	for (len = 1; len < n + n; len <<= 1);
	for (int i = 0; i < len; i++) {
		omg[i] = Comp(cos(2.0 * kPie / len * i), sin(2.0 * kPie / len * i));
		comg[i] = std::conj(omg[i]);
	}
	p[0] = 0;
	for (int i = 1; i <= n; i++) p[i] = 1.0 / Sqr(i);
	FFT(p, q, F1);
	std::reverse(q + 1, q + 1 + n);
	FFT(p, q, F2);

	for (int i = 1; i <= n; i++) printf("%lf\n", E[i]);
	return 0;
}

void BitReverse(Comp a[]) {
	for (int i = 0, j = 0; i < len; i++) {
		if (i > j) std::swap(a[i], a[j]);
		for (int l = len >> 1; (j ^= l) < l; l >>= 1);
	}
}

void DFT(Comp a[], Comp o[]) {
	BitReverse(a);
	for (int i = 2, m, div = len >> 1; i <= len; i <<= 1, div >>= 1) {
		m = i >> 1;
		for (int j = 0; j < len; j += i) {
			for (int k = 0, ok = 0; k < m; k++, ok += div) {
				Comp tmp = a[j + m + k] * o[ok];
				a[j + m + k] = a[j + k] - tmp;
				a[j + k] += tmp;
			}
		}
	}
}

void FFT(double A_[], double B_[], void (*Calc)(Comp ret[])) {	
	static Comp A[kMaxn], B[kMaxn];
	for (int i = 0; i < len; i++) {
		A[i] = Comp(A_[i]);
		B[i] = Comp(B_[i]);
	}
	DFT(A, omg);
	DFT(B, omg);
	for (int i = 0; i < len; i++) A[i] *= B[i];
	DFT(A, comg);
#ifndef ONLINE_JUDGE
	puts(" FFT ans:");
	for (int i = 0; i < len; i++) {
		printf("%.2lf ", A[i].real() / len);
	}
	putchar('\n');
#endif
	Calc(A);
}
