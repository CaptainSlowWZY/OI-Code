// beatall
#include <cstdio>
#include <utility>
   
#define rg register
#define gch getchar
#define pch putchar
#define fir first
#define sec second
 
typedef long long LL;
typedef std::pair<int, int> Pii;
   
const int MAXN = 1e6 + 10;
   
int N, Q[MAXN];
Pii A[MAXN];
 
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
inline Pii operator-(const Pii & v1, const Pii & v2) {
    return Pii(v1.fir - v2.fir, v1.sec - v2.sec);
}
inline LL operator*(const Pii & v1, const Pii & v2) {
    return (LL)v1.fir * v2.sec - (LL)v1.sec * v2.fir;
}
inline bool over(const Pii & p1, const Pii & p2, const Pii & now) {
    return (p2 - p1) * (now - p1) >= 0;
}
   
int main() {
    using FastIO::read;
   
    read(N);
    for (int i = 0; i < N; i++) read(A[i].fir), read(A[i].sec);
   
    int top = 0;
    for (int i = 0; i < N; i++) {
    	// while (top && A[Q[top - 1]].sec <= A[i].sec) --top;
        while (top > 1 && over(A[Q[top - 2]], A[Q[top - 1]], A[i])) --top;
		if (top == 1 && A[Q[top - 1]].sec <= A[i].sec) --top;
        if (!top) FastIO::writeln(i + 1);
        else FastIO::writeln(Q[top - 1] + 1);
        Q[top++] = i;
    }
    return 0;
}
  
/*
7
1 10
2 7
3 8
4 2
5 6
6 100
7 10
*/
   
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

// AC!!!