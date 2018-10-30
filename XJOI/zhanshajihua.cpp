// zhanshajihua
#include <cstdio>
#include <algorithm>

#ifdef DEBUG_MD
	#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define debug(format, ...) 0
#endif
#define RG register

const int MAXATK = 3e4 + 5;

int N, M, cnt[MAXATK];

namespace FastIO {
	template <typename T>
		void read(T & x) {
			RG char ch = getchar();
			for (; ch < '0' || ch > '9'; ch = getchar());
			for (x = 0; ch >= '0' && ch <= '9'; x = (x << 3) + (x << 1) + (ch ^ '0'), ch = getchar());
		}
}

int main() {
#if !defined(LOCAL) && !defined(ONLINE_JUDGE)
	freopen("zhanshajihua.in", "r", stdin);
	freopen("zhanshajihua.out", "w", stdout);
#endif
	using FastIO::read;

	read(N), read(M);
	int mxai = 0;
	for (RG int i = 0, ai; i < N; i++) {
		read(ai);
		++cnt[ai], mxai = std::max(mxai, ai);
	}

	int ans = 0;
	if (cnt[1] + 2 * cnt[2] + 3 * cnt[3] >= M) {
		debug("cnt[1]=%d, cnt[2]=%d, cnt[3]=%d\n", cnt[1], cnt[2], cnt[3]);
		if (cnt[2] * 2 >= M) ans = (M + 1) / 2;
		else if (cnt[1] + 2 * cnt[2] >= M) ans = M - cnt[2];
		else {
			ans = cnt[1] + cnt[2] + (M - cnt[1] - cnt[2] * 2 + 2) / 3 * 4;
			int atk = cnt[1] + cnt[2] * 2 + (M - cnt[1] - cnt[2] * 2 + 2) / 3 * 3;
			while (atk > M && cnt[1] > 0) --atk, --ans, --cnt[1];
		}
		printf("0 %d\n", ans);
	}
	else {
		int tot = 0, f = 1;
		for (int i = 4; i <= mxai; i += 3) {
			++tot;
			cnt[1] += cnt[i], cnt[2] += cnt[i + 1], cnt[3] += cnt[i + 2];
			if (cnt[1] + 2 * cnt[2] + 3 * cnt[3] >= M) {
				if (cnt[2] * 2 >= M) ans = (M + 1) / 2;
				else if (cnt[1] + 2 * cnt[2] >= M) ans = M - cnt[2];
				else {
					debug(" cnt1=%d, cnt2=%d, M - cnt1 - cnt2 * 2=%d \n", cnt[1], cnt[2], M - cnt[1] - cnt[2] * 2), ans = cnt[1] + cnt[2] + (M - cnt[1] - cnt[2] * 2 + 2) / 3 * 4;
					int atk = cnt[1] + cnt[2] * 2 + (M - cnt[1] - cnt[2] * 2 + 2) / 3 * 3;
					while (atk > M && cnt[1] > 0) --atk, --ans, --cnt[1];
				}
				printf("%d %d\n", tot, tot + ans);
				f = 0;
				break;
			}
		}
		if (f) puts("-1");
	}
	
#if !defined(LOCAL) && !defined(ONLINE_JUDGE)
	fclose(stdin); fclose(stdout);
#endif
	return 0;
}
