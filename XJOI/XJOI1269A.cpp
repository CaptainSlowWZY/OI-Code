#include <cstdio>

typedef long long LL;

int n, d, S[1000010];

inline LL Sq(LL x) { return x * x; }

int main() {
	scanf("%d%d", &n, &d);
	for (int i = 1; i <= n; ++i) scanf("%d", S + i);
	LL ssr = 0, sxr = 0, ssl = 0, sxl = 0, sr = 0, sl = 0;
	for (int i = 1; i <= d; ++i) {
		sr += Sq(d - i + 1) * S[i];
		sxr += (i - 1) * S[i];
		ssr += S[i];
	}
/*	printf(" pos1 sumR %lld, sumR x*si %lld, sumR si%lld\n", 
			sr, sxr, ssr);*/
	LL ans = sr;
	for (int i = 2; i <= n; ++i) {
		sl -= 2ll * (d * ssl - sxl) - ssl;
		sxl += ssl;
//		printf(" i = %d, UPD sl <- %lld, sxl <- %lld\n", i, sl, sxl);
		if (i - d - 1 > 0) {
			ssl -= S[i - d - 1];
			sxl -= d * S[i - d - 1];
//			printf("   dec %d ssl <- %lld, sxl <- %lld\n", i - d - 1, ssl, sxl);
		}
		sl += Sq(d) * S[i - 1];
		ssl += S[i - 1];
		sr -= Sq(d) * S[i - 1];
		ssr -= S[i - 1];
		sr += 2ll * (d * ssr - sxr) + ssr;
		sxr -= ssr;
/*		printf(" pos%d sumL %lld, sumL x*si %lld, sumL si%lld,", 
				i, sl, sxl, ssl);
		printf(" sumR %lld, sumR x*si %lld, sumR si%lld\n", 
				sr, sxr, ssr);*/
		if (i + d - 1 <= n) {
			ssr += S[i + d - 1];
			sr += S[i + d - 1];
			sxr += (d - 1) * S[i + d - 1];
//			printf("   inc %d\n", i + d - 1);
		}
/*		printf(" pos%d sumL %lld, sumL x*si %lld, sumL si%lld,", 
				i, sl, sxl, ssl);
		printf(" sumR %lld, sumR x*si %lld, sumR si%lld\n\n", 
				sr, sxr, ssr); */
		if (sl + sr > ans)
			ans = sl + sr;
	} printf("%lld\n", ans);
	return 0;
}
