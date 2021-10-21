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

bool Solve(i64 a, i64 b, i64 c, i64 &x0, i64 &y0, i64 &g) {
    g = extGcd(std::abs(a), std::abs(b), x0, y0);
    if (c % g != 0) {
        return false;
    }
    x0 *= c / g;
    y0 *= c / g;
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    return true;
}
