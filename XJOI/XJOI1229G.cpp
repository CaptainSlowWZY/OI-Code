#include <cstdio>
#include <algorithm>
const int ArSize = 1 << 18, INF = 0x7f7f7f7f;
struct Node {
    int val, mark;
    Node() { val = mark = 0; }
};
 
Node tree[ArSize];
int C, S, R, O, D, N;
 
int query(int rt, int l, int r);
void insert(int rt, int l, int r);
void pushdown(int rt);
 
int main() {
    scanf("%d%d%d", &C, &S, &R);
    for (int i = 0; i < R; i++) {
        scanf("%d%d%d", &O, &D, &N);
        if (query(1, 1, C) + N > S) puts("N");
        else {
            puts("T");
            insert(1, 1, C);
        }
    }
    return 0;
}
 
#define lson (rt << 1)
#define rson (rt << 1 | 1)
 
int query(int rt, int l, int r) {
    if (r <= O || l >= D) return 0;
    if (O <= l && r <= D) {
        return tree[rt].val;
    }
    int mid = (l + r) >> 1;
    pushdown(rt);
    return std::max(query(lson, l, mid), query(rson, mid, r));
}
 
void insert(int rt, int l, int r) {
    if (r <= O || l >= D) return;
    if (O <= l && r <= D) {
        tree[rt].val += N;
        tree[rt].mark += N;
        return;
    }
    int mid = (l + r) >> 1;
    pushdown(rt);
    insert(lson, l, mid);
    insert(rson, mid, r);
    tree[rt].val = std::max(tree[lson].val, tree[rson].val);
}
 
void pushdown(int rt) {
    if (tree[rt].mark) {
        tree[lson].val += tree[rt].mark;
        tree[lson].mark += tree[rt].mark;
        tree[rson].val += tree[rt].mark;
        tree[rson].mark += tree[rt].mark;
        tree[rt].mark = 0;
    }
}
