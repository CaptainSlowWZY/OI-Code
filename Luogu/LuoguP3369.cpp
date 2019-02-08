#include <cstdio>
#include <cstdlib>
#include <climits>

class Splay {
private:
    struct Node {
        int val, sz, cnt;
        Node *fa, *ch[2];
        //	rt - pointer to the root-pointer in the splay-tree
        Node(int v_, Node *fa_ = NULL) : val(v_), fa(fa_) {
            ch[0] = ch[1] = NULL, cnt = 1;
        }
        //	the relation - left/right child
        int relat() const {
            return this == fa->ch[0] ? 0 : 1;
        }
        //	reset the information
        void reset() {
            sz = cnt + (ch[0] ? ch[0]->sz : 0) + (ch[1] ? ch[1]->sz : 0);
        }
        //	node-precursor
        //	notice that in this splay, there are no same-key node
        //	and prec() is always after splay(), so we can make it easier
        Node *prec() {
            Node *v = ch[0];
            while (v->ch[1]) v = v->ch[1];
            return v;
        }
        //	node-successor
        Node *succ() {
            Node *v = ch[1];
            while (v->ch[0]) v = v->ch[0];
            return v;
        }
        int rank() const {
            return ch[0] ? ch[0]->sz : 0;
        }
    } *root;

    void rotate(Node *u) {
        Node *prf = u->fa;
        int r = u->relat();
        // 	link self and pre-fa's father
        u->fa = prf->fa;
        if (prf->fa) prf->fa->ch[prf->relat()] = u;
        //	link one child and pre-fa
        if (u->ch[r ^ 1]) u->ch[r ^ 1]->fa = prf;
        prf->ch[r] = u->ch[r ^ 1];
        //	set pre-fa son
        prf->fa = u, u->ch[r ^ 1] = prf;
        //	update information
        prf->reset();
        u->reset();
        if (!u->fa) root = u;
    }
    //	Splay operation, trgt - the target position's father
    void splay(Node *u, Node *trgt = NULL) {
        while (u->fa != trgt) {
            if (u->fa->fa == trgt) rotate(u);
            else if (u->fa->relat() == u->relat()) {
                rotate(u->fa);
                rotate(u);
            }
            else {
                rotate(u);
                rotate(u);
            }
        }
    }
    Node *find(int k) {
        Node *v = root;
        for (; v && v->val != k; v = k < v->val ? v->ch[0] : v->ch[1]);
        if (v) splay(v);
        return v;
    }
//	erase a node
    void erase(Node *v) {
        Node *su = v->succ(), *pr = v->prec();
        splay(pr);
        splay(su, pr);
        if (v->sz > 1) {
            --v->sz, --v->cnt;
        }
        else {
            delete su->ch[0];
            su->ch[0] = NULL;
        }
        --su->sz, --pr->sz;
    }
public:
    Splay() : root(NULL) {
        insert(INT_MAX);
        insert(INT_MIN);
    }
    Node *insert(int k) {
        Node **v = &root, *fa = NULL;
    //	here we must let v be a pointer to pointer
        for (; *v && (*v)->val != k; v = k < fa->val ? &fa->ch[0] : &fa->ch[1]) {
            fa = *v, ++fa->sz;
        }
        if (*v) {
            ++(*v)->cnt, ++(*v)->sz;
        }
        else (*v) = new Node(k, fa);
        splay(*v);
        return root;
    }
//	erase a key
    void erase(int k) {
        Node *v = find(k);
        if (v) erase(v);
    }
//	key-precursor
    int prec(int k) {
        Node *v = find(k);
        if (v) return v->prec()->val;
        else {
            v = insert(k);
            int ret = v->prec()->val;
            erase(v);
            return ret;
        }
    }
//	key-successor
    int succ(int k) {
        Node *v = find(k);
        if (v) return v->succ()->val;
        else {
            v = insert(k);
            int ret = v->succ()->val;
            erase(v);
            return ret;
        }
    }
//	key-rank
    int rank(int k) {
        Node *v = find(k);
        if (v) return v->rank();
        else {
            v = insert(k);
            int ret = v->rank();
            erase(v);
            return ret;
        }
    }
//	find k-th key
    int query(int k) {
        Node *v = root;
        while (true) {
            if (k < v->rank()) v = v->ch[0];
            else if (k >= v->rank() + v->cnt) {
                k -= v->rank() + v->cnt;
                v = v->ch[1];
            }
            else break;
        }
        splay(v);
        return v->val;
    }
} T;

int main() {
    int n;
    scanf("%d", &n);
    for (int o, x; n--; ) {
        scanf("%d%d", &o, &x);
        switch (o) {
            case 1	:
                T.insert(x);
                break;
            case 2	:
                T.erase(x);
                break;
            case 3	:
                printf("%d\n", T.rank(x));
                break;
            case 4	:
                printf("%d\n", T.query(x));
                break;
            case 5	:
                printf("%d\n", T.prec(x));
                break;
            case 6	:
                printf("%d\n", T.succ(x));
        }
    }

    return 0;
}
