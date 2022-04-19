#include "pair.h"
#include "sort.h"
#include <algorithm>

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	TVector<TPair> vec;
	TPair p;
    unsigned int maxKey = 0;
    
	while(std::cin >> p.key >> p.value) {
		vec.PushBack(p);
		if (p.key > maxKey) {
			maxKey = p.key;
		}
		p.Reset();
	}

	TVector<TPair> sortedVector = CountingSort(vec, maxKey);
    std::cout << sortedVector;
	return 0;
}