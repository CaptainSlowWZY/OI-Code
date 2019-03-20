#include <cstdio>

#define forto(_) for (int e = last[_], v = E[e].to; e; v = E[e = E[e].next].to)

const int kMaxn = 1e6 + 10;

typedef long long LL;
typedef int IAr[kMaxn];

struct Edge {
    int to, next;
} E[kMaxn << 1];

int n, m, tote;
IAr last, V;

namespace hld {
    IAr dep, sz, fa, son, top, dfn;

    void Dfs1(int u);
    namespace smt {
        LL Build(int l, int r);
        LL Modify(int l, int r, int ql, int qr, int del);
    }
    void Dfs2(int u, int tp);
    inline void Init() {
        dep[1] = 1;
        Dfs1(1);
        Dfs2(1, 1);
        smt::Build(1, n);
    }
    inline void AddVec(int u, int del) {
        smt::Modify(1, n, dfn[u], dfn[u], del);
    }
    inline void AddSub(int u, int del) {
        smt::Modify(1, n, dfn[u], dfn[u] + sz[u] - 1, del);
    }
    LL Query(int u);
}
inline void AddEdge(int u, int v) {
    E[++tote] = (Edge){v, last[u]}, last[u] = tote;
    E[++tote] = (Edge){u, last[v]}, last[v] = tote;
}

signed main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", V + i);
    for (int i = 1, u, v; i < n; i++) {
        scanf("%d%d", &u, &v);
        AddEdge(u, v);
    }

    hld::Init();

    for (int tp, x, a; m--; ) {
        scanf("%d", &tp);
        if (tp == 1) {
            scanf("%d%d", &x, &a);
            hld::AddVec(x, a);
        }
        if (tp == 2) {
            scanf("%d%d", &x, &a);
            hld::AddSub(x, a);
        }
        if (tp == 3) {
            scanf("%d", &x);
            printf("%lld\n", hld::Query(x));
        }
    }
    return 0;
}

namespace hld {
    void Dfs1(int u) {
        sz[u] = 1, son[u] = -1;
        forto(u) {
            if (v == fa[u]) continue;
            fa[v] = u, dep[v] = dep[u] + 1;
            Dfs1(v);
            sz[u] += sz[v];
            if (son[u] == -1 || sz[v] > sz[son[u]]) son[u] = v;
        }
    }
    namespace smt {
        struct Node {
            LL val, tag;
            Node(LL val_ = 0) :
                val(val_) { tag = 0; }
        } T[kMaxn << 1];

        inline int Id(int l, int r) {
            return l + r | l != r;
        }
        LL Build(int l, int r) {
            int rt = Id(l, r);
            if (l == r) return T[rt].val;
            int mid = l + r >> 1;
            return T[rt].val = Build(l, mid) + Build(mid + 1, r);
        }
        void PushDown(int l, int mid, int r) {
            int rt = Id(l, r);
            if (!T[rt].tag) return;
            int ls = Id(l, mid), rs = Id(mid + 1, r);
            T[ls].val += 1ll * (mid - l + 1) * T[rt].tag;
            T[ls].tag += T[rt].tag;
            T[rs].val += 1ll * (r - mid) * T[rt].tag;
            T[rs].tag += T[rt].tag;
            T[rt].tag = 0;
        }
        LL Modify(int l, int r, int ql, int qr, int del) {
            int rt = Id(l, r);
            if (l > qr || r < ql) return T[rt].val;
            if (ql <= l && r <= qr) {
                T[rt].tag += del;
                return T[rt].val += 1ll * (r - l + 1) * del;
            }
            int mid = l + r >> 1;
            PushDown(l, mid, r);
            return T[rt].val = Modify(l, mid, ql, qr, del) +
                        Modify(mid + 1, r, ql, qr, del);
        }
        LL Query(int l, int r, int ql, int qr) {
            int rt = Id(l, r);
            if (ql <= l && r <= qr) return T[rt].val;
            int mid = l + r >> 1;
            PushDown(l, mid, r);
            LL ret = 0;
            if (ql <= mid) ret += Query(l, mid, ql, qr);
            if (mid < qr) ret += Query(mid + 1, r, ql, qr);
            return ret;
        }
    }
    void Dfs2(int u, int tp) {
        static int dfs_clock = 0;
        dfn[u] = ++dfs_clock, top[u] = tp;
        smt::T[smt::Id(dfn[u], dfn[u])] = V[u];
        if (son[u] == -1) return;
        Dfs2(son[u], tp);
        forto(u) {
            if (v == fa[u] || v == son[u]) continue;
            Dfs2(v, v);
        }
    }
    LL Query(int u) {
        LL ret = 0;
        for (; u; u = fa[top[u]]) {
            ret += smt::Query(1, n, dfn[top[u]], dfn[u]);
        }
        return ret;
    }
}