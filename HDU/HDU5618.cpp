#include <cstdio>
#include <cctype>
#include <algorithm>

const int kMaxn = 1e5 + 10;

struct Point {
	int x, y, z, id;
	bool operator<(const Point & p) const {
		return z == p.z ? 
				(x == p.x ? y < p.y : x < p.x) :
				z < p.z;
	}
	bool operator==(const Point & p) const {
		return x == p.x && y == p.y && z == p.z;
	}
} P[kMaxn];

int n, ans[kMaxn], Maxy;

namespace fast_io {
	template <typename T>
		void Read(T & x) {
			register char ch = getchar();
			register bool f = false; x = 0;
			for (; !isdigit(ch); f |= (ch == '-'), ch = getchar());
			for (; isdigit(ch); ch = getchar())
				x = (x << 3) + (x << 1) + (ch ^ '0');
			f ? x = -x : 0;
		}
	template <typename T>
		void Print(T x) {
			if (!x) return (void)(putchar('0'));
			if (x < 0) x = -x, putchar('-');
			register int arr[20], len = 0;
			for (; x; arr[len++] = x % 10, x /= 10);
			while (len) putchar(arr[--len] ^ '0');
		}
	template <>
		void Print(const char * buff) {
			for (register int i = 0; buff[i]; ++i) putchar(buff[i]);
		}
	template <typename T>
		inline void Println(T x) {
			Print(x), putchar('\n');
		}
}
void Solve(int l, int r);

int main() {
	using fast_io::Read;

	int t;
	for (Read(t); t--; ) {
		Read(n);
		for (int i = 0; i < n; i++) {
			Read(P[i].x), Read(P[i].y), Read(P[i].z);
			Maxy = std::max(Maxy, P[i].y);
			P[i].id = i;
		}

		std::sort(P, P + n);
		Solve(0, n);
		for (int i = n - 2, cnt = 0; i >= 0; i--) {
			P[i] == P[i + 1] ? ++cnt : cnt = 0;
			ans[P[i].id] += cnt;
		}

		for (int i = 0; i < n; i++) {
			fast_io::Println(ans[i]);
			ans[i] = 0;
		}
	}

	return 0;
}

namespace bit {
	int T[kMaxn];

	void Add(int p, int d = 1) {
		for (; p <= Maxy; p += p & -p) {
			T[p] += d;
		}
	}
	int Sum(int p) {
		int ret = 0;
		for (; p; p &= p - 1) {
			ret += T[p];
		}
		return ret;
	}
}

void Solve(int l, int r) {
	if (r - l <= 1) return;
	int mid = l + r >> 1;
	Solve(l, mid);
	Solve(mid, r);
	int p1 = l, p2 = mid, p3 = l;
	static Point buf[kMaxn];
	for (; p1 < mid && p2 < r; ) {
		using namespace bit;
		if (P[p1].x <= P[p2].x) {
			Add(P[p1].y);
			buf[p3++] = P[p1++];
		}
		else {
			ans[P[p2].id] += Sum(P[p2].y);
			buf[p3++] = P[p2++];
		}
	}
	for (; p2 < r; ) {
		ans[P[p2].id] += bit::Sum(P[p2].y);
		buf[p3++] = P[p2++];
	}
	for (int i = l; i < p1; i++) {
		bit::Add(P[i].y, -1);
	}
	for (; p1 < mid; ) {
		buf[p3++] = P[p1++];
	}
	for (int i = l; i < r; i++) {
		P[i] = buf[i];
	}
}
