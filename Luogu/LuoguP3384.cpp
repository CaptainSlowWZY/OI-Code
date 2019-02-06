// Luogu P3384
// Heavy-Light Decomposition Template
#include <cstdio>
#include <cstring>
#include <algorithm>

#define forto(_) for (int e = last[_], v = E[e].to; e; v = E[e = E[e].next].to)

const int MAXV = 1e5 + 10;

typedef long long LL;
typedef int IntAr[MAXV];

struct Edge {
    int to, next;
} E[MAXV << 1];

int N, M, RT, MOD, tote;
IntAr A, last;

namespace HLD {
IntAr fa, dep, sz, son, top, id;

/* fa[u]    - father of u
 * dep[u]   - depth of u
 * sz[u]    - size of subtree-u
 * son[u]   - heaviest son of u
 * top[u]   - the top of the chain that u belongs to
 * id[u]    - new id of u(in the segment tree)
 * rank[i]  - the vertex that the node-i in segment tree represent
 */

    namespace SMT {
        int QL, QR, DLT;

        int build(int l, int r);
        int _Q(int l, int r);
        int _UPD(int l, int r);
        inline int query(int l_, int r_) {
            QL = l_, QR = r_;
            return _Q(1, N);
        }
        inline void update(int l_, int r_, int d_) {
            QL = l_, QR = r_, DLT = d_;
            _UPD(1, N);
        } 
    } // namespacee SegMent Tree

    int query(int u, int v);
    void update(int u, int v, int delta);
    inline int query(int u) {
        return SMT::query(id[u], id[u] + sz[u] - 1);
    }
    inline void update(int u, int delta) {
        SMT::update(id[u], id[u] + sz[u] - 1, delta);
    }
    void dfs1(int u);
    void dfs2(int u, int tp);
    inline void init() {
		memset(son, 0xff, sizeof son);
		dep[RT] = 1;
        dfs1(RT);
//		puts(" DFS1 Complete!");
        dfs2(RT, RT);
//		puts(" DFS2 Complete!");
        SMT::build(1, N);
//		puts(" BUILD Complete!");
    }
} // namespace Heavy-Light Decomposition

inline void add_edge(int u, int v) {
    E[++tote] = (Edge){v, last[u]}, last[u] = tote;
    E[++tote] = (Edge){u, last[v]}, last[v] = tote;
}

int main() {
    scanf("%d%d%d%d", &N, &M, &RT, &MOD);
    for (int i = 1; i <= N; i++) scanf("%d", A + i);
    for (int i = 1, u, v; i < N; i++) {
        scanf("%d%d", &u, &v);
        add_edge(u, v);
    }

    HLD::init();
    for (int o, x, y, z; M--; ) {
        scanf("%d", &o);
        switch (o) {
            case 1  :
                scanf("%d%d%d", &x, &y, &z);
                HLD::update(x, y, z);
                break;
            case 2  :
                scanf("%d%d", &x, &y);
                printf("%d\n", HLD::query(x, y));
                break;
            case 3  :
                scanf("%d%d", &x, &z);
                HLD::update(x, z);
                break;
            case 4  :
                scanf("%d", &x);
                printf("%d\n", HLD::query(x));
        }
    }

    return 0;
}

namespace HLD {
    int totid;
    
    namespace SMT {
        struct Node {
            int val, mark;
        } T[MAXV << 1];

        inline int get_id(int l, int r) {
            return l + r | l != r;
        }

        int build(int l, int r) {
            int rt = get_id(l, r);
            T[rt].mark = 0;
            if (l == r) return T[rt].val;
            int mid = l + r >> 1;
            return T[rt].val = (build(l, mid) + build(mid + 1, r)) % MOD;
        }

        void push_down(int l, int r) {
            int rt = get_id(l, r);
            if (T[rt].mark) {
                int mid = l + r >> 1, ls = get_id(l, mid), rs = get_id(mid + 1, r);
                (T[ls].val += LL(mid - l + 1) * T[rt].mark % MOD) %= MOD;
                (T[rs].val += LL(r - mid) * T[rt].mark) %= MOD;
                (T[ls].mark += T[rt].mark) %= MOD, (T[rs].mark += T[rt].mark) %= MOD;
                T[rt].mark = 0;
            }
        }
        int _Q(int l, int r) {
            if (r < QL || l > QR) return 0;
            if (QL <= l && r <= QR) return T[get_id(l, r)].val;
            push_down(l, r);
            int mid = l + r >> 1;
            return (_Q(l, mid) + _Q(mid + 1, r)) % MOD;
        }

        int _UPD(int l, int r) {
            int rt = get_id(l, r);
            if (r < QL || l > QR) return T[rt].val;
            if (QL <= l && r <= QR) {
                (T[rt].val += LL(r - l + 1) * DLT % MOD) %= MOD;
                (T[rt].mark += DLT) %= MOD;
                return T[rt].val;
            }
            push_down(l, r);
            int mid = l + r >> 1;
            return T[rt].val = (_UPD(l, mid) + _UPD(mid + 1, r)) % MOD;
        } 
    } // namespacee SegMent Tree

    int query(int u, int v) {
        int ret = 0;
        for (; top[u] ^ top[v]; u = fa[top[u]]) {
            if (dep[top[u]] < dep[top[v]]) std::swap(u, v);
            (ret += SMT::query(id[top[u]], id[u])) %= MOD;
        }
        if (dep[u] < dep[v]) std::swap(u, v);
        return (ret + SMT::query(id[v], id[u])) % MOD;
    }

    void update(int u, int v, int delta) {
        for (delta %= MOD; top[u] ^ top[v]; u = fa[top[u]]) {
            if (dep[top[u]] < dep[top[v]]) std::swap(u, v);
            // u should be deeper
            SMT::update(id[top[u]], id[u], delta);
        }
        if (dep[u] < dep[v]) std::swap(u, v);
        SMT::update(id[v], id[u], delta);
    }

    void dfs1(int u) {
        sz[u] = 1;
        forto(u) {
            if (v == fa[u]) continue;
            fa[v] = u, dep[v] = dep[u] + 1;
            dfs1(v);
            sz[u] += sz[v];
            if (son[u] == -1 || sz[v] > sz[son[u]]) son[u] = v;
        }
    }

    void dfs2(int u, int tp) {
        id[u] = ++totid, top[u] = tp, SMT::T[SMT::get_id(totid, totid)].val = A[u] % MOD;
        if (son[u] == -1) return;
        dfs2(son[u], tp);
        forto(u) {
            if (v == son[u] || v == fa[u]) continue;
            dfs2(v, v);
        }
    }
} // namespace Heavy-Light Decomposition
