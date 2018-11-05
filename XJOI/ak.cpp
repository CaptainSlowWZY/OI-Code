#include <cstdio>

#ifdef DEBUG_MD
	#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define debug(format, ...) 0
#endif
#define rg register
#define gch getchar
#define pch putchar

const int MAXN = 1 << 21;

int N, exs[MAXN];

namespace FastIO {
	template <typename T>
		void read(T & x);
	template <typename T>
		void write(T x);
	template <typename T>
		inline void writeln(T x) {
			write(x), pch('\n');
		}
}
void insert(int);
int find(int);

int main() {
	using FastIO::read;

	read(N);
	int _xor = 0;
	exs[0] = 1;
	for (int i = 0, ai; i < N; i++) {
		read(ai);
		_xor ^= ai;
		FastIO::writeln(find(_xor));
		insert(_xor);
	}

	return 0;
}

void insert(int val) {
	if (exs[val]) return;
	exs[val] = 1;
	for (int i = 0; i <= 20; i++)
		if (val >> i & 1) insert(val ^ (1 << i));
}

int find(int val) {
	int ret = 0, now = 0;
	for (int i = 20; i >= 0; i--) {
		if (val >> i & 1) {
			ret |= 1 << i;
			continue;
		}
		if (exs[now | 1 << i]) ret += 1 << i + 1, now |= 1 << i;
	}
	return ret;
}

namespace FastIO {
	template <typename T>
		void read(T & x) {
			rg char ch = gch();
			for (; ch < '0' || ch > '9'; ch = gch());
			for (x = 0; ch >= '0' && ch <= '9'; x = (x << 3) + (x << 1) + (ch ^ '0'), ch = gch());
		}
	template <typename T>
		void write(T x) {
			if (!x) return (void)pch('0');
			if (x < 0) x = -x, pch('-');
			rg int arr[20], len = 0;
			for (; x; x /= 10) arr[len++] = x % 10;
			while (len) pch(arr[--len] ^ '0');
		}
}
