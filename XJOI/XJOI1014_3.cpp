// XJOI 1014 3
#include <cstdio>
#include <cstring>
#include <set>
typedef long long LL;
typedef std::set<int> MySt;

const int MAXN = 3010;
const int MOD = 1e8 + 7;
const int A = 0, B = 1, C = 2;

typedef int IntAr[MAXN];

int N;
MySt T;

class Counter {
private:
	struct Cell {
		int rat[3];
		void reset() { memset(rat, 0, sizeof rat); }
		void down() { --rat[0], --rat[1], --rat[2]; }
		void down(int md) { --rat[md]; }
		void up() { ++rat[0], ++rat[1], ++rat[2]; }
		void up(int md) { ++rat[md]; }
		int vld_s() const { return (rat[0] >= 0) + (rat[1] >= 0) + (rat[2] >= 0); }
	} dat[MAXN];
	int cnt[5];
public:
	LL cunt() const;
	void init() {
		memset(dat, 0, sizeof dat);
		memset(cnt, 0, sizeof cnt);
		cnt[3] = T.size();
	}
	void set_vld(int pos, int md) {
		--cnt[dat[pos].vld_s()];
		dat[pos].down(), dat[pos].up(md);
		++cnt[dat[pos].vld_s()];
	}
	void setback_vld(int pos, int md) {
		--cnt[dat[pos].vld_s()];
		dat[pos].up(), dat[pos].down(md);
		++cnt[dat[pos].vld_s()];
	}
	void set_invld(int pos, int md) {
		--cnt[dat[pos].vld_s()];
		dat[pos].down(md);
		++cnt[dat[pos].vld_s()];
	}
	void setback_invld(int pos, int md) {
		--cnt[dat[pos].vld_s()];
		dat[pos].up(md);
		++cnt[dat[pos].vld_s()];
	}
	void Debug(int sp) const;
	friend void set(Counter & c, int bgn, int end, int md);
} Al, Nc;

IntAr num, pow2, pow3;

namespace FastIO {
	template <typename T>
	void read(T & x) {
		x = 0; register char ch = getchar();
		for (; ch < '0' || ch > '9'; ch = getchar());
		for (; ch >= '0' && ch <= '9'; x = (x << 3) + (x << 1) + (ch ^ '0'), ch = getchar());
	}
}
inline void add(LL & x, LL d) { (x += d) %= MOD; }
void init();

// #define _DEBUG_MD_

int main() {
	using FastIO::read;
	read(N);
	init();
	for (int i = 0; i < N; i++) read(num[i]), T.insert(num[i]);
	LL ans = 0;
	for (int i = 0; i < N; i++) { // the first position of character A
#ifdef _DEBUG_MD_
		printf("i=%d\n", i);
#endif
		Al.init(), Nc.init();
		set(Al, 0, i, A), set(Nc, 0, i, A);
		set(Al, i + 1, N, B), set(Nc, i + 1, N, B);
		Al.set_vld(num[i], A), Nc.set_vld(num[i], A);
#ifdef _DEBUG_MD_
		puts(" Debug All:"), Al.Debug(1);
		Al.cunt();
		puts(" Debug NoC:"), Nc.Debug(1);
		Nc.cunt();
#endif
		for (int j = N - 1; j > i; j--) {	// the first position of character B
#ifdef _DEBUG_MD_
			printf("  j=%d\n", j);
#endif
			Al.setback_invld(num[j], B), Nc.setback_invld(num[j], B);
			Al.set_vld(num[j], B), Nc.set_vld(num[j], B);
#ifdef _DEBUG_MD_
			puts("   Debug All:"), Al.Debug(3);
			puts("   Debug NoC:"), Nc.Debug(3);
#endif
			add(ans, (Al.cunt() - Nc.cunt() + MOD) % MOD);
#ifdef _DEBUG_MD_
			printf("   ans_delta=%d\n", Al.cunt() - Nc.cunt());
#endif
			Al.setback_vld(num[j], B), Nc.setback_vld(num[j], B);
			Nc.set_invld(num[j], C);
#ifdef _DEBUG_MD_
			puts("   Debug All:"), Al.Debug(3);
			puts("   Debug NoC:"), Nc.Debug(3);
#endif
		}
	}
	printf("%lld\n", ans);
	return 0;
}

LL Counter::cunt() const {
#ifdef _DEBUG_MD_
	printf("  Debug: cnt0=%d, cnt1=%d, cnt2=%d, cnt3=%d\n", cnt[0], cnt[1], cnt[2], cnt[3]);
#endif
	return cnt[0] ? 0 : (LL)pow2[cnt[2]] * pow3[cnt[3]] % MOD;
}

void init() {
	pow2[0] = pow3[0] = 1;
	for (int i = 1; i <= N; i++) pow2[i] = (LL)pow2[i - 1] * 2 % MOD, pow3[i] = (LL)pow3[i - 1] * 3 % MOD;
}

void set(Counter & c, int bgn, int end, int md) {
	// mode: -1 - free, 0~2 - ABC invalid
	if (~md) {
		for (; bgn < end; ++bgn) c.set_invld(num[bgn], md);
	}
	else {
		for (; bgn < end; ++bgn) {
			int now = num[bgn];
			--c.cnt[c.dat[now].vld_s()];
			c.dat[now].reset();
			++c.cnt[c.dat[now].vld_s()];
		}
	}
}

void Counter::Debug(int sp) const {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < sp; j++) putchar(' ');
		printf("num[%d]=%d: A_val=%d, B_val=%d, C_val=%d, vld_s=%d\n", i, num[i], dat[num[i]].rat[0], dat[num[i]].rat[1], dat[num[i]].rat[2], dat[num[i]].vld_s());
	}
}

// AC!!!