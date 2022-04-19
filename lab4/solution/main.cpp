#include <iostream>
#include <vector>
#include <string>
#include "KMP.h"

int main() {
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
    return 0;
}