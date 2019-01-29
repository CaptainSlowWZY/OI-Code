// BZOJ 1007
#include <cstdio>
#include <cmath>
#include <algorithm>

const int MAXN = 5e4 + 5;
const double EPS = 1e-7;

struct Line {
	int k, b, id;
	Line() {}
	Line(int k_, int b_, int id_) : k(k_), b(b_), id(id_) {}
	bool operator<(const Line & l) const {
		return k ^ l.k ? k < l.k : b < l.b;
	}
	friend double Lintersecx(const Line & l1, const Line & l2) {
		return double(l2.b - l1.b) / double(l1.k - l2.k);
	}
	friend bool parl(const Line & l1, const Line & l2) {
		return l1.k == l2.k;
	}
} L[MAXN], stc[MAXN];

int N, top;

inline bool cmp(const Line & l1, const Line & l2) {
	return l1.id < l2.id;
}
inline bool le(double x, double y) {
	return x < y ? true : fabs(x - y) < EPS;
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d%d", &L[i].k, &L[i].b);
		L[i].id = i + 1;
	}

	std::sort(L, L + N);
	int top = 0;
	for (int i = 0; i < N; i++) {
		while (top > 0 && parl(stc[top - 1], L[i]) || top > 1 && le(Lintersecx(stc[top - 1], L[i]), Lintersecx(stc[top - 1], stc[top - 2]))) --top;
		stc[top++] = L[i];
	}
	std::sort(stc, stc + top, cmp);
	
	for (int i = 0; i < top; i++) printf("%d ", stc[i].id);
	putchar('\n');

	return 0;
}
