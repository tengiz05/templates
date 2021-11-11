// https://codeforces.com/gym/102770/problem/E

#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 5, M = 5e6;

std::vector<int> f;
int ts = 0, rt[M], siz[M], ls[M], rs[M];
i64 pre[N + 1], sum[M];

void modify(int x, int w, int &u, int v, int l, int r) {
    u = ++ts;
    ls[u] = ls[v];
    rs[u] = rs[v];
    siz[u] = siz[v] + 1;
    sum[u] = sum[v] + w;
    if (l == r)
        return;
    int m = (l + r) / 2;
    if (x <= m) {
        modify(x, w, ls[u], ls[v], l, m);
    } else {
        modify(x, w, rs[u], rs[v], m + 1, r);
    }
}
i64 query(int u, int v, int l, int r, int k) {
    if (l == r) {
        return 1LL * k * f[l - 1];
    }
    int m = (l + r) / 2;
    int rsiz = siz[rs[v]] - siz[rs[u]];
    if (rsiz >= k) {
        return query(rs[u], rs[v], m + 1, r, k);
    } else {
        return sum[rs[v]] - sum[rs[u]] + query(ls[u], ls[v], l, m, k - rsiz);
    }
}

void solve() {
    ts = 0;
    int n;
    std::cin >> n;
    
    int a[n + 1];
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
    
    f = std::vector<int>(a + 1, a + n + 1);
    std::sort(f.begin(), f.end());
    f.erase(std::unique(f.begin(), f.end()), f.end());
    int m = f.size();
    for (int i = 1; i <= n; i++) {
        modify(std::lower_bound(f.begin(), f.end(), a[i]) - f.begin() + 1, a[i], rt[i], rt[i - 1], 1, m);
    }
    
    int q;
    std::cin >> q;
    
    while (q--) {
        int l, r, k;
        std::cin >> l >> r >> k;
        l--;
        std::cout << pre[r - l] + query(rt[l], rt[r], 1, m, k) << "\n";
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    for (int i = 1; i <= N; i++) {
        pre[i] = pre[i - 1] + 1LL * i * i;
    }
    
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    
    return 0;
}
