#include <cstdio>
#include <cstring>

const int kMaxn = 1e5 + 10;

typedef int IAr[kMaxn];

int n, k;
IAr p, q, a[7], ip, iq, B, IB, buf;

void SetId(int ar[]) {
	for (int i = 1; i <= n; i++) ar[i] = i;
}
void Inv(int ar[], int rs[]) {
	for (int i = 1; i <= n; i++) rs[ar[i]] = i;
}
void Mul(int ar[], int m[]) {
	for (int i = 1; i <= n; i++) buf[i] = ar[m[i]];
	memcpy(ar, buf, sizeof(int) * (n + 1));
}
void Mul(int ar[], int m[], int ret[]) {
	for (int i = 1; i <= n; i++) buf[i] = ar[m[i]];	
	memcpy(ret, buf, sizeof(int) * (n + 1));
}
void FPow(int ar[], int ex);
void Print(int ar[]);

int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) scanf("%d", p + i);
	for (int i = 1; i <= n; i++) scanf("%d", q + i);

	memcpy(a[1], p, sizeof(int) * (n + 1));
	memcpy(a[2], q, sizeof(int) * (n + 1));
	for (int i = 3; i <= 6; i++) {
		Inv(a[i - 2], buf);
		Mul(a[i - 1], buf, a[i]);
	}

	if (k <= 6) {
		Print(a[k]);
		return 0;
	}
	SetId(B);
	Inv(q, iq), Inv(p, ip);
	Mul(B, q), Mul(B, ip), Mul(B, iq), Mul(B, p);
	Inv(B, IB);

	int ex = (k - 1) / 6;
	FPow(B, ex), FPow(IB, ex);
	Mul(B, a[(k - 1) % 6 + 1]), Mul(B, IB);

	Print(B);
	return 0;
}

void FPow(int ar[], int ex) {
	static IAr bs, ret;
	memcpy(bs, ar, sizeof(int) * (n + 1));
	SetId(ret);
	for (; ex; Mul(bs, bs), ex >>= 1)
		if (ex & 1) Mul(ret, bs);
	memcpy(ar, ret, sizeof(int) * (n + 1));
}

void Print(int ar[]) {
	for (int i = 1; i <= n; i++) {
		printf("%d ", ar[i]);
	}
	putchar('\n');
}
