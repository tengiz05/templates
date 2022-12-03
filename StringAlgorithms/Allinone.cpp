int min_cyc(const string &s) {
    int n = s.size();
    int res = 0;
    for (int l = 0; l < n; ){
        res = l;
        int r = l, p = l + 1;
        for (; r < n; ++r, ++p) {
            char c = (p < n) ? s[p] : s[p - n];
            if (s[r] > c) break;
            if (s[r] < c) r = l - 1;
        }        
        l = max(r, l + p - r);
    }
    return res;
}

string convertToNewString(const string &s) {
    string newString = "@";
 
    for (int i = 0; i < s.size(); i++) {
        newString += "#" + s.substr(i, 1);
    }
 
    newString += "#$";
    return newString;
}
vector<int> longestPalindromeSubstring(const string &s) {
    string Q = convertToNewString(s);
    int c = 0, r = 0;
    std::vector<int> P(Q.size());
    for (int i = 1; i < Q.size() - 1; i++) {
        int iMirror = c - (i - c);
        if(r > i) {
            P[i] = min(r - i, P[iMirror]);
        }
        while (Q[i + 1 + P[i]] == Q[i - 1 - P[i]]){
            P[i]++;
        }
        if (i + P[i] > r) {
            c = i;
            r = i + P[i];
        }
    }
    return P;
}

std::vector<int> prefix_function(std::string s) {
    int n = s.size();
    std::vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}
std::vector<int> z_function(std::string s) {
    int n = s.length();
    std::vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r)
            z[i] = std::min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}

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

int compare(int i, int j, int l) {
    int k = std::__lg(l);
    std::pair<int, int> a = {c[k][i], c[k][(i + l - (1 << k)) % n]};
    std::pair<int, int> b = {c[k][j], c[k][(j + l - (1 << k)) % n]};
    return a == b ? 0 : a < b ? -1 : 1;
}
