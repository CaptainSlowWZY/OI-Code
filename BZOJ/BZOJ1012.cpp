// BZOJ 1012
// JSOI 2008
#include <cstdio>
#include <utility>

#define fir first
#define sec second

typedef std::pair<int, int> Pii;

int N, MOD, len;
Pii que[200010];
char S[5];

int main() {
	scanf("%d%d", &N, &MOD);
	int tl = 0, last = 0;
	for (int i = 0, x; i < N; i++) {
		scanf("%s%d", S, &x);
		if (S[0] == 'Q') {
			int l = 0, r = tl, mid;	// (l, r]
			while (r - l > 1) {
				mid = l + r >> 1;
				if (que[mid].sec <= len - x) l = mid;
				else r = mid;
			}
			printf("%d\n", last = que[r].fir);
		}
		else {
			x = (x + last) % MOD;
			Pii now(x, ++len); 
			while (tl > 0 && que[tl].fir <= now.fir) --tl;
			que[++tl] = now;
		}
	}

	return 0;
}
