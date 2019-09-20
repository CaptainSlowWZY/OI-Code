#include <iostream>
#include <queue>
#include <utility>

#define x first
#define y second

using namespace std;

typedef pair<int, int> Pii;

const int kDx[] = {2, 1, 0};
const int kDy[] = {0, 1, 2};

int n;
int A[55][55], vis[55][55];
std::queue<Pii> que;

inline int Ask(int x1, int y1, int x2, int y2) {
	cout << "? " << x1 << ' ' << y1 << ' '
		<< x2 << ' ' << y2 << endl;
	cout.flush();
	int res;
	cin >> res; return res;
}
bool Check(int x1, int y1, int x2, int y2);
void Print();
void Swap();

int main() {
	cin >> n;
	A[1][1] = 1, A[n][n] = 0;
	vis[1][1] = vis[n][n] = 1;
	que.push({1, 1});
	while (!que.empty()) {
		Pii u = que.front(); que.pop();
		for (int i = 0, nx, ny; i < 3; i++) {
			nx = u.x + kDx[i], ny = u.y + kDy[i];
			if (nx <= n && ny <= n && !vis[nx][ny]) {
				vis[nx][ny] = 1;
				que.push({nx, ny});
				A[nx][ny] = A[u.x][u.y] ^ !Ask(u.x, u.y, nx, ny);
			}
		}
	} A[1][2] = 1;
	for (int i = 1, sx = 2; i <= n; i++) {
		for (int j = sx; j + 2 <= n; j += 2)
			A[i][j + 2] = A[i][j] ^ !Ask(i, j, i, j + 2);
		if (sx > 2) {
			A[i][sx - 2] = A[i][sx] ^ !Ask(i, sx - 2, i, sx);
			sx -= 2;
		}
		if (i < n)
			A[i + 1][sx + 1] = A[i][sx] ^ !Ask(i, sx, i + 1, sx + 1);
		++sx;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			for (int k = 0; k < 4; k++) {
				if (i + k <= n && j + 3 - k <= n &&
					Check(i, j, i + k, j + 3 - k)) {
					int r = Ask(i, j, i + k, j + 3 - k);
					if (r && A[i][j] != A[i + k][j + 3 - k]) Swap();
					if (!r && A[i][j] == A[i + k][j + 3 - k]) Swap();
					Print(); return 0;
				}
			}
		}
	} return 0;
}

void Swap() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++)
			if (i + j & 1) A[i][j] ^= 1;
	}
}

void Print() {
	cout << "!" << endl;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++)
			cout << A[i][j];
		cout << endl;
	}
}

bool Check(int x1, int y1, int x2, int y2) {
	if (x1 == x2)
		return !A[x1][y1] ^ A[x1][y1 + 1] ^
			A[x1][y1 + 2] ^ A[x1][y2];
	int t = A[x1][y1] ^ A[x2][y2];
	if (x1 + 1 == x2) {
		return (A[x1][y1 + 1] ^ A[x1][y2]) == t ||
			(A[x1][y1 + 1] ^ A[x2][y1 + 1]) == t ||
			(A[x2][y1] ^ A[x2][y1 + 1]) == t;
	}
	if (x1 + 2 == x2) {
		return (A[x1][y2] ^ A[x1 + 1][y2]) == t ||
			(A[x1 + 1][y1] ^ A[x1 + 1][y2]) == t ||
			(A[x1 + 1][y1] ^ A[x2][y1]) == t;
	}
	return (A[x1 + 1][y1] ^ A[x1 + 2][y1]) == t;
}
