constexpr int alphabet = 256;
std::vector<int> sort_cyclic_shifts(const std::string &s) {
    int n = s.length();
    std::vector<int> p(n), c(n), cnt(std::max(n, alphabet), 0);
    for (int i = 0; i < n; i++)
        cnt[s[i]]++;
    for (int i = 1; i < alphabet; i++)
        cnt[i] += cnt[i - 1];
    for (int i = 0; i < n; i++)
        p[--cnt[s[i]]] = i;
    c[p[0]] = 0;
    int classes = 1;
    for (int i = 1; i < n; i++) {
        if (s[p[i]] != s[p[i - 1]])
            classes++;
        c[p[i]] = classes - 1;
    }
    std::vector<int> pn(n), cn(n);
    for (int h = 0; (1 << h) < n; h++) {
        for (int i = 0; i < n; i++) {
            pn[i] = p[i] - (1 << h);
            if (pn[i] < 0)
                pn[i] += n;
        }
        std::fill(cnt.begin(), cnt.begin() + classes, 0);
        for (int i = 0; i < n; i++)
            cnt[c[pn[i]]]++;
        for (int i = 1; i < classes; i++)
            cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; i--)
            p[--cnt[c[pn[i]]]] = pn[i];
        cn[p[0]] = 0;
        classes = 1;
        for (int i = 1; i < n; i++) {
            std::pair<int, int> cur{c[p[i]], c[(p[i] + (1 << h)) % n]};
            std::pair<int, int> prev{c[p[i - 1]], c[(p[i - 1] + (1 << h)) % n]};
            if (cur != prev)
                classes++;
            cn[p[i]] = classes - 1;
        }
        c.swap(cn);
    }
    return p;
}
std::vector<int> lcp_construction(std::string const& s, std::vector<int> const& p) {
    int n = s.size();
    std::vector<int> rank(n);
    for (int i = 0; i < n; i++)
        rank[p[i]] = i;
    int k = 0;
    std::vector<int> lcp(n - 1, 0);
    for (int i = 0; i < n; i++) {
        if (rank[i] == n - 1) {
            k = 0;
            continue;
        }
        int j = p[rank[i] + 1];
        while (i + k < n && j + k < n && s[i + k] == s[j + k])
            k++;
        lcp[rank[i]] = k;
        if (k)
            k--;
    }
    return lcp;
}

std::vector<int> suffix_array(std::string s) {
    s += "$";
    std::vector<int> shifts = sort_cyclic_shifts(s);
    shifts.erase(shifts.begin());
    return shifts;
}
