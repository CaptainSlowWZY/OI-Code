#include <algorithm>
#include <cstdio>

const int kMaxn = 1e4 + 5, kMaxm = 1e3 + 5, kInf = 0x3f3f3f3f;

int n, m, k;
int X[kMaxn], Y[kMaxn], L[kMaxn], H[kMaxn];
int min[kMaxm], DP[2][kMaxm], *prv, *nxt;

int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 0; i < n; i++) {
		scanf("%d%d", X + i, Y + i);
		L[i + 1] = 0, H[i + 1] = m + 1;
	}
	for (int i = 0, p; i < k; i++) {
		scanf("%d", &p);
		scanf("%d%d", L + p, H + p);
	}

	prv = DP[0], nxt = DP[1];
	prv[0] = kInf;
	for (int i = 0, cnt = 0; i < n; i++) {
		int able = 0;
		std::fill(nxt, nxt + m + 1, kInf);
		for (int j = X[i] + 1; j <= m; j++)
			nxt[j] = std::min(nxt[j],
				std::min(nxt[j - X[i]], prv[j - X[i]]) + 1);
		for (int j = m - X[i]; j <= m; j++)
			nxt[m] = std::min(nxt[m],
				std::min(prv[j], nxt[j]) + 1);
		for (int j = m - Y[i]; j; j--)
			nxt[j] = std::min(nxt[j], prv[j + Y[i]]);
		for (int j = 0; j <= L[i + 1]; j++) nxt[j] = kInf;
		for (int j = H[i + 1]; j <= m; j++) nxt[j] = kInf;
		for (int j = L[i + 1] + 1; j < H[i + 1]; j++)
			able |= nxt[j] < kInf;
		if (!able) {
			printf("0\n%d\n", cnt); return 0;
		} std::swap(prv, nxt);
		if (L[i + 1] || H[i + 1] <= m) ++cnt;
	} int ans = kInf;
	for (int i = 1; i <= m; i++) ans = std::min(ans, prv[i]);
	printf("1\n%d\n", ans);
	return 0;
}
