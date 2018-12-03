// BZOJ 4259
#pragma GCC diagnostic error "-std=c++11"
#include <cstdio>
#include <cmath>
#include <complex>
#include <algorithm>
#include <vector>

#define rg register

const int MAXN = 1 << 20;
const double Pie = acos(-1);

typedef long long LL;
typedef std::complex<double> Cmplx;
typedef Cmplx CmplxArr[MAXN];
typedef int (*Intfun)(int);

char S[MAXN], T[MAXN];
int M, N;
CmplxArr A, B, OMG, CONJ_OMG;
LL C[MAXN];
std::vector<int> ret;

inline int self(int x) { return x; }
inline int sqr(int x) { return x * x; }
inline int cubic(int x) { return x * x * x; }
void turn(char [], int);
void init(int);
void FFT(Intfun, Intfun, int n);

int main() {
	scanf("%d%d%s%s", &N, &M, T, S);

	std::reverse(T, T + N);
	turn(S, M);
	turn(T, N);
	int n = 1;
	for (; n <= M + N; n <<= 1);
	init(n);

	FFT(cubic, self, n);
	for (int i = 0; i < n; i++) C[i] = (LL)floor(A[i].real() / (double)n + 0.5);
	FFT(sqr, sqr, n);
	for (int i = 0; i < n; i++) C[i] -= 2 * (LL)floor(A[i].real() / (double)n + 0.5);
	FFT(self, cubic, n);
	for (int i = 0; i < n; i++) C[i] += (LL)floor(A[i].real() / (double)n + 0.5);

	for (int i = N - 1; i < M; i++)
		if (!C[i]) ret.push_back(i - N + 1);

	printf("%d\n", (int)ret.size());
	for (int pos : ret) printf("%d ", pos + 1);
	if ((int)ret.size()) putchar('\n');

	return 0;
}

void turn(char str[], int len) {
	for (rg int i = 0; i < len; i++)
		if (str[i] == '*') str[i] = 0;
		else str[i] -= 'a' - 1;
}

void init(int n) {
	for (rg int i = 0; i < n; i++) {
		OMG[i] = Cmplx(cos(2 * Pie / n * i), sin(2 * Pie / n * i));
		CONJ_OMG[i] = std::conj(OMG[i]);
	}
}

void bit_reverse(Cmplx a[], int n) {
	for (rg int i = 0, j = 0; i < n; i++) {
		if (i > j) std::swap(a[i], a[j]);
		for (rg int l = n >> 1; (j ^= l) < l; l >>= 1);
	}
}

void DFT(Cmplx a[], Cmplx omg[], int n) {
	bit_reverse(a, n);
	for (rg int i = 2; i <= n; i <<= 1) {
		int m = i >> 1;
		for (rg int j = 0; j < n; j += i)
			for (rg int k = 0; k < m; k++) {
				Cmplx tmp = a[j + m + k] * omg[n / i * k];
				a[j + m + k] = a[j + k] - tmp;
				a[j + k] += tmp;
			}
	}
}

void FFT(Intfun pf1, Intfun pf2, int n) {
	for (rg int i = 0; i < M; i++) A[i] = pf1(S[i]);
	for (rg int i = M; i < n; i++) A[i] = 0;
	for (rg int i = 0; i < N; i++) B[i] = pf2(T[i]);
	for (rg int i = N; i < n; i++) B[i] = 0;

	DFT(A, OMG, n);
	DFT(B, OMG, n);
	for (rg int i = 0; i < n; i++) A[i] *= B[i];
	DFT(A, CONJ_OMG, n);
}
