#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
template<class T> using ordered_set = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update> ;
//order_of_key(x) = position of element x;
//find_by_order(i) = a[i];


mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
