constexpr i64 inf = 1LL << 62;
i64 power(i64 a, i64 b, i64 P) {
    i64 res = 1;
    for (; b > 0; b /= 2, a = __int128(a) * a % P) {
        if (b % 2 == 1) {
            res = __int128(res) * a % P;
        }
    }
    return res;
}
std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
i64 pr[12] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
bool prime(i64 n) {
    if (n < 5)
        return (n == 2 || n == 3);
    if (n % 2 == 0)
        return false;
    bool prime = false;
    for (int i = 0; i < 12; i++) {
        i64 a = pr[i];
        if (a >= n) break;
        i64 p = power(a, (n - 1) / 2, n);
        if (p == 1)
            continue;
        if (p == n - 1)
            prime = true;
        else 
            return false;
    }
    return prime;
}
