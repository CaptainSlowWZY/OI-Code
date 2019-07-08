#include <algorithm>
#include <cstdio>

const int kInf = 0x3f3f3f3f;
const int kStick[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
const int kDf[10][10] = {
	{0, 4, 3, 3, 4, 3, 3, 3, 1, 2},
	{4, 0, 5, 3, 2, 5, 6, 1, 5, 4},
	{3, 5, 0, 2, 5, 4, 3, 4, 2, 3},
	{3, 3, 2, 0, 3, 2, 3, 2, 2, 1},
	{4, 2, 5, 3, 0, 3, 4, 3, 3, 2},
	{3, 5, 4, 2, 3, 0, 1, 4, 2, 1},
	{3, 6, 3, 3, 4, 1, 0, 5, 1, 2},
	{3, 1, 4, 2, 3, 4, 5, 0, 4, 3},
	{1, 5, 2, 2, 3, 2, 1, 4, 0, 1},
	{2, 4, 3, 1, 2, 1, 2, 3, 1, 0}};
const int lb[5] = {0, 0, 10, 100, 1000};
const int ub[5] = {0, 9, 99, 999, 2000};

char S[100];
int A[3], D[3];

int Len(int x);
int Calc(int x);
int Diff(int x, int y);

int main() {
	scanf("%s", S);
	int plus = 0, dec = 0;
	for (int i = 0, j = 0; S[i]; i++) {
		if ('0' <= S[i] && S[i] <= '9') {
			A[j] = A[j] * 10 + (S[i] ^ '0');
		} else {
			++j;
			if (S[i] == '+') plus = 1;
			if (S[i] == '-') dec = 1;
		}
	}

	int tots = 0;
	for (int i = 0; i < 3; i++) {
		D[i] = Len(A[i]);
		tots += Calc(A[i]);
	}
	if (plus) tots += 4;
	if (dec) tots += 3;
	int ans = kInf;
	for (int a = lb[D[0]]; a <= ub[D[0]]; a++) {
		for (int c, b = lb[D[1]]; b <= ub[D[1]]; b++) {
			c = a + b;
			if (Calc(a) + Calc(b) + Calc(c) + 4 == tots && Len(c) == D[2]) {
				ans = std::min(ans, Diff(A[0], a) + Diff(A[1], b) + Diff(A[2], c) + dec >> 1);
			}
			c = a - b;
			if (c >= 0 && Calc(a) + Calc(b) + Calc(c) + 3 == tots && Len(c) == D[2]) {
				ans = std::min(ans, Diff(A[0], a) + Diff(A[1], b) + Diff(A[2], c) + plus >> 1);
			}
		}
	}

	printf("%d\n", ans == kInf ? -1 : ans);
	return 0;
}

int Len(int x) {
	if (!x) return 1;
	int l = 0;
	for (; x; x /= 10, l++);
	return l;
}

int Calc(int x) {
	if (!x) return kStick[0];
	int res = 0;
	for (; x; x /= 10) res += kStick[x % 10];
	return res;
}

int Diff(int x, int y) {
	int l = Len(x), res = 0;
	for (int i = 0; i < l; i++) {
		res += kDf[x % 10][y % 10];
		x /= 10, y /= 10;
	}
	return res;
}
