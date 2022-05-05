struct Vector {
    int x, y;
    Vector(int x = 0, int y = 0) : x(x), y(y) {}
    Vector(const Vector &a, const Vector &b) : x(b.x - a.x), y(b.y - a.y){}
};

int side(const Vector &a) {
    if (a.y == 0)
        return a.x > 0 ? 0 : 2;
    return a.y > 0 ? 1 : 2;
}

bool operator<(const Vector &a, const Vector &b) {
    int A = side(a), B = side(b);
    if (A != B)
        return A < B;
    return 1LL * a.y * b.x < 1LL * a.x * b.y;
}
// counter clockwise
