#include <cstdio>
#include <set>

typedef long long LL;

const int kMaxn = 1e5 + 10, kLg = 18, kMod = 1e9 + 7;

int n, m, index;
int pw[kLg], id[kMaxn][kLg], fa[kMaxn * kLg], mp[kMaxn * kLg];
std::set<int> s;

int Find(int x) { return fa[x] == x ? x : fa[x] = Find(fa[x]); }
inline void Merge(int x, int y) {
	x = Find(x), y = Find(y); fa[x] = y;
}
LL FPow(LL bs, int ex) {
	LL res = 1;
	for (; ex; (bs *= bs) %= kMod, ex >>= 1) {
		if (ex & 1) (res *= bs) %= kMod;
	} return res;
}

int main() {
	scanf("%d%d", &n, &m);

	for (int i = pw[0] = 1; i < kLg; i++) pw[i] = pw[i - 1] << 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < kLg && i + pw[j] - 1 <= n; j++) {
			mp[id[i][j] = ++index] = i, fa[id[i][j]] = index;
		}
	}
	for (int i = 0, l1, r1, l2, r2, len; i < m; i++) {
		scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
		len = r1 - l1 + 1;
		for (int j = kLg - 1; j >= 0 && l1 <= r1; j--) {
			if (len >> j & 1) {
			//	printf(" merge (%d, %d)(%d) (%d, %d)(%d)\n",
			//			l1, j, id[l1][j], l2, j, id[l2][j]);
				Merge(id[l1][j], id[l2][j]);
				l1 += pw[j], l2 += pw[j];
			}
		}
	}
	for (int i = kLg - 1; i; i--) {
		for (int j = 1, x, y; j + pw[i] - 1 <= n; j++) {
			if ((x = Find(id[j][i])) == id[j][i]) continue;
			y = mp[x];
		//	printf(" 2^(%d) = %d, %d and %d\n", i - 1, pw[i - 1], j, y);
			Merge(id[j][i - 1], id[y][i - 1]);
			Merge(id[j + pw[i - 1]][i - 1], id[y + pw[i - 1]][i - 1]);
		}
	}
	for (int i = 1; i <= n; i++) s.insert(Find(id[i][0]));
//	printf("%d\n", (int)s.size());
	printf("%lld\n", 9ll * FPow(10, (int)s.size() - 1) % kMod);
	return 0;
}
