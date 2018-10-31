// LOJ 6282
// Bucket Method
#pragma GCC optimize(2)
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <utility>
#include <list>

#ifdef DEBUG_MD
	#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define debug(format, ...) 0
#endif
#define fir first
#define sec second
#define pb push_back
#define pf push_front
#define GCH getchar
#define RG register

typedef std::list<int> Block;
typedef std::list<Block> Blocks;
typedef std::pair<Blocks::iterator, Block::iterator> P;

int N, bsz;
Block now;
Blocks blks;

namespace FastIO {
	template <typename T>
		void read(T & x);
	template <typename T>
		void write(T x);
	template <typename T>
		inline void writeln(T x) {
			write(x), putchar('\n');
		}
}
P jump(int pos) {
	Blocks::iterator it = blks.begin();
	for (; it != blks.end() && it->size() < pos; ++it) pos -= (int)it->size();
	Block::iterator itt = it->begin();
	debug(" jumping: pos=%d\n", pos);
	for (--pos; pos--; ++itt);
	return P(it, itt);
}

int main() {
	using FastIO::read;

	read(N);
	bsz = floor(sqrt(N));
	for (int i = 1, ai; i <= N; i++) {
		read(ai);
		now.pb(ai);
		if ((int)now.size() == bsz) {
			blks.pb(now);
			now.clear();
		}
	}
	blks.pb(now);

	for (int cs = 0, opt, l, r, c; cs < N; cs++) {
		read(opt), read(l), read(r), read(c);
		debug("opt%d, l=%d, r=%d, c=%d\n", opt, l, r, c);
		if (opt) {
			FastIO::writeln(*jump(r).sec);
		}
		else {
			P p = jump(l);
			if (p.sec == p.fir->end()) p.fir->pb(r);
			else p.fir->insert(p.sec, r);
			if (p.fir->size() > 2 * bsz) {
				now.clear();
				for (; p.fir->size() > bsz; p.fir->pop_back()) now.pf(p.fir->back());
				blks.insert(++p.fir, now);
			}
		}
	}

	return 0;
}

namespace FastIO {
	template <typename T>
		void read(T & x) {
			RG char ch = GCH(); RG int f = 0;
			for (; ch < '0' || ch > '9'; ch = GCH()) f |= ch == '-';
			for (x = 0; ch >= '0' && ch <= '9'; ch = GCH()) x = (x << 3) + (x << 1) + (ch ^ '0');
			f ? (x = ~x + 1) : 0;
		}
	template <typename T>
		void write(T x) {
			if (!x) return (void)putchar('0');
			if (x < 0) x = -x, putchar('-');
			RG int arr[20], len = 0;
			for (; x; x /= 10) arr[len++] = x % 10;
			while (len) putchar(arr[--len] ^ '0');
		}
}
