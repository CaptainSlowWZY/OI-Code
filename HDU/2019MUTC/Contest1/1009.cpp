#include <algorithm>
#include <cstdio>
#include <vector>

const int kMaxn = 1e5 + 10;

char S[kMaxn], ans[kMaxn];
int k, len;
int L[26], R[26], cnt[kMaxn][26], used[26], cur[26];
std::vector<int> pos[26];

int main() {
	while (~scanf("%s%d", S, &k)) {
		for (int i = 0; i < 26; i++) pos[i].clear();
		for (len = 0; S[len]; ++len) {
			pos[S[len] -= 'a'].push_back(len);
		}
		for (int i = 0; i < 26; i++) {
			scanf("%d%d", L + i, R + i);
			cnt[len][i] = used[i] = cur[i] = 0;
		}

		for (int i = len - 1; i >= 0; i--) {
			for (int j = 0; j < 26; j++)
				cnt[i][j] = cnt[i + 1][j] + (S[i] == j);
		}
		int nos = 0;
		for (int i = 0, fir = 0, exist; i < k; i++) {
			exist = 0;
			for (int ch = 0; ch < 26; ch++) {
				if (used[ch] == R[ch]) continue;	
				for (; cur[ch] < pos[ch].size() &&
						pos[ch][cur[ch]] < fir; ++cur[ch]);
				if (cur[ch] == pos[ch].size()) continue;
				
				int fail = 0, sum = 0, nxt = pos[ch][cur[ch]];
				for (int j = 0; j < 26; j++) {
					if (cnt[nxt][j] + used[j] < L[j]) {
						fail = 1; break;
					}
					sum += std::max(0, L[j] - used[j] - (j == ch));
				}
				if (sum > k - i - 1) fail = 1;
				for (int j = sum = 0; j < 26; j++) {
					sum += std::min(R[j] - used[j] - (j == ch),
							cnt[nxt + 1][j]);
				}
				if (sum < k - i - 1) fail = 1;
				if (!fail) {
					ans[i] = ch + 'a';
					fir = nxt + 1, ++cur[ch], ++used[ch];
					exist = 1; break;
				}
			}
			if (!exist) {
				nos = 1;
				break;
			}
		}
		if (nos) puts("-1");
		else {
			ans[k] = '\0';
			puts(ans);
		}
	}
	return 0;
}
