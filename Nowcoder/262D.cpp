#include <cstdio>

const int kMaxn = 205;
const int kBeat[5][5] = {
	{-1, 0, 1, 1, 0},
	{1, -1, 0, 1, 0},
	{0, 1, -1, 0, 1},
	{0, 0, 1, -1, 1},
	{1, 1, 0, 0, -1}
};

int n, na, nb;
int A[kMaxn], B[kMaxn];

int main() {
	scanf("%d%d%d", &n, &na, &nb);
	for (int i = 0; i < na; i++) scanf("%d", A + i);
	for (int i = 0; i < nb; i++) scanf("%d", B + i);

	int srca = 0, srcb = 0;
	for (int i = 0, j = 0, k = 0; i < n; i++) {
		switch (kBeat[A[j]][B[k]]) {
			case 1 : ++srca; break;
			case 0 : ++srcb; break;
		}
		if (++j == na) j = 0;
		if (++k == nb) k = 0;
	} printf("%d %d\n", srca, srcb);
	return 0;
}
