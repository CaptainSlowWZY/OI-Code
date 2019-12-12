#include <algorithm>
#include <cstdio>
#include <vector>

const int kMaxn = 1e5 + 5;

int n, size;
int T[kMaxn * 51][11], sum[kMaxn * 51];
std::vector<int> tim[kMaxn * 51];
char S[55];

int main() {
	scanf("%d", &n);
	for (int a, b, c, la = 0, t = 1, op; t <= n; ++t) {
		scanf("%d%s", &op, S);
		if (op == 1) {
			for (int c, rt = 0, i = 0; S[i]; ++i) {
				if (!T[rt][c = S[i] - 'a']) T[rt][c] = ++size;
				rt = T[rt][c];
				if (++sum[rt] > (int)tim[rt].size()) tim[rt].push_back(t);
			}
		} else if (op == 2) {
			for (int rt = 0, i = 0; S[i]; ++i) { rt = T[rt][S[i] - 'a']; --sum[rt]; }
		} else if (op == 3) {
			scanf("%d%d%d", &a, &b, &c);
			a = (1ll * a * abs(la) + b) % c;
			int rt = 0;
			for (int i = 0; S[i]; ++i) rt = T[rt][S[i] - 'a'];
			printf("%d\n", la = (int)tim[rt].size() <= a ? -1 : tim[rt][a]);
		}
	} return 0;
}
