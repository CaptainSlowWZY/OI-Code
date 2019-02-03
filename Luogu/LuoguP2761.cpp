// Luogu P2761
#include <cstdio>
#include <cstring>
#include <queue>

const int MAXM = (1 << 20) + 10;

typedef int IntAr[105];

int N, M, DP[MAXM], in_que[MAXM];
IntAr T, B1, B2, F1, F2;
char S[25];
std::queue<int> que;

int main() {
	scanf("%d%d", &N, &M);
	int all = (1 << N) - 1;
	for (int i = 0; i < M; i++) {
		scanf("%d%s", T + i, S);
		for (int j = 0; j < N; j++) {
			if (S[j] == '+') B1[i] |= 1 << j;
			else if (S[j] == '-') B2[i] |= 1 << j;
		}
		scanf("%s", S);
		F1[i] = all;
		for (int j = 0; j < N; j++) {
			if (S[j] == '-') F1[i] ^= 1 << j;
			else if (S[j] == '+') F2[i] |= 1 << j;
		}
	}

	memset(DP, 0x3f, sizeof DP);
	for (DP[all] = 0, que.push(all), in_que[all] = 1; !que.empty(); ) {
		int mask = que.front(); que.pop();
		for (int i = 0; i < M; i++)
			if ((B1[i] & mask) == B1[i] && !(mask & B2[i])) {
				int nxt = mask & F1[i] | F2[i];
				if (DP[nxt] > DP[mask] + T[i]) {
					DP[nxt] = DP[mask] + T[i];
					if (!in_que[nxt]) que.push(nxt), in_que[nxt] = 1;
				}
			}
		in_que[mask] = 0;
	}

	printf("%d\n", DP[0] == 0x3f3f3f3f ? 0 : DP[0]);
	return 0;
}
