https://codeforces.com/contest/1401/problem/F
// range querying in the array a[i ^ x] for some 0 <= x < n

struct XORSegmentTree {
    // length must be a power of 2
    int n;
    std::vector<std::vector<i64>> t;
    std::vector<i64> lazy;
    XORSegmentTree(int n) : n(n), t(2 * n), lazy(2 * n) {}
    void build(int p, int l, int r, std::vector<int> &a) {
        if (l == r - 1) {
            t[p].push_back(a[l]);
        } else {
            int m = (l + r) / 2;
            build(2 * p, l, m, a);
            build(2 * p + 1, m, r, a);
            for (int i = 0; i < m - l; i++) {
                t[p].push_back(t[2 * p][i] + t[2 * p + 1][i]);
            }
            for (int i = 0; i < m - l; i++) {
                t[p].push_back(t[2 * p + 1][i] + t[2 * p][i]);
            }
        }
    }
    void modify(int p, int l, int r, int x, int y) {
        lazy[p] += y;
        if (l == r - 1) {
            return;
        } else {
            int m = (l + r) / 2;
            if (x < m) {
                modify(2 * p, l, m, x, y);
            } else {
                modify(2 * p + 1, m, r, x, y);
            }
        }
    }
    void modify(int x, int y) {
        modify(1, 0, n, x, y);
    }
    i64 query(int p, int l, int r, int x, int y, int XOR) {
        if (r <= x || y <= l) {
            return 0;
        }
        if (x <= l && r <= y) {
            return lazy[p] + t[p][XOR & (r - l - 1)];
        }
        int bit = (r - l) / 2;
        int m = (l + r) / 2;
        if (~XOR & bit) {
            return query(2 * p, l, m, x, y, XOR) + query(2 * p + 1, m, r, x, y, XOR);
        } else {
            return query(2 * p + 1, m, r, x + bit, std::min(m, y) + bit, XOR) + query(2 * p, l, m, std::max(x, m) - bit, y - bit, XOR);
        }
    }
    i64 query(int l, int r, int XOR) {
        return query(1, 0, n, l, r, XOR);
    }
};
