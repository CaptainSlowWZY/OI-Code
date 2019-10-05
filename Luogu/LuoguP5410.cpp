// EX-KMP template
#include <algorithm>
// #include <cassert>
#include <cctype>
// #include <cmath>
#include <cstdio>
// #include <cstdlib>
#include <cstring>

#define pch putchar

const int kLen = 1e5 + 5;

int lena, lenb;
char A[kLen], B[kLen];
int exa[kLen], exb[kLen];

void ExKmp();

int main() {
	scanf("%s%s", A + 1, B + 1);
	lena = strlen(A + 1), lenb = strlen(B + 1);
	ExKmp();
	for (int i = 1; i <= lenb; ++i) printf("%d ", exb[i]);
	pch('\n');
	for (int i = 1; i <= lena; ++i) printf("%d ", exa[i]);
	pch('\n');
	return 0;
}

void ExKmp() {
	exb[1] = lenb;
	int x = 1, k = 2;
	while (x + 1 <= lenb && B[x] == B[x + 1]) ++x;
	exb[2] = x - 1;
	for (int i = 3, p, l, j; i <= lenb; ++i) {
		p = k + exb[k] - 1, l = exb[i - k + 1];
		if (i + l < p + 1) exb[i] = l;
		else {
			for (j = std::max(0, p - i + 1);
				i + j <= lenb && B[j + 1] == B[i + j]; ++j);
			exb[k = i] = j;
		}
	}
	for (x = 1; x <= lena && x <= lenb && A[x] == B[x]; ++x);
	exa[k = 1] = x - 1;
	for (int i = 2, p, l, j; i <= lena; ++i) {
		p = k + exa[k] - 1, l = exb[i - k + 1];
		if (i + l < p + 1) exa[i] = l;
		else {
			for (j = std::max(0, p - i + 1); i + j <= lena &&
				j < lenb && B[j + 1] == A[i + j]; ++j);
			exa[k = i] = j;
		}
	}
}