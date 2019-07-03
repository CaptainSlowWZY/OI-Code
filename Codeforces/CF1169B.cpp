#include <cstdio>
#include <cstring>

const int kMaxn = 3e5 + 5;

int n, m;
int A[kMaxn], B[kMaxn], cnt[kMaxn];

bool Suppose(int x);

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++) scanf("%d%d", A + i, B + i);

	puts(Suppose(A[0]) || Suppose(B[0]) ? "YES" : "NO");
	return 0;
}

bool Suppose(int x) {
	static int cnt[kMaxn];
	memset(cnt, 0, sizeof cnt);

	int tot = 0;
	for (int i = 1; i < m; i++) {
		if (A[i] == x || B[i] == x) continue;
		++tot, ++cnt[A[i]];
		if (B[i] != A[i]) ++cnt[B[i]];
	}
	int maxi = 0;
	for (int i = 1; i <= n; i++) {
		if (cnt[maxi] < cnt[i]) maxi = i;
	}
	return cnt[maxi] == tot;
}
