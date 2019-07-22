#include <cstdio>

const int kMaxn = 1e6 + 5;

char S[kMaxn];
int len;

void Solve(int l, int r);

int main() {
	scanf("%s", S);
	
	for (; S[len]; ) S[len++] -= 'a';
	Solve(0, len);
	putchar('\n');
	return 0;
}

void Solve(int l, int r) {
	if (l >= r) return;
	if (r - l <= 3) {
		putchar('a' + S[l]);
		return;
	}
	static int cnt[3];
	for (int i = 0; i < 3; i++) cnt[i] = 0;
	for (int i = 0; i < 2; i++) {
		++cnt[S[l + i]], ++cnt[S[r - 1 - i]];
	}
	int k = 0;
	for (int i = 0; i < 3; i++) {
		if (cnt[i] >= 2) { k = i; break; }
	}
	for (int i = 0; i < 2; i++) {
		if (S[l + i] == k) putchar('a' + k);
	}
	Solve(l + 2, r - 2);
	for (int i = 0; i < 2; i++) {
		if (S[r - 1 - i] == k) putchar('a' + k);
	}
}
