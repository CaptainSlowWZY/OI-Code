#include <bits/stdc++.h>

const int kLen = 5e5 + 10;

char S[kLen], T[kLen];
int fail[kLen];

void Turn(char str[]) {
	for (int i = 0; str[i]; i++) {
		str[i] ^= '0';
	}
}

int main() {
	scanf("%s%s", S, T);

	int lens = strlen(S), lent = strlen(T);
	Turn(S), Turn(T);
	fail[0] = fail[1] = 0;
	for (int i = 1, j; i < lent; i++) {
		for (j = fail[i]; j && T[i] != T[j]; j = fail[j]);
		fail[i + 1] = T[i] == T[j] ? j + 1 : 0;
	}
	int s0 = 0, s1 = 0;
	for (int i = 0; i < lens; i++) {
		!S[i] ? ++s0 : ++s1;
	}
	for (int i = 0; i < fail[lent]; i++) {
		if (T[i] && s1) {
			putchar('1');
			--s1;
		}
		if (!T[i] && s0) {
			putchar('0');
			--s0;
		}
	}
	if (!s0 || !s1) {
		for (; s0 > 0; --s0) putchar('0');
		for (; s1 > 0; --s1) putchar('1');
	}
	else {
		int fir = fail[lent], lst = lent;
		for (int j = fir; s0 > 0 && s1 > 0; j++) {
			if (j == lst) j = fir;
			if (T[j] && s1) {
				putchar('1');
				--s1;
			}
			if (!T[j] && s0) {
				putchar('0');
				--s0;
			}
		}
		for (; s0 > 0; --s0) putchar('0');
		for (; s1 > 0; --s1) putchar('1');
	}
	putchar('\n');
	return 0;
}
