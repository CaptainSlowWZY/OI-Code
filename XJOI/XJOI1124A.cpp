#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <complex>

typedef std::complex<double> Cmplx;

const int MAXN = 1 << 19;
const double Pie = acos(-1);

int N, M, K, h[MAXN], f[4][MAXN], g[4][MAXN], last[4];
char S[MAXN], T[MAXN];
Cmplx OMG[MAXN], CONJ_OMG[MAXN], A[MAXN], B[MAXN];

void turn(char str[]);
void init(int n);
void FFT(int n, const int f[], const int g[], int h[]);

int main() {
	scanf("%d%s%s", &K, S, T);

	N = strlen(S), M = strlen(T);
	std::reverse(T, T + M);
	turn(S);
	turn(T);
	memset(last, 0x80, sizeof last);
	for (int i = 0; i < N; i++) {
		last[S[i]] = i;
		for (int j = 0; j < 4; j++) f[j][i] = i - last[j] <= K;
	}
	memset(last, 0x7f, sizeof last);
	for (int i = N - 1; i >= 0; i--) {
		last[S[i]] = i;
		for (int j = 0; j < 4; j++) f[j][i] |= last[j] - i <= K;
	}
	for (int i = 0; i < M; i++) g[T[i]][i] = 1;

	int n = 1;
	for (; n <= N + M; n <<= 1);
	init(n);
	
	for (int i = 0; i < 4; i++) FFT(n, f[i], g[i], h);

	int ans = 0;
	for (int i = M - 1; i < N; i++)
		if (h[i] == M) ++ans;
	
	printf("%d\n", ans);
	return 0;
}

void turn(char str[]) {
	for (int i = 0; str[i]; i++) {
		if (str[i] == 'Z') str[i] = 0;
		if (str[i] == 'P') str[i] = 1;
		if (str[i] == 'S') str[i] = 2;
		if (str[i] == 'B') str[i] = 3;
	}
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

void DFT(Cmplx a[], const Cmplx omg[], int n) {
	bit_reverse(a, n);
	for (int i = 2; i <= n; i <<= 1) {
		int m = i >> 1;
		for (int j = 0; j < n; j += i)
			for (int k = 0; k < m; k++) {
				Cmplx tmp = a[j + m + k] * omg[n / i * k];
				a[j + m + k] = a[j + k] - tmp;
				a[j + k] += tmp;
			}
	}
}

void FFT(int n, const int f[], const int g[], int h[]) {
	for (int i = 0; i < n; i++) A[i] = f[i], B[i] = g[i];
	DFT(A, OMG, n);
	DFT(B, OMG, n);
	for (int i = 0; i < n; i++) A[i] *= B[i];
	DFT(A, CONJ_OMG, n);
	for (int i = 0; i < n; i++) h[i] += (int)floor(A[i].real() / (double)n + 0.5);
}