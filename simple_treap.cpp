#define ar array
struct treap{
	int data, pr, sz;
	ar<treap*, 2> kids;
	treap(int data);
};
int size(treap* me){
	return me == NULL? 0:me->sz;
}

void recalc(treap *me){
	if(me == NULL)return;
	me->sz = 1;
	for(treap* t:me->kids)if(t != NULL)me->sz += t->sz;
}
// TODO prop function

treap* merge(treap *l, treap *r){
	if(l == NULL)return r;
	if(r == NULL)return l;
	if(l->pr < r->pr){
		l->kids[1] = merge(l->kids[1], r);
		recalc(l);
		return l;
	}else {
		r->kids[0] = merge(l, r->kids[0]);
		recalc(r);
		return r;
	}
}
ar<treap*, 2> split(treap *me, int pos){
	if(me == NULL)return {NULL, NULL};
	if(size(me->kids[0]) >= pos){
		ar<treap*, 2> left = split(me->kids[0], pos);
		me->kids[0] = left[1];
		recalc(me);
		return {left[0], me};
	}else {
		pos -= size(me->kids[0])+1;
		ar<treap*, 2> right= split(me->kids[1], pos);
		me->kids[1] = right[0];
		recalc(me);
		return {me, right[1]};
	}
}
 
treap::treap(int data){
	kids = {NULL, NULL};
	this->data = data;
	recalc(this);
	int t = uniform_int_distribution<int>(0, N)(rng);
	this->pr = t;
}

void show(treap *me){
	if(me == NULL)return;
	show(me->kids[0]);
	cout << (me->data) << ' ';
	show(me->kids[1]);
}
