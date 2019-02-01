/* DP[i][j] - time i, disturb j times
 * if get the envelope, -> DP[d[i] + 1][j] = DP[i][j] + w[i]
 * if was disturbed, -> DP[i + 1][j + 1] = DP[i][j]
 * if no envelope, -> DP[i + 1][j] = DP[i][j];
 */
#include <cstdio>
#include <cstring>
#include <utility>
#include <functional>
#include <vector>
#include <map>

#define fir first
#define sec second

typedef std::pair<int, int> Pii;
typedef long long LL;

const int MAXN = 1e5 + 10;
const int MAXM = 205;
const LL INF = 0x3f3f3f3f3f3f3f3f;

struct Envlp {
	int di, wi, in;
};

int N, M, K;
std::map<Pii, int, std::greater<Pii> > Mp;
Pii chos[MAXN];
LL DP[MAXN][MAXM];
std::vector<Envlp> A[MAXN];

inline void upd_min(LL & x, LL y) { x > y ? x = y : 0; }

int main() {
	scanf("%d%d%d", &N, &M, &K);
	for (int i = 0, si, ti, di, wi; i < K; i++) {
		scanf("%d%d%d%d", &si, &ti, &di, &wi);
		A[si].push_back((Envlp){di, wi, 1});
		A[ti + 1].push_back((Envlp){di, wi, 0});
	}

	for (int i = 1; i <= N; i++) {
		for (auto & e : A[i]) {
			Pii tmp(e.wi, e.di);
			if (e.in) ++Mp[tmp];
			else {
				if (!(--Mp[tmp])) Mp.erase(tmp);
			}
		}

		if (Mp.size()) chos[i] = Mp.begin()->fir;
		else chos[i] = Pii(0, i);
	}

	memset(DP, 0x3f, sizeof DP);
	DP[1][0] = 0;
	for (int i = 1; i <= N; i++)
		for (int j = 0; j <= M; j++) {
			upd_min(DP[chos[i].sec + 1][j], DP[i][j] + chos[i].fir);
			if (j < M) upd_min(DP[i + 1][j + 1], DP[i][j]);
		}
	LL ans = INF;
	for (int i = 0; i <= M; i++) upd_min(ans, DP[N + 1][i]);
	
	printf("%lld\n", ans);
	return 0;
}
