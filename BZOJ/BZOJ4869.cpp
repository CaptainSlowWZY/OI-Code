#include <algorithm>
#include <cstdio>

typedef long long LL;
typedef int IAR[50][10010];

const int kMaxn = 5e4 + 5;

int n, m, P, C, lim;
int A[kMaxn], ph[50];
IAR pw1, pw2, cr1, cr2;

namespace smt {
    int Build(int, int);
    int Query(int, int, int, int);
    void Modify(int, int, int, int);
}
int Phi(int);

int main() {
    scanf("%d%d%d%d", &n, &m, &P, &C);
    for (int i = 1; i <= n; i++) scanf("%d", A + i);
    
    ph[0] = P;
    for (; ph[lim] > 1; ++lim) ph[lim + 1] = Phi(ph[lim]);
	ph[++lim] = 1;
    smt::Build(1, n);
    for (int i = 0; i <= lim; i++) {
        pw1[i][0] = pw2[i][0] = 1;
		LL tmp;
        for (int j = 1; j <= 10000; j++) {
            tmp = (LL)pw1[i][j - 1] * C;
			if (tmp >= ph[i]) {
				tmp %= ph[i], cr1[i][j] = 1;
			}
			pw1[i][j] = tmp, cr1[i][j] |= cr1[i][j - 1];
		}
        pw2[i][1] = pw1[i][10000], cr2[i][1] = cr1[i][10000];
        for (int j = 2; j <= 10000; j++) {
            tmp = (LL)pw2[i][j - 1] * pw2[i][1];
			if (tmp >= ph[i]) {
				tmp %= ph[i], cr2[i][j] = 1;
			}
			pw2[i][j] = tmp, cr2[i][j] |= cr2[i][j - 1];
		}
    }

    for (int t, l, r; m--; ) {
        scanf("%d%d%d", &t, &l, &r);
        if (t) printf("%d\n", smt::Query(1, n, l, r));
        else smt::Modify(1, n, l, r);
    }
    return 0;
}

int Phi(int n0) {
    if (n0 == 1) return 0;
    int res = 1, n = n0;
    for (int i = 2; i * i <= n0 && i <= n; i++) {
        if (n % i) continue;
        for (res *= i - 1, n /= i; !(n % i); res *= i, n /= i);
    }
    return res * (n > 1 ? n - 1 : 1);
}

int flag;

int FPowc(int ex, int k) {
	int a = ex / 10000, b = ex % 10000;
	LL res = 1ll * pw2[k][a] * pw1[k][b];
	flag = cr2[k][a] | cr1[k][b];
	if (res >= ph[k]) {
		res %= ph[k];
		flag |= 1;
	}
	return res;
}

int Calc(int x, int k, int lm) {
	flag = 0;
	if (k == lm) {
		if (x >= ph[k]) {
			flag = 1; x %= ph[k];
		}
		return x;
	}
	int tmp = Calc(x, k + 1, lm);
	return FPowc(flag ? tmp + ph[k + 1] : tmp, k);
}

namespace smt {
    struct Node {
        int cnt, sum;
    } T[kMaxn << 1];

    inline int Id(int l, int r) { return l + r | l != r; }
    int Build(int l, int r) {
        int cur = Id(l, r); T[cur].cnt = 0;
        if (l == r) return T[cur].sum = A[l] % P;
        int mid = l + r >> 1;
        return 
            T[cur].sum = (Build(l, mid) + Build(mid + 1, r)) % P;
    }
    int Query(int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return T[Id(l, r)].sum;
        int res = 0, mid = l + r >> 1;
        if (ql <= mid) (res += Query(l, mid, ql, qr)) %= P;
        if (qr > mid) (res += Query(mid + 1, r, ql, qr)) %= P;
        return res;
    }
    void Modify(int l, int r, int ql, int qr) {
        int cur = Id(l, r);
        if (T[cur].cnt >= lim) return;
        if (l == r) {
            ++T[cur].cnt, T[cur].sum = Calc(A[l], 0, T[cur].cnt);
            return;
        }
        int mid = l + r >> 1, ls = Id(l, mid), rs = Id(mid + 1, r);
        if (ql <= mid) Modify(l, mid, ql, qr);
        if (qr > mid) Modify(mid + 1, r, ql, qr);
        T[cur].cnt = std::min(T[ls].cnt, T[rs].cnt);
        T[cur].sum = (T[ls].sum + T[rs].sum) % P;
    }
}
