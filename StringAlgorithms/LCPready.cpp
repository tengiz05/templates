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
std::vector<int> rank;
std::vector<int> lcp_construction(std::string const& s, std::vector<int> const& p) {
    int n = s.size();
    rank.assign(n, 0);
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
 
std::vector<std::vector<int>> mn;
 
std::string s;
void suffix_array(std::string &s) {
    int n = s.size();
    s += "$";
    std::vector<int> p = sort_cyclic_shifts(s);
    auto lcp = lcp_construction(s, p);
    p.erase(p.begin());
    mn.assign(n, std::vector<int>(20));
    for (int i = 0; i < n; i++) {
        mn[i][0] = lcp[i];
    }
    for (int j = 0; (1 << (j + 1)) <= n; j++) {
        for (int i = 0; i + (1 << (j + 1)) <= n; i++) {
            mn[i][j + 1] = std::min(mn[i][j], mn[i + (1 << j)][j]);
        }
    }
}
 
int getMin(int l, int r) {
    int k = std::__lg(r - l);
    return std::min(mn[l][k], mn[r - (1 << k)][k]);
}
int getLCP(int i, int j) {
    if (i == j) {
        return int(mn.size()) - i;
    }
    i = rank[i], j = rank[j];
    return getMin(std::min(i, j), std::max(i, j));
}
bool cmp(const std::pair<int, int> &a, const std::pair<int, int> &b) {
    if (a.first == b.first) {
        return a.second < b.second;
    }
    int k = getLCP(a.first, b.first);
    return s[a.first + k] < s[b.first + k];
}
