#include <bits/stdc++.h>
 
using i64 = long long;
 
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<int> e[n];
    // for (int i = 0; i < n - 1; i++) {
    //     int u, v;
    //     std::cin >> u >> v;
    //     u--;
    //     v--;
    //     e[u].push_back(v);
    //     e[v].push_back(u);
    // }
    
    int r = 0;
    
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        if (x == -1) {
            r = i;
        } else {
            e[--x].push_back(i);
        }
    }
    
    int p[n][20];
    
    int timeStamp = 0;
    int in[n], out[n], dep[n];
    std::function<void(int, int, int)> dfs = [&](int u, int par, int d) {
        in[u] = timeStamp++;
        p[u][0] = par;
        dep[u] = d;
        for (int v : e[u]) {
            if (v != par) {
                dfs(v, u, d + 1);
            }
        }
        out[u] = timeStamp;
    };
    
    dfs(r, r, 0);
    
    for (int j = 1; j < 20; j++) {
        for (int i = 0; i < n; i++) {
            p[i][j] = p[p[i][j - 1]][j - 1];
        }
    }
    
    auto is = [&](int u, int v) {
        return in[u] <= in[v] && out[u] >= out[v];
    };
    
    auto lca = [&](int u, int v) {
        if (is(u, v)) return u;
        if (is(v, u)) return v;
        for (int i = 19; i >= 0; i--) {
            if (!is(p[u][i], v)) {
                u = p[u][i];
            }
        }
        return p[u][0];
    };
    
    int q;
    std::cin >> q;
    
    std::vector<int> adj[n];
    
    while (q--) {
        int k;
        std::cin >> k;
        
        std::vector<int> a(k);
        for (int i = 0; i < k; i++) {
            std::cin >> a[i];
            a[i]--;
        }
        
        if (!std::count(a.begin(), a.end(), r)) {
            a.push_back(r);
            k++;
        }
        
        std::sort(a.begin(), a.end(), [&](int i, int j) {
            return in[i] < in[j];
        });
        
        for (int i = 1; i < k; i++) {
            a.push_back(lca(a[i - 1], a[i]));
        }
        
        std::sort(a.begin(), a.end(), [&](int i, int j) {
            return in[i] < in[j];
        });
        a.erase(std::unique(a.begin(), a.end()), a.end());
        
        k = a.size();
        std::vector<int> s{a[0]};
        for (int i = 1; i < k; i++) {
            int u = a[i];
            while (int(s.size()) >= 2 && !is(s.back(), u)) {
                adj[s[int(s.size()) - 2]].push_back(s.back());
                s.pop_back();
            }
            s.push_back(u);
        }
        
        while (int(s.size()) >= 2) {
            adj[s[int(s.size()) - 2]].push_back(s.back());
            s.pop_back();
        }
        
        int ans = 1;
        
        for (auto x : a) {
            for (auto y : adj[x]) {
                ans += dep[y] - dep[x];
            }
        }
        
        std::cout << ans << "\n";
        
        for (auto x : a) {
            adj[x].clear();
        }
    }
    
    return 0;
}
