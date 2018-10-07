// XJOI 1014 1
#include <cstdio>

int N;

namespace Subtask1 {
	void solve();
}
namespace Subtask2 {
	void solve();
}

int main() {
	scanf("%d", &N);
	if (N <= 26) Subtask1::solve();
	else Subtask2::solve();
	return 0;
}

namespace Subtask1 {
	void solve() {
		for (int i = 0; i < N; i++) putchar('a' + i), putchar('\n');
	}
}
namespace Subtask2 {
	/*
	Let's construct the strings like this:
	ababab....
	cdcdcd....
	efefef....
	g
	h
	....
	z(in turns)
	 */
	void solve() {	
		int rnd = (N - 3) / 20, rem = (N - 3) % 20;
		for (int i = 0; i < rem; i++) {
			for (int j = 0; j <= rnd; j++) putchar('g' + i), putchar('\n');
		}
		for (int i = 20 - rem; i > 0; i--) {
			for (int j = 0; j < rnd; j++) putchar('g' + rem + i - 1), putchar('\n');
		}
		int smlv = rem * rnd * (rnd + 1) / 2 + (20 - rem) * (rnd - 1) * rnd / 2;
		if (smlv >= 99) {
			for (int i = 0; i < 50; i++) putchar('a'), putchar('b');
			smlv -= 99;
		}
		else {
			for (int i = 0, f = 0; i <= smlv; i++, f ^= 1) putchar('a' + f);
			smlv = 0;
		}
		putchar('\n');
		if (smlv >= 99) {
			for (int i = 0; i < 50; i++) putchar('c'), putchar('d');
			smlv -= 99;
		}
		else {
			for (int i = 0, f = 0; i <= smlv; i++, f ^= 1) putchar('c' + f);
			smlv = 0;
		}
		putchar('\n');
		if (smlv >= 99) {
			for (int i = 0; i < 50; i++) putchar('e'), putchar('f');
			smlv -= 99;
		}
		else {
			for (int i = 0, f = 0; i <= smlv; i++, f ^= 1) putchar('e' + f);
			smlv = 0;
		}
		putchar('\n');
	}
}

// AC!!!