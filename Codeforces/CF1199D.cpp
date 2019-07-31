#include<bits/stdc++.h>
using namespace std;

const int N=2e5+10;

int n, q, opt, x, y, a[N];
int pos[N << 2], T[N << 2];

void Build(int l, int r, int k);
void Change(int l, int r, int k, int x, int y);
void Print(int l, int r, int k);

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", a + i);
	scanf("%d",&q);

	Build(1, n, 1);
	for (int i = 1; i <= q; i++) {
		scanf("%d", &opt);
		if (opt == 1) {
			scanf("%d%d", &x, &y);
			Change(1, n, 1, x, y);
		} else {
			scanf("%d",&x);
			pos[1] = max(pos[1], x);
			T[1] = max(T[1], x);	
		}
	}
	Print(1, n, 1);
	putchar('\n');
	return 0;
}

void Build(int l, int r, int k) {
	if (l == r) T[k] = a[l];
	else {
		int mid = l + r >> 1;
		Build(l, mid, k << 1);
		Build(mid + 1, r, k << 1 | 1);
	}
}

void PushDown(int x) {
	if (pos[x] > pos[x << 1]) { 
		pos[x << 1] = pos[x];
		T[x << 1] = max(T[x << 1], pos[x]);
	}
	if (pos[x] > pos[x << 1 | 1]){
		pos[x << 1 | 1] = pos[x];
		T[x << 1 | 1] = max(T[x << 1 | 1], pos[x]);
	}
	pos[x] = 0;
}

void Change(int l, int r, int k, int x, int y) {
	if (l == r) {
		T[k] = y, pos[k] = 0;
	} else {
		int mid = l + r >> 1;
		PushDown(k);
		if (x <= mid) Change(l, mid, k<<1, x, y);
		else Change(mid + 1, r, k << 1 | 1, x, y);
	}
}

void Print(int l, int r, int k) {
	if (l == r) printf("%d ", T[k]);
	else {
		int mid = l + r >> 1;
		PushDown(k);
		Print(l, mid, k << 1);
		Print(mid + 1, r, k << 1| 1);
	}
}
