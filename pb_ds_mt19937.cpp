#include <ext/pb_ds/assoc_container.hpp>
template<typename T>
using Set = __gnu_pbds::tree<T, __gnu_pbds::null_type, std::less<T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> ;


std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
//example of use
int t = std::uniform_int_distribution<int>(0,1000000000)(rng);
int x = rng() % 100;
