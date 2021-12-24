#include <bits/stdc++.h>

std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());

struct Node {
    int pr;
    int x;
    int sz;
    bool prop;
    Node *l, *r, *p;
    int L, R;
    int tag;
    Node(int x) : sz(1), x(x), l(nullptr), r(nullptr), p(nullptr), prop(0) {
        pr = rnd() % 2000000000;
        L = R = x;
        tag = 0;
    }
};
int size(Node *me) {
    if (me == nullptr) return 0;
    return me->sz;
}
void push(Node *me) {
    if (me == nullptr) return;
    if (me->prop) {
        std::swap(me->l, me->r);
        std::swap(me->L, me->R);
        if (me->l != nullptr) me->l->prop ^= 1;
        if (me->r != nullptr) me->r->prop ^= 1;
        me->prop = 0;
    }
}
void recalc(Node *me) {
    push(me->l);
    push(me->r);
    me->L = me->R = me->x;
    if (me->l != nullptr) {
        me->l->p = me;
        me->L = me->l->L;
    }
    if (me->r != nullptr) {
        me->r->p = me;
        me->R = me->r->R;
    }
    me->sz = size(me->l) + 1 + size(me->r);
}
Node* merge(Node *l, Node *r) {
    push(l);
    push(r);
    if (l == nullptr) return r;
    if (r == nullptr) return l;
    if (l->pr > r->pr) {
        l->r = merge(l->r, r);
        recalc(l);
        return l;
    } else {
        r->l = merge(l, r->l);
        recalc(r);
        return r;
    }
}
std::pair<Node*, Node*> split(Node *me, int inLeft) {
    if (me == nullptr) return {nullptr, nullptr};
    push(me);
    if (inLeft > size(me->l)) {
        auto p = split(me->r, inLeft - size(me->l) - 1);
        me->r = p.first;
        recalc(me);
        me->p = nullptr;
        if (p.second != nullptr) p.second->p = nullptr;
        return {me, p.second};
    } else {
        auto p = split(me->l, inLeft);
        me->l = p.second;
        recalc(me);
        me->p = nullptr;
        if (p.first != nullptr) p.first->p = nullptr;
        return {p.first, me};
    }
}
void show(Node *me) {
    if (me == nullptr) return;
    push(me);
    show(me->l);
    std::cerr << me->x << " ";
    show(me->r);
}
void print(Node *me) {
    show(me);
    std::cerr << "\n";
}

int first(Node *me) {
    if (me->l != nullptr) {
        return first(me->l);
    }
    return me->x;
}
int last(Node *me) {
    if (me->r != nullptr) {
        return last(me->r);
    }
    return me->x;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, q;
    std::cin >> n >> q;
    
    int a[n];
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        a[i]--;
    }
    
    Node *p[n];
    
    for (int i = 0; i < n; i++) {
        p[i] = new Node(i);
    }
    
    auto prop = [&](int u) {
        std::vector<int> v;
        while (p[u]->p != nullptr) {
            v.push_back(u);
            u = p[u]->p->x;
        }
        v.push_back(u);
        for (int i = int(v.size()) - 1; i >= 0; i--) {
            push(p[v[i]]);
        }
    };
    
    auto find = [&](int u) {
        prop(u);
        while (p[u]->p != nullptr) {
            u = p[u]->p->x;
        }
        return u;
    };
    
    std::set<std::pair<int, int>> s;
    
    auto disconnect = [&](int u, int v) {
        s.erase({u, v});
        int U = find(u);
        int V = find(v);
        int x = size(p[U]);
        auto dist = [&](int u) {
            prop(u);
            int lst = u;
            int res = size(p[u]->l);
            while (p[u]->p != nullptr) {
                u = p[u]->p->x;
                if (p[u]->r != nullptr && lst == p[u]->r->x) {
                    res += size(p[u]->l) + 1;
                }
                lst = u;
            }
            return res;
        };
        int up = dist(u), vp = dist(v);
        if (up > vp) {
            std::swap(up, vp);
        }
        if (p[U]->tag) {
            p[U]->tag = 0;
            if (vp - up == 1) {
                auto [l, r] = split(p[U], vp);
                Node *_ = merge(r, l);
            }
        } else {
            auto [l, r] = split(p[U], vp);
        }
    };
    auto connect = [&](int u, int v) {
        s.insert({u, v});
        int U = find(u);
        int V = find(v);
        int x = size(p[U]);
        auto dist = [&](int u) {
            prop(u);
            int lst = u;
            int res = size(p[u]->l);
            while (p[u]->p != nullptr) {
                u = p[u]->p->x;
                if (p[u]->r != nullptr && lst == p[u]->r->x) {
                    res += size(p[u]->l) + 1;
                }
                lst = u;
            }
            return res;
        };
        int up = dist(u), vp = dist(v);
        if (U == V) {
            p[U]->tag = 1;
        } else {
            if (p[U]->L == u) {
                if (p[V]->R != v)
                    p[V]->prop = 1;
                Node *root = merge(p[V], p[U]);
            } else {
                if (p[V]->L != v)
                    p[V]->prop = 1;
                Node *root = merge(p[U], p[V]);
            }
        }
    };
    for (int i = 0; i < n; i++) {
        connect(i, a[i]);
    }
    
    while (q--) {
        int op;
        int u, v;
        std::cin >> op >> u >> v;
        u--;
        v--;
        
        int U = find(u);
        
        auto dist = [&](int u) {
            prop(u);
            int lst = u;
            int res = size(p[u]->l);
            while (p[u]->p != nullptr) {
                u = p[u]->p->x;
                if (p[u]->r != nullptr && lst == p[u]->r->x) {
                    res += size(p[u]->l) + 1;
                }
                lst = u;
            }
            return res;
        };
        
        if (op == 2) {
            v++;
            int up = dist(u);
            int sz = size(p[U]);
            int F = first(p[U]);
            int S = last(p[U]);
            int pos;
            if (s.count({F, S})) {
                pos = (((up - v) % sz) + sz) % sz;
            } else {
                pos = (((up + v) % sz) + sz) % sz;
            }
            auto [l, M] = split(p[U], pos);
            auto [m, r] = split(M, 1);
            std::cout << m->x + 1 << "\n";
            merge(l, merge(m, r));
        } else {
            disconnect(u, a[u]);
            disconnect(v, a[v]);
            std::swap(a[u], a[v]);
            connect(u, a[u]);
            connect(v, a[v]);
        }
    }
    
    return 0;
}
