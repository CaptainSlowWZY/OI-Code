#include <cstdio>
#include <vector>

int n;

int main() {
	int t;
	for (scanf("%d", &t); t--; ) {
		scanf("%d", &n);
		int s = 0;
		for (int x = n; x; x /= 10) s += x % 10;

		std::vector<int> ans;
		for (int i = 1; i <= s; i++) {
			if (s % i || n % i) continue;
			ans.push_back(i);
		} printf("%d\n", (int)ans.size());
		for (int i = 0; i < (int)ans.size(); i++)
			printf("%d%c", ans[i],
				i + 1 == (int)ans.size() ? '\n' : ' ');
	} return 0;
}
