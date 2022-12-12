https://vjudge.net/problem/SPOJ-KQUERY
#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;

// number of elements in range [l, r) that are bigger than k
struct Node {
    Node *l;
    Node *r;
    int cnt;
    Node() : l{}, r{}, cnt{} {}
};

Node *add(Node *t, int l, int r, int x) {
    Node *nt = new Node();
    if (t) {
        *nt = *t;
    }
    nt->cnt++;
    if (r - l > 1) {
        int m = (l + r) / 2;
        if (x < m) {
            nt->l = add(nt->l, l, m, x);
        } else {
            nt->r = add(nt->r, m, r, x);
        }
    }
    return nt;
}

int query(Node *t1, Node *t2, int l, int r, int x, int y) {
    if (r <= x || y <= l) {
        return 0;
    }
    if (x <= l && r <= y) {
        return (t2 ? t2->cnt : 0) - (t1 ? t1->cnt : 0);
    }
    int m = (l + r) / 2;
    return query(t1 ? t1->l : nullptr, t2 ? t2->l : nullptr, l, m, x, y)
         + query(t1 ? t1->r : nullptr, t2 ? t2->r : nullptr, m, r, x, y);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    auto f = a;
    std::sort(f.begin(), f.end());
    f.erase(std::unique(f.begin(), f.end()), f.end());
    
    std::vector<Node *> tree(n + 1);
    for (int i = 0; i < n; i++) {
        a[i] = std::lower_bound(f.begin(), f.end(), a[i]) - f.begin();
        tree[i + 1] = add(tree[i], 0, n, a[i]);
    }
    
    int q;
    std::cin >> q;
    
    while (q--) {
        int l, r, k;
        std::cin >> l >> r >> k;
        l--;
        k = std::upper_bound(f.begin(), f.end(), k) - f.begin();
        int ans = query(tree[l], tree[r], 0, n, k, n);
        std::cout << ans << "\n";
    }
    
    return 0;
}
