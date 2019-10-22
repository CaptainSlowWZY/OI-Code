#include <algorithm>
#include <cstdio>
#include <cstring>

#define int LL

typedef long long LL;
typedef LL LAr[210];

int n, m1, m2;
LAr cnt1, cnt2, cnt3, cnta, cntb;

void Read(LL cnt[], int n);

signed main() {
	scanf("%lld%lld%lld", &n, &m1, &m2);
	Read(cnt1, n); Read(cnt2, m1); Read(cnt3, m2);
	memcpy(cnta, cnt1, sizeof cnt1);
	memcpy(cntb, cnt2, sizeof cnt2);
	LL ans = 0;
	for (int i = 0; i <= 200; ++i) {
		for (int j = i; j <= 200 && cntb[i]; ++j) {
			LL k = std::min(cnta[j], cntb[i]);
			cnta[j] -= k, cntb[i] -= k;
		} if (cntb[i]) { ans = -1; break; }
	}
	if (!ans) {
		memcpy(cntb, cnt3, sizeof cntb);
		cntb[100] += 100000000000000000ll;
		for (int i = 0; i <= 100; ++i) {
			for (int j = 200; j >= i && cntb[i]; --j) {
				LL k = std::min(cnta[j], cntb[i]);
				ans += (j - i) * k;
				cnta[j] -= k, cntb[i] -= k;
			}
		}
	}
	memcpy(cnta, cnt1, sizeof cnt1);
	memcpy(cntb, cnt3, sizeof cnt3);
	LL sum = 0;
	for (int i = 0; i <= 200; ++i) {
		for (int j = 200; j >= i && cntb[i]; --j) {
			LL k = std::min(cnta[j], cntb[i]);
			sum += (j - i) * k;
			cnta[j] -= k, cntb[i] -= k;
		}
	}
	printf("%lld\n", std::max(sum, ans));
	return 0;
}

void Read(LL cnt[], int n) {
	for (int i = 0, a, x; i < n; ++i) {
		scanf("%lld%lld", &a, &x); cnt[a + 100] += x;
	}
}
