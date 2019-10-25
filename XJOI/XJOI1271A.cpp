#include <cstdio>
#include <map>

int n, m, hd, tl;
int que[100010];
std::map<int, int> mp;

int main() {
	scanf("%d%d", &n, &m);
	for (int o, x, y; n--; ) {
		scanf("%d", &o);
		if (o == 1) {
			scanf("%d", &x);
			que[tl++] = x, ++mp[x];
			if (tl - hd > m) {
				y = que[hd++];
				if (!(--mp[y])) mp.erase(y);
			}
		} else {
			if (mp.empty()) puts("0");
			else printf("%d\n", mp.rbegin()->first - mp.begin()->first);
		}
	} return 0;
}
