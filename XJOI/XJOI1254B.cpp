// line
#include <algorithm>
// #include <cassert>
#include <cctype>
#include <cmath>
#include <cstdio>
// #include <cstdlib>
#include <cstring>
// #include <ctime>
#include <map>
#include <queue>
#include <set>
#include <vector>
  
#define fir first
#define sec second
#define pb push_back
#define pch putchar
#define rg register
#define SZ(_) (int)_.size()
#define SORT(_) std::sort(_.begin(), _.end())
#define LB(_, __) std::lower_bound(_.begin(), _.end(), __)
#define UB(_, __) std::upper_bound(_.begin(), _.end(), __)
#define int LL


typedef long long LL;
typedef std::pair<int, int> Pii;
typedef std::pair<LL, int> Pli;
typedef std::pair<int, LL> Pil;
typedef std::pair<LL, LL> Pll;
typedef std::pair<double, int> Pdi;
typedef std::vector<int> Vi;
typedef std::vector<LL> Vl;
typedef std::map<int, int> Mii;
typedef std::map<LL, int> Mli;
typedef std::map<int, LL> Mil;
typedef std::map<LL, LL> Mll;
typedef std::set<int> Si;
typedef std::set<LL> Sl;
  
const int kInf = 0x3f3f3f3f, kMod = 1e9 + 7;
const LL kInf64 = 0x3f3f3f3f3f3f3f3f;
const double kPie = acos(-1), kEps = 1e-12;
  
template <typename T> inline
void UMin(T & x, const T & y) { if (x > y) x = y; }
template <typename T> inline
void UMax(T & x, const T & y) { if (x < y) x = y; }
inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + kMod : a; }
inline int Mul(int a, int b) { return 1ll * a * b % kMod; }
int FPow(int bs, int ex = kMod - 2) {
    int res = 1;
    for (; ex; bs = Mul(bs, bs), ex >>= 1)
        if (ex & 1) res = Mul(res, bs);
    return res;
}
  
const int kMaxn = 1e5 + 5;
  
int n;
Pii P[kMaxn];
  
double Find(LL k);
  
signed main() {
    // freopen("test.in", "r", stdin);
    scanf("%lld", &n);
    for (int i = 0; i < n; ++i) scanf("%lld%lld", &P[i].fir, &P[i].sec);
    // fclose(stdin);
    LL m = n * (n - 1) >> 1;
    // printf(" m = %d\n", m);
    if (m & 1) printf("%.10lf\n", Find(m + 1 >> 1));
    else printf("%.10lf\n", (Find(m >> 1) + Find((m >> 1) + 1)) / 2.0);
    return 0;
}
  
namespace bit {
    int cap;
    LL T[kMaxn];
    inline void Init(int sz_) { std::fill(T, T + (cap = sz_) + 1, 0); }
    void Add(int p) { for (; p <= cap; p += p & -p) ++T[p]; }
    LL Sum(int p) { LL res = 0; for (; p; p &= p - 1) res += T[p]; return res; }
}
  
inline bool Equal(double x, double y) {
    return fabs(x - y) < kEps;
}
inline bool CmpPdi(const Pdi & a, const Pdi & b) {
    return Equal(a.fir, b.fir) ? a.sec > b.sec : a.fir > b.fir;
}
  
LL Count(double ang) {
    double si = sin(ang), ta = tan(ang);
    static double Y[kMaxn];
    static Pdi A[kMaxn];
    for (int i = 0; i < n; ++i) Y[i] = P[i].sec / si;
    std::sort(Y, Y + n);
    int ny = std::unique(Y, Y + n, Equal) - Y;
    for (int i = 0; i < n; ++i) {
        A[i] = {P[i].fir - P[i].sec / ta,
            std::lower_bound(Y, Y + ny, P[i].sec / si) - Y};
        // printf(" i %d (%.5lf, %d)\n", i, A[i].fir, A[i].sec);
    }
    std::sort(A, A + n, CmpPdi);
    int res = 0;
    bit::Init(ny);
    for (int i = 0; i < n; ++i) {
        res += bit::Sum(ny - A[i].sec);
        bit::Add(ny - A[i].sec);
    } return res;
}
  
double Find(LL k) {
    double lb = 0, ub = kPie;
    while (fabs(ub - lb) > kEps) {
        double mid = (lb + ub) / 2.0;
        int tmp = Count(mid);
        // printf(" Count %.5lf = %d\n", mid, tmp);
        if (tmp >= k) ub = mid;
        else lb = mid;
    } return lb;
}