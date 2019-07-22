#include <cstdio>
#include <vector>

#define pb push_back

int np[2005], P[2005];
int n, totp, tote;
std::vector<int> G[1005];

void Print() {
	printf("%d\n", tote);
	for (int i = 1; i <= n; i++) {
		for (auto v : G[i]) printf("%d %d\n", i, v);
	}
}

int main() {
	for (int i = 2; i <= 2000; i++) {
		if (!np[i]) P[totp++] = i;
		for (int j = 0, d; j < totp && (d = i * P[j]) <= 2000; j++) {
			np[d] = 1;
		}
	}
	scanf("%d", &n);

	for (int i = 1; i < n; i++) {
		++tote;
		G[i].pb(i + 1);
	}
	++tote, G[n].pb(1);
	int k = 0;
	for (; k < totp && P[k] < n; k++);
	if (P[k] == n) {
		Print();
		return 0;
	}
	int del = P[k] - n;
	for (int i = 1; i <= n / 2 && del--; i++) {
		++tote;
		G[i].pb(i + n / 2);
	}
	Print();
	return 0;
}
