// KM Algo template
#include <cstdio>
#include <algorithm>

const int kMaxn = 305, kInf = 0x3f3f3f3f;

typedef int IAr[kMaxn];

int n;
IAr W[kMaxn], lx, ly, match, S, T, slack;

template <typename T>
void Fill(T * arr, int size, T val) {
	for (int i = 0; i < size; i += 4) {
		arr[i] = val, arr[i + 1] = val;
		arr[i + 2] = val, arr[i + 3] = val;
	}
}
bool Dfs(int u);
void Update();

int main() {
	while (~scanf("%d", &n)) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) scanf("%d", &W[i][j]);
		}

		// Km
		for (int i = 0; i < n; i++) {
			lx[i] = ly[i] = 0, match[i] = -1;
			for (int j = 0; j < n; j++) lx[i] = std::max(lx[i], W[i][j]);
		}
		for (int i = 0; i < n; i++) {
			Fill(slack, n, kInf);
			for (; ; Update()) {
				Fill(S, n, 0), Fill(T, n, 0);
				if (Dfs(i)) break;
			}
		}

		int ans = 0;
		for (int i = 0; i < n; i++) ans += W[match[i]][i];

		printf("%d\n", ans);
	}
	
	return 0;
}

void Update() {
	int del = kInf;
	for (int i = 0; i < n; i++) {
		if (T[i]) continue;
		del = std::min(del, slack[i]);
	}
	for (int i = 0; i < n; i++) {
		if (S[i]) lx[i] -= del;
		if (T[i]) ly[i] += del;
	}
}

bool Dfs(int u) {
	S[u] = 1;
	for (int v = 0; v < n; v++) {
		if (T[v]) continue;
		int del = lx[u] + ly[v] - W[u][v];
		if (!del) {
			T[v] = 1;
			if (match[v] == -1 || Dfs(match[v])) {
				match[v] = u;
				return true;
			}
		} else slack[v] = std::min(slack[v], del);
	}
	return false;
}
