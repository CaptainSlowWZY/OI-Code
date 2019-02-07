#include <bits/stdc++.h>

typedef std::multiset<int> MySet;

int N;
char str[(int)5e5 + 10];
MySet L, R;

int main() {
	scanf("%d", &N);
	int tot = 0;
	for (int i = 0; i < N; i++) {
		scanf("%s", str);
		int cnt = 0, low = 0;
		for (int j = 0; str[j]; j++) {
			if (str[j] == '(') ++cnt;
			else low = std::min(low, --cnt);
		}
		if (low < 0) {
			if (cnt > low) continue;
			R.insert(cnt);
		}
		else if (!cnt) ++tot;
		else L.insert(cnt);
	}

	int ans = tot / 2;
	for (MySet::iterator it = R.begin(), itt; it != R.end(); ++it) {
		itt = L.find(-*it);
		if (itt == L.end()) continue;
		++ans, L.erase(itt);
	}
	printf("%d\n", ans);
	return 0;
}
