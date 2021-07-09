#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching"
#include<bits/stdc++.h>
struct bipartiteMatching {
    int n;
    std::vector<std::vector<int>> e;
    std::vector<int> match;
    std::vector<bool> used;
    bipartiteMatching(int n) : n(n), e(n) {}
    void addEdge(int u, int v) {
        e[u].push_back(v);
        e[v].push_back(u);
    }
    bool dfs(int v) {
        used[v] = true;
        for (int u : e[v]) {
            int w = match[u];
            if (w < 0 || !used[w] && dfs(w)) {
                match[v] = u;
                match[u] = v;
                return true;
            }
        }
        return false;
    }
    int count() {
        int ans = 0;
        bool flag = true;
        match.assign(n, -1);
        while (flag) {
            flag = false;
            used.assign(n, false);
            for (int v = 0; v < n; v++) {
                if (match[v] == -1 && dfs(v)) {
                    ans++;
                    flag = true;
                }
            }
        }
        return ans;
    }
};
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int L, R, M;
    std::cin >> L >> R >> M;
    bipartiteMatching P(L + R);
    for (int i = 0; i < M; i++) {
        int u, v;
        std::cin >> u >> v;
        P.addEdge(u, L + v);
    }
    std::cout << P.count() << "\n";
    for(int i = 0; i < L; i++){
        if (P.match[i] >= L) {
            std::cout << i << " " << P.match[i] - L << "\n";
        }
    }
}
