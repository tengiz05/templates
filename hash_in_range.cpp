struct Hash {
    static constexpr int P = 1000000007, M = 29;
    int n;
    std::vector<int> a, pw;
    Hash(std::string s) : n(s.size()), a(n + 1), pw(n + 1, 1) {
        for (int i = 1; i <= n; i++)
            pw[i] = 1LL * pw[i - 1] * M % P;
        for (int i = 0; i < n; i++)
            a[i + 1] = (1LL * a[i] * M + (s[i] - 'a' + 1)) % P;
    }
    int get(int l, int r) {
        int res = a[r] - 1LL * pw[r - l] * a[l] % P;
        if (res < 0)
            res += P;
        return res;
    }
};
