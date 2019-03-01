#include <cstdio>
#include <cstring>
#include <algorithm>

const int kMaxn = 2e5 + 10, kINF = 0x3f3f3f3f;

int N, Q;
char A[2][kMaxn];

namespace segt {
	struct Node {
		int dist[2][2];
		Node() {
			memset(dist, 0x3f, sizeof dist);
		}
		friend Node Merge(const Node & n1, const Node & n2, int mid) {
			Node ret;
			for (int i = 0; i < 2; i++)
				for (int j = 0; j < 2; j++)
					ret.dist[i][j] = std::min(
							ret.dist[i][j],
							std::min(n1.dist[i][0] + n2.dist[0][j] + 1, n1.dist[i][1] + n2.dist[1][j] + 1));
			return ret;
		}
	} T[kMaxn << 1];
	int QL, QR;

	const Node & Build(int l, int r);
	Node Q(int l, int r);
	inline int Query(int x1, int l, int x2, int r) {
		QL = l, QR = r;
		return Q(1, N).dist[x1][x2];
	}
}

int main() {
	scanf("%d%d%s%s", &N, &Q, A[0] + 1, A[1] + 1);
	for (int i = 1; i <= N; i++) {
		A[0][i] ^= '0';
		A[1][i] ^= '0';
	}

	segt::Build(1, N);
	for (int x1, x2, y1, y2, ret; Q--; ) {
		scanf("%d%d", &x1, &x2);
		y1 = x1 - (x1 - 1) / N * N;
		y2 = x2 - (x2 - 1) / N * N;
		x1 = (x1 - 1) / N;
		x2 = (x2 - 1) / N;
		if (y1 > y2) {
			std::swap(x1, x2);
			std::swap(y1, y2);
		}
		ret = segt::Query(x1, y1, x2, y2);
		if (ret == kINF) puts("You have been confusional!");
		else printf("%d\n", ret);
	}

	return 0;
}

namespace segt {
	inline int Id(int l, int r) {
		return l + r | l != r;
	}
	const Node & Build(int l, int r) {
		int cur = Id(l, r);
		if (l == r) {
			if (!A[0][l]) T[cur].dist[0][0] = 0;
			if (!A[1][l]) T[cur].dist[1][1] = 0;
			if (!(A[0][l] + A[1][l]))
				T[cur].dist[1][0] = T[cur].dist[0][1] = 1;
			return T[cur];
		}
		int mid = l + r >> 1;
		return T[cur] = Merge(Build(l, mid), Build(mid + 1, r), mid);
	}
	Node Q(int l, int r) {
		if (QL <= l && r <= QR) return T[Id(l, r)];
		int mid = l + r >> 1;
		if (QL <= mid && QR > mid) return Merge(Q(l, mid), Q(mid + 1, r), mid);
		else if (QL <= mid) return Q(l, mid);
		return Q(mid + 1, r);
	}
}
