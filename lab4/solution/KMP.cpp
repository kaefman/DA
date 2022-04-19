#include "KMP.h"

std::vector<int> CalculateSP(std::vector<int> &zArray, std::vector<std::string> &pat) {
    const unsigned long psize = pat.size();
    std::vector<int> spArray(psize);

    for (unsigned long j = psize - 1; j > 0; --j) {
        unsigned long i = j + zArray[j] - 1;
        spArray[i] = zArray[j];
    }
    
    return spArray;
}

std::vector<int> ZFunction(std::vector<std::string> &pat) {
    const unsigned long psize = pat.size();
    std::vector<int> zArray(psize);

    for (int i = 1, l = 0, r = 0; i < psize; ++i) {
        if (i <= r) {
            zArray[i] = std::min(r - i + 1, zArray[i - l]);
        }
        while (i + zArray[i] < psize && pat[zArray[i]] == pat[i + zArray[i]]) {
            ++zArray[i];
        }
        if (i + zArray[i] - 1 > r) {
            l = i; 
            r = i + zArray[i] - 1;
        }
    }
    return zArray;
}

std::vector<int> FailFunction(std::vector<std::string> &pattern) {
    unsigned long psize = pattern.size();

    std::vector<int> zArray = ZFunction(pattern);
    std::vector<int> spArray = CalculateSP(zArray, pattern);
    std::vector<int> f(psize + 1);
    f[0] = 0;

    for (int k = 1; k < psize; ++k) {
        f[k] = spArray[k - 1];
    }
    f[psize] = spArray[psize - 1];
    return f;
}

void KMP(std::vector<std::string> &pat) {
    std::vector<std::pair<std::pair<int, int>, std::string>> text;

    char c = '$';
    bool wordAdded = true;
    std::pair<std::pair<int, int>, std::string> temp;
    const unsigned long n = pat.size();
    temp.first.first = 1;
    temp.first.second = 1;
    int p = 0;
    int t = 0;
    std::vector<int> f = FailFunction(pat);
    do {
        while (text.size() < pat.size() && c != EOF) {
            c = getchar_unlocked();
            if (c == '\n') {
                if (!wordAdded) {
                    text.push_back(temp);
                    temp.second.clear();
                    wordAdded = true;
                }
                ++temp.first.second;
                temp.first.first = 1;
            } 
            else if (c == ' ' || c == '\t' || c == EOF) {
                if (wordAdded) {
                    continue;
                }
                text.push_back(temp);
                temp.second.clear();
                ++temp.first.first;
                wordAdded = true;
            } 
            else {
                if (temp.second.front() == '0') {
                    temp.second.erase(temp.second.begin());
                }
                temp.second.push_back(c);
                wordAdded = false;
            }
        }
        if (text.size() < pat.size()) {
            return;
        }
        while (p < n && pat[p] == text[t].second ) {
            ++p;
            ++t;
        }
        if (p == n) {
            printf("%d, %d\n", text[0].first.second, text[0].first.first);
        }
        if (p == 0) {
            ++t;
        }
        p = f[p];
        text.erase(text.begin(), text.begin() + t - p);
        t = p;
    } while (c != EOF);
}