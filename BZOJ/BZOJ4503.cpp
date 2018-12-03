// BZOJ 4503
#pragma GCC diagnostic error "-std=c++11"
#include <cstdio>
#include <cmath>
#include <complex>
#include <algorithm>
#include <vector>

#define pb push_back
#ifdef DEBUG_MD
	#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define debug(format, ...) 0
#endif

typedef std::complex<double> Cmplx;

const int MAXN = (1 << 18) + 10;
const double Pie = acos(-1);

char S[MAXN], T[MAXN];
int n1, n2, C[MAXN];
Cmplx A[MAXN], B[MAXN], OMG[MAXN], CONJ_OMG[MAXN];
std::vector<int> ret;

void init(int n);
void DFT(Cmplx a[], Cmplx omg[], int n);
inline int sqr(int x) {
	return x * x;
}

int main() {
	scanf("%s%s", S, T);

	for (n1 = 0; S[n1]; n1++) S[n1] -= 'a' - 1;
	for (n2 = 0; T[n2]; n2++)
		if (T[n2] == '?') T[n2] = 0;
		else T[n2] -= 'a' - 1;
	debug("n1=%d, n2=%d\n", n1, n2);
	std::reverse(T, T + n2);
	int n = 1;
	for (; n <= n1 + n2; n <<= 1);
	init(n);

	for (int i = 0; i < n1; i++) A[i] = sqr(S[i]);
	for (int i = 0; i < n2; i++) B[i] = T[i];
	DFT(A, OMG, n);
	DFT(B, OMG, n);
	for (int i = 0; i < n; i++) A[i] *= B[i];
	DFT(A, CONJ_OMG, n);
	for (int i = 0; i < n; i++) C[i] = (int)floor(A[i].real() / (double)n + 0.5);
	
	for (int i = 0; i < n1; i++) A[i] = S[i];
	for (int i = n1; i < n; i++) A[i] = 0;
	for (int i = 0; i < n2; i++) B[i] = sqr(T[i]);
	for (int i = n2; i < n; i++) B[i] = 0;
	DFT(A, OMG, n);
	DFT(B, OMG, n);
	for (int i = 0; i < n; i++) A[i] *= B[i];
	DFT(A, CONJ_OMG, n);
	int tmp = 0;	
	for (int i = 0; i < n2; i++) tmp += sqr(T[i]) * T[i];
	debug("tmp=%d\n", tmp);
	for (int i = 0; i < n; i++) C[i] = C[i] - 2 * (int)floor(A[i].real() / (double)n + 0.5) + tmp;

	for (int i = n2 - 1; i < n1; i++)
		if (!C[i]) ret.pb(i - n2 + 1);

	printf("%d\n", (int)ret.size());
	for (int pos : ret) printf("%d\n", pos);

	return 0;
}

void init(int n) {
	for (int i = 0; i < n; i++) {
		OMG[i] = Cmplx(cos(2 * Pie / n * i), sin(2 * Pie / n * i));
		CONJ_OMG[i] = std::conj(OMG[i]);
	}
}

void bit_reverse(Cmplx a[], int n) {
	for (int i = 0, j = 0; i < n; i++) {
		if (i > j) std::swap(a[i], a[j]);
		for (int l = n >> 1; (j ^= l) < l; l >>= 1);
	}
}

void DFT(Cmplx a[], Cmplx omg[], int n) {
	bit_reverse(a, n);
	for (int i = 2; i <= n; i <<= 1) {
		int m = i >> 1;
		for (int j = 0; j < n; j += i) {
			for (int k = 0; k < m; k++) {
				Cmplx tmp = a[j + m + k] * omg[n / i * k];
				a[j + m + k] = a[j + k] - tmp;
				a[j + k] += tmp;
			}
		}
	}
}
