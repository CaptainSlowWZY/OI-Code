#include <cstdio>
#include <cstring>

const int kMaxn = 205, kMaxv = 5010, kMaxk = 55;

int k, v, n;
int W[kMaxn], V[kMaxn], buf[kMaxk], DP[kMaxv][kMaxk];

int main() {
	scanf("%d%d%d", &k, &v, &n);	
	for (int i = 0; i < n; i++) scanf("%d%d", W + i, V + i);
	
	memset(DP, 0x80, sizeof DP);
	DP[0][0] = 0;
	for (int i = 0; i < n; i++) {
		for (int j = v; j >= W[i]; j--) {
			for (int l = 0, p1 = 0, p2 = 0; l < k; l++) {
				buf[l] = DP[j][p1] < DP[j - W[i]][p2] + V[i] ?
					DP[j - W[i]][p2++] + V[i] : DP[j][p1++];
			}
			memcpy(DP[j], buf, sizeof(int) * k);
		}
	}
	int ans = 0;
	for (int i = 0; i < k; i++) ans += DP[v][i];
	printf("%d\n", ans);
	return 0;
}
