// Luogu P3370
#include <cstdio>
#include <algorithm>

typedef unsigned long long ULL;

const int MAXN = 1e4 + 5;
const int BS = 26;

int N;
char S[1500];

namespace string_hash {
	int cnt = 0;

	void insert(const char * str);
	void work();
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%s", S);
		string_hash::insert(S);
	}

	string_hash::work();

	printf("%d\n", string_hash::cnt);
	return 0;
}

namespace string_hash {
	ULL hv[MAXN];

	void insert(const char * str) {
		ULL tmp = 0;
		for (int i = 0; str[i]; i++) tmp = tmp * BS + str[i];
		hv[cnt++] = tmp;
	}

	void work() {
		std::sort(hv, hv + cnt);
		cnt = std::unique(hv, hv + cnt) - hv;
	}
}

// AC!!!
