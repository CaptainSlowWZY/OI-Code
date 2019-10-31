#include <cstdio>
#include <queue>

#define SZ(_) (int)_.size()

const int kMaxn = 3e5 + 5;

int n, A[kMaxn], B[kMaxn];
long long k;
std::priority_queue<int> H;

int main() {
	scanf("%d%lld", &n, &k);
	for (int i = 0, pi; i < n; ++i) {
		scanf("%d", &pi); A[--pi] = -n + i;
	}
	for (int i = 0, qi; i < n; ++i) {
		scanf("%d", &qi);
		if (k >= --qi) { B[qi] = 0; k -= qi; continue; }
		if (k) {
			for (int j = 0; j < qi; ++j) {	
				if (SZ(H) < k) H.push(A[j]);
				else if (A[j] < H.top()) {
					H.pop(); H.push(A[j]);
				}
			} B[qi] = -H.top() - 1;
		} else B[qi] = n;
		for (++i; i < n; ++i) { scanf("%d", &qi); B[--qi] = n; }
	} puts("Yes");
	for (int i = 0; i < n; ++i) printf("%d%c", A[i], " \n"[i + 1 == n]);
	for (int i = 0; i < n; ++i) printf("%d%c", B[i], " \n"[i + 1 == n]);
	return 0;
}
