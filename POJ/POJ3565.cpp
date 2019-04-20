#include <cstdio>
#include <cmath>
#include <algorithm>

#define x first
#define y second

const int kMaxn = 105;
const long long kInf64 = 0x3f3f3f3f3f3f3f3f;
const double kInfd = 1e15, kEps = 1e-10;

typedef std::pair<int, int> Pii;
typedef int IAr[kMaxn];
typedef double DAr[kMaxn]; 

int n;
IAr match, S, T;
DAr lc, lt, W[kMaxn], slack;
Pii C[kMaxn], A[kMaxn];

template <typename T>
void Fill(T * arr, int size, T val) {
	for (int i = 0; i < size; i += 4) {
		arr[i] = val, arr[i + 1] = val;
		arr[i + 2] = val, arr[i + 3] = val;
	}
}
inline double Sqr(double x) { return x * x; }
inline double Dist(const Pii & p, const Pii & q) {
	return sqrt(Sqr(p.x - q.x) + Sqr(p.y - q.y));
}

bool Dfs(int);
void Update();

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d%d", &C[i].x, &C[i].y);
	for (int i = 0; i < n; i++) scanf("%d%d", &A[i].x, &A[i].y); 

	for (int i = 0; i < n; i++) {
		lt[i] = 0, match[i] = -1;
		lc[i] = -kInfd;
		for (int j = 0; j < n; j++) {
			W[i][j] = -Dist(C[i], A[j]);
			lc[i] = std::max(lc[i], W[i][j]);
		}
	}
	for (int i = 0; i < n; i++) {
		Fill(slack, n, kInfd);
		for (; ; Update()) {
			Fill(S, n, 0), Fill(T, n, 0);
			if (Dfs(i)) break;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (match[j] == i) {
				printf("%d\n", j + 1);
				break;
			}
		}
	}
	return 0;
}

inline int Sign(double x) {
	return fabs(x) <= kEps ? 0 : (x < 0 ? -1 : 1);
}

bool Dfs(int u) {
	S[u] = 1;
	for (int v = 0; v < n; v++) {
		if (T[v]) continue;
		double del = lc[u] + lt[v] - W[u][v];
		if (!Sign(del)) {
			T[v] = 1;
			if (match[v] == -1 || Dfs(match[v])) {
				match[v] = u;
				return true;
			}
		} else slack[v] = std::min(slack[v], del);
	}
	return false;
}

void Update() {
	double del = kInfd;
	for (int i = 0; i < n; i++) {
		if (!T[i]) del = std::min(del, slack[i]);
	}
	for (int i = 0; i < n; i++) {
		if (S[i]) lc[i] -= del;
		if (T[i]) lt[i] += del;
	}
}
