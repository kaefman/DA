#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include "KMP.h"

int main() {
    auto start0 = std::chrono::steady_clock::now();
    std::string buf;
    std::vector<std::string> pattern;
    
    char c;
    while (true) {
        c = getchar_unlocked();
        if (c == ' ') {
            if (!buf.empty()) {
                pattern.push_back(buf);
            }
            buf.clear();
        }
        else if (c == '\n' || c == EOF) {
            if (!buf.empty()) {
                pattern.push_back(buf);
            }
            break;
        }
        else {
            buf.push_back(c);
        }
    }
    
    KMP(pattern);

    auto finish0 = std::chrono::steady_clock::now();
	auto dur0 = finish0 - start0;
	std::cerr << "all " << std::chrono::duration_cast<std::chrono::milliseconds>(dur0).count() << " ms" << std::endl;
    return 0;
}