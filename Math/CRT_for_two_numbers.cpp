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
i64 crt(i64 a, i64 b, i64 n, i64 m) {
    i64 x, y;
    i64 g = extGcd(n, m, x, y);
    if ((b - a) % g != 0) assert(false); // no solution
    i64 ans = (a + x * (b - a) / g % (m / g) * n) % (n * m / g);
    if (ans < 0)
        ans += n * m / g;
    return ans;
}
