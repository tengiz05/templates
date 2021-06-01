#include <bits/stdc++.h>
using i64 = long long;
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
struct Tnode{
    int val, dp, lz, res;
    std::pair<int, int> smx;
    int pr, sz;
    Tnode *l, *r;
    Tnode(int v, int d);
};
inline int size(Tnode *me){
    return ((me==NULL)?0:me->sz);
}
inline void push(Tnode *me){
    if(me == NULL)return;
    me->smx.first += me->lz;
    me->val += me->lz;
    if(me->l != NULL)me->l->lz+=me->lz;
    if(me->r != NULL)me->r->lz+=me->lz;
    me->lz = 0;
}
void recalc(Tnode *me){
    if(me == NULL)return;
    push(me->l);
    push(me->r);
    me->sz = 1 + size(me->l) + size(me->r);
    me->smx = {me->val, me->dp};
    me->res = me->dp;
    if(me->l != NULL)me->res=std::min(me->res, me->l->res);
    if(me->r != NULL)me->res=std::min(me->res, me->r->res);
    if(me->l != NULL)me->smx=std::max(me->smx, me->l->smx);
    if(me->r != NULL)me->smx=std::max(me->smx, me->r->smx);
    return;
}
Tnode::Tnode(int v, int d){
    lz = 0;
    val = v;
    dp = d;
    l = r = NULL;
    pr = rng() % int(2e9);
    recalc(this);
}
struct treap{
    Tnode *root;
    treap(){root = NULL;}
    std::pair<Tnode*,Tnode*> split(Tnode *x, int inLeft){
        push(x);
        if(x == NULL)return {NULL, NULL};
        if(size(x->l) >= inLeft){
            auto t = split(x->l,inLeft);
            x->l = t.second;
            recalc(x);
            return {t.first, x};
        }else {
            auto t = split(x->r,inLeft - size(x->l)-1);
            x->r = t.first;
            recalc(x);
            return {x, t.second};
        }
    }
    Tnode* merge(Tnode *L, Tnode *R){
        push(L);
        push(R);
        if(L == NULL)return R;
        if(R == NULL)return L;
        if(L->pr > R->pr){
            L->r = merge(L->r,R);
            recalc(L);
            return L;
        }else {
            R->l = merge(L,R->l);
            recalc(R);
            return R;
        }
    }
    void push_back(int x, int dp){
        Tnode *t = new Tnode(x, dp);
        root = merge(root, t);
        return;
    }
    int get(int l, int r){
        auto R = split(root,r);
        auto L = split(R.first,l);
        int ans = L.second->smx.first;
        root = merge(merge(L.first, L.second),R.second);
        return ans;
    }
    int get_all(){
        if (root == NULL) return 1e9;
        return root->res;
    }
    void update(int val){
        if (root == NULL) return;
        root->lz += val;
        push(root);
    }
    void show(Tnode *x){
        if(x == NULL)return;
        push(x);
        show(x->l);
        std::cout << x->val << ' ' << x->dp << "\n";
        show(x->r);
        return;
    }
    void print(){
        std::cout << "-----------begin-----------\n";
        show(root);
        std::cout << "------------end------------\n";
        return;
    }
    bool found;
    int find(Tnode *x, const std::pair<int, int> t){
        if(x == NULL)return 0;
        push(x);
        push(x->l);
        push(x->r);
        if(x->l == NULL || x->l->smx < t){
            if(std::pair<int, int>{x->val, x->dp} == t)found = true;
            if(std::pair<int, int>{x->val, x->dp} >= t)return 0 + size(x->l);
            else return find(x->r, t)+1+size(x->l);
        }else {
            return find(x->l, t);
        }
    }
    int order_of_key(const std::pair<int, int> x){
        return find(root, x);
    }
    void insert(int x, int dp){
        int p = find(root, std::pair<int, int> {x, dp});
        auto [l, r] = split(root, p);
        Tnode *t = new Tnode(x, dp);
        root = merge(merge(l, t), r);
    }
    bool erase(int x, int dp) {
        found = false;
        int p = find(root, std::pair<int, int> {x, dp});
        if (!found) return false;
        auto [l, r] = split(root, p);
        auto [L, R] = split(r, 1);
        root = merge(l, R);
        return true;
    }
};
/* instructions:

t.push_back(x, dp)
t.order_of_key(x, dp)
t.get(l, r)  ->  in range [l, r)
t.insert(x, dp)
t.erase(x, dp)

*/
constexpr int N = 3e5 + 5;
int pr[2][N], dp[N];
int main() {
    freopen("redistricting.in", "r", stdin);
    freopen("redistricting.out", "w", stdout);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, k;
    std::cin >> n >> k;
    std::string s;
    std::cin >> s;
    for (int i = 0; i < n; i++) {
        pr[std::string("HG").find(s[i])][i + 1] = 1;
        pr[0][i + 1] += pr[0][i];
        pr[1][i + 1] += pr[1][i];
    }
    memset(dp, 0x3f, sizeof dp);
    dp[0] = 0;
    treap bad, good;
    bad.push_back(0, 0);
    for (int i = 1; i <= n; i++) {
        if (s[i - 1] == 'H') {
            bad.update(-1);
            good.update(-1);
            int p = bad.order_of_key({-1, 1e9});
            auto [L, R] = bad.split(bad.root, p);
            bad.root = R;
            good.root = good.merge(good.root, L);
        } else {
            bad.update(1);
            good.update(1);
            int p = good.order_of_key({-1, 1e9});
            auto [L, R] = good.split(good.root, p);
            good.root = L;
            bad.root = bad.merge(R, bad.root);
        }
        dp[i] = std::min(bad.get_all() + 1, good.get_all());
        bad.insert(0, dp[i]);
        if (i - k >= 0) {
            int p1 = pr[1][i] - pr[1][i - k];
            int p2 = pr[0][i] - pr[0][i - k];
            if (p1 - p2 < 0) assert(good.erase(p1 - p2, dp[i - k]));
            else assert(bad.erase(p1 - p2, dp[i - k]));
        }
    }
    std::cout << dp[n] << "\n";
    return 0;
}
