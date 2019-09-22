#include <cstdio>
#include <map>

#define fir first
#define sec second

typedef long long LL;

const char kAname[] = "sjfnb";
const char kBname[] = "cslnb";
const int kMaxn = 1e5 + 5;

int n;
int A[kMaxn];
std::map<int, int> cnt;

int main() {
	scanf("%d", &n);
	int is0 = 1, cnt0 = 0;
	for (int i = 0; i < n; i++) {
		scanf("%d", A + i);
		if (!A[i]) ++cnt0;
		else is0 = 0;
		++cnt[A[i]];
	}
	int c2 = 0, c3 = 0;
	for (auto & p : cnt) {
		if (p.sec >= 2) {
			++c2;
			if (cnt.count(p.fir - 1)) c3 = 1;
		}
		if (p.sec >= 3) ++c3;
	}
	if (is0 || c2 > 1 || c3 || cnt0 > 1) {
		puts(kBname);
		return 0;
	}
	int cur = 0;
	LL step = 0;
	for (auto & p : cnt) {
		if (!p.sec) continue;
		step += p.fir - cur++;	
		if (p.sec > 1) {
			step += p.fir - cur++;
		}
	}
	puts(step & 1 ? kAname : kBname);
	return 0;
}
