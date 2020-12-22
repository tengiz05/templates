// maximum subbarray in range where every
// element in the subarray is maximum of range 
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL);
#define all(x) (x).begin(), (x).end()
#define pb push_back
const int mod = 1e9+7, N = 2e5+5;
int msb(int val){return sizeof(int)*8-__builtin_clzll(val);}
int n, m, sz =1;
struct Node {
	int l, r, mx, toprop;
	int pr, sf, ans;
};
Node t[N*2];
void prop(int node){
	if(t[node].toprop == 0)return;
	t[node*2].toprop += t[node].toprop;
	t[node*2+1].toprop += t[node].toprop;
	t[node].mx += t[node].toprop;
	t[node].toprop = 0;
}
Node Merge(Node &l, Node &r){
	if(l.l == -1)return r;
	else if(r.r == -1)return l;
	Node res;
	res.l = l.l;
	res.r = r.r;
	res.mx = max(l.mx, r.mx);
	if(res.mx > l.mx){
		res.pr = 0;
		res.sf = r.sf;
		res.ans = r.ans;
	}else if(res.mx > r.mx){
		res.pr = l.pr;
		res.sf = 0;
		res.ans = l.ans;		
	}else {
		int ls = l.r-l.l;
		int rs = r.r-r.l;
		if(l.ans == ls){
			res.pr = ls+r.pr;
		}
		if(r.ans == rs){
			res.sf = rs+l.sf;
		}
		res.ans = max(max(l.ans, r.ans), l.sf+r.pr);
	}
	res.toprop = 0;
	return res;
}
int tp;
void update(int l, int r, int L ,int R, int node){
	prop(node);
	if(L >= r || R <= l)return;
	if(L >= l && R <= r){
		t[node].toprop += tp;
		prop(node);
		return;
	}int mid = t[node*2].r;
	update(l, r, L, mid, node*2);
	update(l, r, mid, R, node*2+1);
	t[node] = Merge(t[node*2], t[node*2+1]);
}
Node query(int l, int r, int L, int R, int node){
	prop(node);
	if(L >= r || R <= l)return {-1,-1,-1,-1,-1,-1,-1};
	if(L >= l && R <= r){
		return t[node];
	}int mid = t[node*2].r;
	auto m1 = query(l, r, L, mid, node*2);
	auto m2 = query(l, r, mid, R, node*2+1);
	return Merge(m1, m2);
}

void solve(int test_case){
	int i, j, q;
	cin >> q;
	set<int> temp;
	vector<tuple<short, int, int, int>> Q;
	for(i=0;i<q;i++){
		int typ;
		cin >> typ;
		if(typ == 1){
			int l, r, val;
			cin >> l >> r >> val;
			l--;
			Q.pb(make_tuple(typ, l, r, val));
			temp.insert(l);
			temp.insert(r);
		}else {
			int l, r, val=0;
			cin >> l >> r;
			l--;
			Q.pb(make_tuple(typ, l, r, val));
			temp.insert(l);
			temp.insert(r);
		}
	}
	while(sz < temp.size()){
		sz <<= 1;
	}
	while(temp.size() <= sz){
		int lst = *temp.rbegin();
		temp.insert(lst);
		temp.insert(lst+1);
	}if(temp.size() > sz+1)temp.erase(*temp.rbegin());
	vector<int> v;
	for(auto x : temp)v.pb(x);
	
	for(i=0;i<sz;i++){
		t[i+sz] = {v[i], v[i+1], 0, 0, v[i+1]-v[i], v[i+1]-v[i], v[i+1]-v[i]};
	}
	for(i=sz-1;i>0;i--){
		t[i] = Merge(t[i*2], t[i*2+1]);
	}
	for(auto [typ, l, r, val] : Q){
		if(typ == 1){
			//update
			tp = val;
			update(l,r,0,v.back(), 1);
		}else {
			//query
			auto ans = query(l, r, 0, v.back(), 1);
			cout << ans.ans << '\n';
		}
	}
	return;
}

signed main(){
	FASTIO;
	solve(1);
	return 0;
}




