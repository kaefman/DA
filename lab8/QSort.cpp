#include "QSort.hpp"

uint64_t QSort (const std::vector<uint64_t> &mas) {
    uint64_t ans = 0, one = 0, three = 0;
    std::vector<uint64_t> nums(3, 0);
    for (uint64_t i = 0; i < mas.size(); ++i) {
        uint64_t index = mas[i] - 1;
        nums[index] += 1;
    }
    for (uint64_t i = 0; i < nums[0]; ++i) {
        uint64_t index = i;
        if (mas[index] != 1) {
            ++ans;
        }
        if (mas[index] == 3) {
            ++three;
        }
    }
    for (uint64_t i = 0; i < nums[2]; ++i) {
        uint64_t index = i + nums[0] + nums[1];
        if (mas[index] != 3) {
            ++ans;
        }
        if (mas[index] == 1) {
            ++one;
        }
    }
    ans -= one > three ? three : one;
    return ans; 
}