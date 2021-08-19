struct Fenwick {
    const int n;
    std::vector<int> a;
    Fenwick(int n) : n(n), a(n) {}
    void add(int x, int v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] += v;
        }
    }
    int sum(int x) {
        int ans = 0;
        for (int i = x; i > 0; i -= i & -i) {
            ans += a[i - 1];
        }
        return ans;
    }
    int find(int k) {
        int x = 0;
        for (int i = 1 << std::__lg(n); i > 0; i /= 2) {
            if (x + i <= n && a[x + i - 1] <= k) {
                x += i;
                k -= a[x - 1];
            }
        }
        return x;
    }
};
