struct SegmentTree {
    int n;
    std::vector<int> mn, mx;
    SegmentTree(int n) : n(n), mn(4 * n, 1E9), mx(4 * n) {}
    void modify(int p, int l, int r, int x, int y) {
        if (r - l == 1) {
            mn[p] = mx[p] = y;
        } else {
            int m = (l + r) / 2;
            if (x < m) {
                modify(2 * p, l, m, x, y);
            } else {
                modify(2 * p + 1, m, r, x, y);
            }
            mn[p] = std::min(mn[2 * p], mn[2 * p + 1]);
            mx[p] = std::max(mx[2 * p], mx[2 * p + 1]);
        }
    }
    void modify(int x, int y) {
        modify(1, 0, n, x, y);
    }
    int rangeMin(int p, int l, int r, int x, int y) {
        if (y <= l || r <= x) {
            return 1E9;
        }
        if (x <= l && r <= y) {
            return mn[p];
        }
        int m = (l + r) / 2;
        return std::min(rangeMin(2 * p, l, m, x, y), rangeMin(2 * p + 1, m, r, x, y));
    }
    int rangeMin(int l, int r) {
        return rangeMin(1, 0, n, l, r);
    }
    int nextSmaller(int p, int l, int r, int x, int y, int v) {
        if (y <= l || r <= x || mn[p] > v) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        int res = nextSmaller(2 * p, l, m, x, y, v);
        if (res == -1) {
            res = nextSmaller(2 * p + 1, m, r, x, y, v);
        }
        return res;
    }
    int nextSmaller(int l, int r, int v) {
        return nextSmaller(1, 0, n, l, r, v);
    }
    int nextGreater(int p, int l, int r, int x, int y, int v) {
        if (y <= l || r <= x || mx[p] < v) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        int res = nextGreater(2 * p, l, m, x, y, v);
        if (res == -1) {
            res = nextGreater(2 * p + 1, m, r, x, y, v);
        }
        return res;
    }
    int nextGreater(int l, int r, int v) {
        return nextGreater(1, 0, n, l, r, v);
    }
};
