// UOJ 34
// FFT template
#include <cstdio>
#include <complex>

typedef std::complex<double> Cmplx;

const int MAXN = 3e5 + 10;
const double Pie = acos(-1);

Cmplx A[MAXN], B[MAXN], OMG[MAXN], CONJ_OMG[MAXN];
int N, M;

void init(int n);
void DFT(Cmplx a[], Cmplx omg[], int n);

int main() {
	scanf("%d%d", &N, &M);
	for (int Ai, i = 0; i <= N; i++) {
		scanf("%d", &Ai);
		A[i].real(Ai);
	}
	for (int Bi, i = 0; i <= M; i++) {
		scanf("%d", &Bi);
		B[i].real(Bi);
	}

	int n = 1;
	// N + M + 1 points at least
	for (; n <= N + M + 1; n <<= 1);
	init(n);
	
	DFT(A, OMG, n);
	DFT(B, OMG, n);
	for (int i = 0; i < n; i++) A[i] *= B[i];
	DFT(A, CONJ_OMG, n);	// in fact this step is IDFT
	for (int i = 0; i < n; i++) A[i] /= n;

	for (int i = 0; i <= N + M; i++) printf("%d ", (int)floor(A[i].real() + 0.5));

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