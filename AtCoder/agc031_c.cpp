#include <cstdio>

const int kBits = 18, kLen = (1 << 17) + 5;

int N, A, B, ans[kBits][kLen];

void Solve(int s, int t, int bit);

int main() {
	scanf("%d%d%d", &N, &A, &B);

	int ca = 0, cb = 0;
	for (int i = 0; i < N; i++) ca += A >> i & 1;
	for (int i = 0; i < N; i++) cb += B >> i & 1;
	if ((ca & 1) == (cb & 1)) {
		puts("NO");
		return 0;
	}

	Solve(A, B, N);
	puts("YES");
	for (int i = 0, u = 1 << N; i < u; i++) {
		printf("%d ", ans[N][i]);
	}
	putchar('\n');
	return 0;
}

inline int DelBit(int n, int i) {
	return n >> i + 1 << i | n & (1 << i) - 1;
}

inline int InsBit(int n, int i, int b) {
	return n >> i << i + 1 | n & (1 << i) - 1 | (1 & b) << i;
}

void Solve(int s, int t, int bit) {
//	printf(" Solve from %d to %d, bit = %d\n", s, t, bit);
	if (bit == 1) {
		ans[1][0] = s, ans[1][1] = t;
		return;
	}
	for (int i = 0; i < bit; i++) {
		if (!(s >> i & 1 ^ t >> i & 1)) continue;
		int c = DelBit(s, i) ^ 1, u = 1 << bit - 1;
	//	printf("  s and t differ at %d bits, c = %d\n", i, c);
		Solve(DelBit(s, i), c, bit - 1);
		for (int j = 0; j < u; j++) {
			ans[bit][j] = InsBit(ans[bit - 1][j], i, s >> i & 1);
		}
		Solve(c, DelBit(t, i), bit - 1);
		for (int j = 0; j < u; j++) {
			ans[bit][u + j] = InsBit(ans[bit - 1][j], i, t >> i & 1);
		}
		break;
	}
}
