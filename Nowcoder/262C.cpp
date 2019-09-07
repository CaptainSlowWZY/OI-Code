#include <cctype>
#include <cstdio>
#include <vector>

#define GCH getchar()
#define PCH putchar
#define RG register

typedef long long LL;

const int kMaxn = 105, kMod1 = 1e4 + 7, kMod2 = 998244353;

int n, m;
char S[10005];
int vis[kMod1 + 5];
LL A[kMaxn], B[kMaxn];
std::vector<int> ans;

namespace fast_io {
	template <typename T>
		void Read(T & x);
	template <typename T>
		void Print(T x);
	template <typename T> inline
		void Println(T x) {
			Print(x); PCH('\n');
		}
}

int main() {
	using namespace fast_io;
	Read(n); Read(m);
	for (int i = 0; i <= n; i++) {
		char ch = GCH;
		for (; ch != '-' && !isdigit(ch); ch = GCH);
		if (ch != '-' && !isdigit(ch)) printf(" unknow ##%c##\n", ch);
		int f = ch == '-';
		if (f) ch = GCH;
		for (; isdigit(ch); ch = GCH) {
			A[i] = ((A[i] << 1) + (A[i] << 3) + (ch ^ '0')) % kMod1;
			B[i] = ((B[i] << 1) + (B[i] << 3) + (ch ^ '0')) % kMod2;
		} if (f) {
			A[i] = -A[i], B[i] = -B[i];
		}
	}
	for (int x = 0; x < kMod1; x++) {
		LL sum1 = A[n];
		for (int i = n - 1; i >= 0; i--) {
			sum1 = (sum1 * x % kMod1 + A[i]) % kMod1;
		}
		if (!sum1) vis[x] = 1;
	}
	for (int x = 1; x <= m; x++) {	
		if (!vis[x % kMod1]) continue;
		LL sum1 = A[n], sum2 = B[n];
		for (int i = n - 1; i >= 0; i--) {
			sum1 = (sum1 * x % kMod1 + A[i]) % kMod1;
			sum2 = (sum2 * x % kMod2 + B[i]) % kMod2;
		}
		if (!sum1 && !sum2) ans.push_back(x);
	} printf("%d\n", (int)ans.size());
	for (auto i : ans) printf("%d\n", i);
	return 0;
}

namespace fast_io {
	template <typename T>
		void Read(T & x) {
			char ch = GCH; x = 0;
			for (; !isdigit(ch); ch = GCH);
			for (; isdigit(ch); ch = GCH)
				x = (x << 3) + (x << 1) + (ch ^ '0');
		}
	template <typename T>
		void Print(T x) {
			int a[10], len = 0;
			for (; x; x /= 10) a[len++] = x % 10;
			while (len) PCH(a[--len] ^ '0');
		}
}
