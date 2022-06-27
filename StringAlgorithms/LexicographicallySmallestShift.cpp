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
