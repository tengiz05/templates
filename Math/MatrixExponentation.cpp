constexpr int P = 1000000007;
using i64 = long long;
// assume -P <= x < 2P
int norm(int x) {
    if (x < 0) {
        x += P;
    }
    if (x >= P) {
        x -= P;
    }
    return x;
}
template<class T>
T power(T a, int b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}
struct Z {
    int x;
    Z(int x = 0) : x(norm(x)) {}
    int val() const {
        return x;
    }
    Z operator-() const {
        return Z(norm(P - x));
    }
    Z inv() const {
        assert(x != 0);
        return power(*this, P - 2);
    }
    Z &operator*=(const Z &rhs) {
        x = i64(x) * rhs.x % P;
        return *this;
    }
    Z &operator+=(const Z &rhs) {
        x = norm(x + rhs.x);
        return *this;
    }
    Z &operator-=(const Z &rhs) {
        x = norm(x - rhs.x);
        return *this;
    }
    Z &operator/=(const Z &rhs) {
        return *this *= rhs.inv();
    }
    friend Z operator*(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res *= rhs;
        return res;
    }
    friend Z operator+(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res += rhs;
        return res;
    }
    friend Z operator-(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res -= rhs;
        return res;
    }
    friend Z operator/(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res /= rhs;
        return res;
    }
};
using Matrix = std::vector<std::vector<Z>>;
int Size = 0;
Matrix operator*(const Matrix &a, const Matrix &b) {
    Matrix c(Size, std::vector<Z>(Size));
    for (int i = 0; i < Size; i++) {
        for (int j = 0; j < Size; j++) {
            for (int k = 0; k < Size; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return c;
}
std::vector<Z> operator*(const std::vector<Z> &a, const Matrix &b) {
    std::vector<Z> c(Size);
    for (int j = 0; j < Size; j++) {
        for (int k = 0; k < Size; k++) {
            c[j] += a[k] * b[k][j];
        }
    }
    return c;
}
