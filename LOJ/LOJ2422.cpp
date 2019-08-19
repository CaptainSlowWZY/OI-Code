#include <algorithm>
#include <cstdio>

const int kInf = 0x3f3f3f3f;

int t, n, sk, lk, ans;
int cnt[15];

void Dfs(int r, int t);

int main() {
	scanf("%d%d", &t, &n);
	while (t--) {
		sk = lk = 0;
		std::fill(cnt, cnt + 15, 0);
		for (int i = 0, a, b; i < n; i++) {
			scanf("%d%d", &a, &b);
			if (!a) (b == 1 ? sk : lk) = 1;
			else ++cnt[a == 1 ? 14 : a];
		} ans = kInf;
		Dfs(n, 0);
		printf("%d\n", ans);
	} return 0;
}

void Dfs(int r, int t) {
	if (t >= ans) return;
	if (!r) return (void)(ans = t);
	for (int i = 3; i <= 13; i++) {
		for (int j = 0, m = cnt[i + j];
			i + j <= 14 && cnt[i + j]; j++) {
			m = std::min(m, cnt[i + j]);
			if (j >= 4 && m) {
				for (int k = 0; k <= j; k++) --cnt[i + k];
				Dfs(r - j - 1, t + 1);
				for (int k = 0; k <= j; k++) ++cnt[i + k];
			} if (j >= 2 && m >= 2) {
				for (int k = 0; k <= j; k++) cnt[i + k] -= 2;
				Dfs(r - 2 * (j + 1), t + 1);
				for (int k = 0; k <= j; k++) cnt[i + k] += 2;
			} if (j && m >= 3) {
				for (int k = 0; k <= j; k++) cnt[i + k] -= 3;
				Dfs(r - 3 * (j + 1), t + 1);
				for (int k = 0; k <= j; k++) cnt[i + k] += 3;
			}
		}
	}
	for (int i = 2; i <= 14; i++) {
		if (cnt[i] <= 2) continue;
		for (int j = 2; j <= 14; j++) {
			if (!cnt[j] || j == i) continue;
			if (cnt[i] == 4 && cnt[j]) {
				cnt[i] -= 4;
				for (int k = j + 1; k <= 14; k++) {
					if (!cnt[k] || k == j || k == i) continue;
					if (cnt[j] >= 2 && cnt[k] >= 2) {
						cnt[j] -= 2, cnt[k] -= 2;
						Dfs(r - 8, t + 1);
						cnt[j] += 2, cnt[k] += 2;
					} if (cnt[j] && cnt[k]) {
						--cnt[j], --cnt[k];
						Dfs(r - 6, t + 1);
						++cnt[j], ++cnt[k];
					}
				} cnt[i] += 4;
			} if (cnt[i] >= 3 && cnt[j] >= 2) {
				cnt[i] -= 3, cnt[j] -= 2;
				Dfs(r - 5, t + 1);
				cnt[i] += 3, cnt[j] += 2;
			} if (cnt[i] >= 3 && cnt[j]) {
				cnt[i] -= 3, --cnt[j];
				Dfs(r - 4, t + 1);
				cnt[i] += 3, ++cnt[j];
			}
		}
		if (cnt[i] >= 4) {
			cnt[i] -= 4; Dfs(r - 4, t + 1); cnt[i] += 4;
		} if (cnt[i] >= 3) {
			cnt[i] -= 3;
			if (sk) {
				sk = 0; Dfs(r - 4, t + 1); sk = 1;
			} if (lk) {
				lk = 0; Dfs(r - 4, t + 1); lk = 1;
			} Dfs(r - 3, t + 1); cnt[i] += 3;
		}
	}
	int sk0 = sk, lk0 = lk;
	if (sk && lk) {
		sk = lk = 0; ++t;
	} for (int i = 2; i <= 14; i++) {
		t += cnt[i] / 2 + (cnt[i] & 1);
	}
	t += sk + lk;
	if (t < ans) ans = t;
	sk = sk0, lk = lk0;
}
