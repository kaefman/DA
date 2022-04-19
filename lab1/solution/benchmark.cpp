#include "pair.h"
#include "sort.h"
#include <chrono>
#include <algorithm>

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	TVector<TPair> vec;
	TPair p;
	unsigned int maxKey = 0;

    auto start = std::chrono::steady_clock::now();
	while(std::cin >> p.key >> p.value) {
		vec.PushBack(p);
		if (p.key > maxKey) {
			maxKey = p.key;
		}
		p.Reset();
	}
    auto finish = std::chrono::steady_clock::now();
	auto dur1 = finish - start;
	std::cerr << "input " << std::chrono::duration_cast<std::chrono::milliseconds>(dur1).count() << " ms" << std::endl;

    std::cout << "Number of elems is " << vec.Size() << std::endl;

    start = std::chrono::steady_clock::now();
	TVector<TPair> sortedVector = CountingSort(vec, maxKey);
    //    std::stable_sort(vector.Begin(), vector.End());
	finish = std::chrono::steady_clock::now();
	auto dur2 = finish - start;
	std::cerr << "sort " << std::chrono::duration_cast<std::chrono::milliseconds>(dur2).count() << " ms" << std::endl;

    start = std::chrono::steady_clock::now();
    std::cout << sortedVector;
    finish = std::chrono::steady_clock::now();
	auto dur3 = finish - start;
	auto dur = dur1 + dur2 + dur3;
	std::cerr << "output " << std::chrono::duration_cast<std::chrono::milliseconds>(dur3).count() << " ms" << std::endl;
	std::cerr << "all " << std::chrono::duration_cast<std::chrono::milliseconds>(dur).count() << " ms" << std::endl;
	return 0;
}