#include <bits/stdc++.h>

int main() {
	int N, A, B, cnta, cntb, cntc;
	cnta = cntb = cntc = 0;
	scanf("%d%d%d", &N, &A, &B);
	for (int i = 0, Pi; i < N; i++) {
		scanf("%d", &Pi);
		if (Pi <= A) ++cnta;
		else if (Pi <= B) ++cntb;
		else ++cntc;
	}

	printf("%d\n", std::min(cnta, std::min(cntb, cntc)));
	return 0;
}
