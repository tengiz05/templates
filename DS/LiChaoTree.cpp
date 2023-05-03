constexpr i64 inf = 1E9 + 44;
 
struct Line {
    i64 a, b;
    Line(i64 a = 0, i64 b = 0) : a(a), b(b) {}
};
 
i64 F(const Line &k, i64 x) {
    return x * k.a + k.b;
}
 
struct LiChao {
    struct Node {
        Line k;
        Node *l, *r;
        Node() : l(nullptr), r(nullptr) {}
    };
    int n;
    Node *root;
    LiChao(int n) : n(n), root(nullptr) {}
    void addLine(Node *&p, int l, int r, const Line &k) {
        if (p == nullptr) p = new Node();
        int m = (l + r) / 2;
        int lef = F(k, l) > F(p->k, l);
        int mid = F(k, m) > F(p->k, m);
        if (mid) {
            p->k = k;
        }
        if (l == r - 1) {
            return;
        }
        if (lef == mid) {
            addLine(p->r, m, r, k);
        } else {
            addLine(p->l, l, m, k);
        }
    }
    void addLine(const Line k) {
        addLine(root, 0, n, k);
    }
    i64 get(Node *&p, int l, int r, int x) {
        if (p == nullptr) return 0;
        if (l == r - 1) {
            return F(p->k, x);
        } else {
            int m = (l + r) / 2;
            if (x < m) {
                return std::max(F(p->k, x), get(p->l, l, m, x));
            } else {
                return std::max(F(p->k, x), get(p->r, m, r, x));
            }
        }
    }
    i64 get(int x) {
        return get(root, 0, n, x);
    }
};
