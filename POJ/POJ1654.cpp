#include <cstdio>
#include <algorithm>

const int DRC[10][2] = {{0, 0}, {1, -1}, {1, 0}, {1, 1}, {0, -1}, {0, 0}, {0, 1}, {-1, -1}, {-1, 0}, {-1, 1}};

char IN[1000010];

int main() {
    int t;
    scanf("%d", &t);
    for (; t--; ) {
        scanf("%s", IN);
        long long ret = 0, x0, y0, x1, y1;
        x0 = y0 = 0;

        for (int i = 0; IN[i] != '5'; i++, x0 = x1, y0 = y1) {
            x1 = x0 + DRC[IN[i] ^ '0'][0], y1 = y0 + DRC[IN[i] ^ '0'][1];
            ret += x0 * y1 - y0 * x1;
        }
        if (ret < 0) ret = -ret;
        printf("%lld", ret >> 1);
        if (ret & 1) puts(".5");
        else putchar('\n');
    }
    return 0;
}