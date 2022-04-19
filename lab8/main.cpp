#include <iostream>
#include <vector>

#include "QSort.hpp"

int main () {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    uint64_t ans, count;
    std::vector<uint64_t> mas;
    std::cin >> count;
    for (uint64_t i = 0; i < count; ++i) {
        uint64_t el;
        std::cin >> el;
        mas.push_back(el);
    }
    ans = QSort(mas);
    std::cout << ans << '\n';
    return 0;
}