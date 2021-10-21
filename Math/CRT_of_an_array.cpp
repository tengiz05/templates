i64 extGcd(i64 a, i64 b, i64 &x, i64 &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    i64 x1, y1;
    i64 d = extGcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}
i64 norm(i64 a, i64 b) {
    a %= b;
    if (a < 0) {
        a += b;
    }
    return a;
}
i64 crt(std::vector<i64> a, std::vector<i64> n) {
    i64 ans = a[0];
    i64 lcm = n[0];
    for (int i = 1; i < int(a.size()); i++) {
        i64 x, y;
        i64 g = extGcd(lcm, n[i], x, y);
        if ((a[i] - ans) % g != 0) {
            // no solution
            return -1;
        }
        ans = norm(ans + x * (a[i] - ans) / g % (n[i] / g) * lcm, lcm * n[i] / g);
        lcm = std::lcm(lcm, n[i]);
    }
    return ans;
}
