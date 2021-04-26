inline int emn(){return inf;}
inline int opmn(int a, int b){return min(a,b);}
inline int propmn(int a, int b){return a;}
inline int esm(){return 0;}
inline int opsm(int a, int b){return a+b;}
inline int propsm(int a, int b){return a*b;}
template <class S, S(*op)(S,S), S(*e)(),S(*prop)(S,S)>
struct segtree{
	vector<int> t, lz;
	int n, sz;
	segtree(vector<int> a){
		n = a.size();
		sz=1; while(sz < n)sz<<=1;
		t.assign(sz*2,e());
		for(int i=0;i<n;i++)t[i+sz] = a[i];
		for(int i=sz-1;i>0;i--)t[i] = op(t[i<<1],t[i<<1|1]);
		lz.assign(sz*2,0);
	}
	void push(int x, int len){
		t[x] += prop(lz[x],len);
		if(x < sz)lz[x<<1] += lz[x], lz[x<<1|1] += lz[x];
		lz[x] = 0;
	}
	int get(int l, int r, int L, int R, int x){
		push(x,R-L);
		if(L >= r || R <= l)return e();
		if(L >= l && R <= r){
			return t[x];
		}int mid = (L+R)/2;
		return op(get(l,r,L,mid,x<<1),get(l,r,mid,R,x<<1|1));
	}int get(int l, int r){return get(l,r,0,sz,1);}
	int val;
	void update(int l, int r, int L, int R, int x){
		push(x,R-L);
		if(L >= r || R <= l)return;
		if(L >= l && R <= r){
			lz[x] = val;
			push(x,R-L);
			return;
		}int mid = (L+R)/2;
		update(l,r,L,mid,x<<1);
		update(l,r,mid,R,x<<1|1);
		t[x] = op(t[x<<1],t[x<<1|1]);
	}void update(int l, int r, int v){val = v; update(l,r,0,sz,1);}
};
/// segtree<int,opmn,emn,propmn> mn(a);
