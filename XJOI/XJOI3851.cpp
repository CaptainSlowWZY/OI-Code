// XJOI 3851
#pragma GCC diagnostic error "-std=c++11"
#include <cstdio>
#include <cstring>
#include <utility>
#include <algorithm>
#include <queue>
#include <cassert>
 
#ifdef DEBUG_MD
	#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define debug(format, ...)
#endif
#define fir first
#define sec second
#define pb push_back

const int MAXN = 105;

typedef int arr[MAXN];
typedef std::pair<int, int> Pii;

arr odgr, oodgr, vis, A[MAXN];
int N;
std::vector<int> G[MAXN];
 
bool check() {
	memset(oodgr, 0, sizeof oodgr);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) oodgr[i] += A[i][j];
		debug(" checking... i: %d, oodgr: %d, odgr: %d\n", i, oodgr[i], odgr[i]);
		if (oodgr[i] != odgr[i]) return false;
	}
	return true;
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) scanf("%d", odgr + i);
     
    std::sort(odgr, odgr + N);
	for (int i = 0; i < N; i++)
		for (int j = i + 1; j < N; j++) A[j][i] = 1, ++oodgr[j];
	std::priority_queue<Pii> hp;
	for (int i = 0; i < N; i++) {
		if (oodgr[i] < odgr[i]) hp.push(Pii(odgr[i] - oodgr[i], i));
		std::vector<Pii> vec;
		for (; oodgr[i] > odgr[i]; ) {
			debug("i=%d, hp.size()=%d\n", i, (int)hp.size());
			if (hp.empty()) { 
//				assert(0); 
				break; 
			}
			Pii now = hp.top(); hp.pop();
			if (A[i][now.sec]) --now.fir, --oodgr[i], A[now.sec][i] = 1, A[i][now.sec] = 0;
			vec.pb(now);
		}
		for (auto pr : vec) 
			if (pr.fir) hp.push(pr);
	}

#ifdef DEBUG_MD
	puts("-----  MAP  -----");
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) debug("%2d", A[i][j]);
		putchar('\n');
	}
	puts("-----  END  -----");
#endif
	assert(check());
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (A[i][j]) G[i].pb(j);
	int ans = 0;
	for (int i = 0; i < N; i++) {
		int tmp = 1;
		std::queue<int> Q;
		memset(vis, 0, sizeof vis);
		for (vis[i] = 1, Q.push(i); !Q.empty(); Q.pop())
			for (auto v : G[Q.front()])
				if (!vis[v]) ++tmp, vis[v] = 1, Q.push(v);
		debug("i=%d, tmp=%d\n", i, tmp);
		ans += tmp;
	}

	printf("%d\n", ans);
    return 0;
}

// AC!!!
