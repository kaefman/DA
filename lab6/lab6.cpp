#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

class TSuperAlg {
    public:
        static const int BASE = 10000;
        static const int RADIX = 4;
        TSuperAlg() = default; 
        TSuperAlg(const std::string &s) {
            Initialize(s);
        }
        void Initialize(const std::string &str);

        friend std::istream& operator>>(std::istream &in, TSuperAlg &rhs);
        friend std::ostream& operator<<(std::ostream &out, const TSuperAlg& rhs);

        TSuperAlg operator-(const TSuperAlg &rhs) const;
        TSuperAlg operator+(const TSuperAlg &rhs) const;
        TSuperAlg operator/(const TSuperAlg &rhs) const;
        TSuperAlg operator*(const TSuperAlg &rhs) const;
        TSuperAlg Pow(int p);

        bool operator<(const TSuperAlg &rhs) const;
        bool operator>(const TSuperAlg &rhs) const;
        bool operator==(const TSuperAlg &rhs) const;
    private:
        void DeleteLeadingZeros();
        std::vector<int32_t> _data;

};

// using int100500_t = uint64_t;
using int100500_t = TSuperAlg;

void TSuperAlg::Initialize(const std::string &str) {
    int size = static_cast<int>(str.size());
    for (int i = size - 1; i >= 0; i = i - TSuperAlg::RADIX) {
        if (i < TSuperAlg::RADIX) {
            _data.push_back(static_cast<int32_t>(atoll(str.substr(0, i + 1).c_str())));
        }
        else {
            _data.push_back(static_cast<int32_t>(atoll(str.substr(i - TSuperAlg::RADIX + 1, TSuperAlg::RADIX).c_str())));
        }
    }
    DeleteLeadingZeros();
}

TSuperAlg TSuperAlg::operator+(const TSuperAlg &rhs) const {
    TSuperAlg res;
    int32_t carry = 0;
    size_t n = std::max(rhs._data.size(), _data.size());
    res._data.resize(n);
    for (size_t i = 0; i < n; ++i) {
        int32_t sum = carry;
        if (i < rhs._data.size()) {
            sum += rhs._data[i];
        }
        if (i < _data.size()) {
            sum += _data[i];
        }
        carry = sum / TSuperAlg::BASE;
        res._data[i] = sum % TSuperAlg::BASE;
    }
    if (carry != 0) {
        res._data.push_back(1);
    }
    res.DeleteLeadingZeros();
    return res;
}


TSuperAlg TSuperAlg::operator-(const TSuperAlg &rhs) const {
    TSuperAlg res;
    int32_t carry = 0;
    size_t n = std::max(rhs._data.size(), _data.size());
    res._data.resize(n + 1, 0);
    for (size_t i = 0; i < n; ++i) {
        int32_t diff = _data[i] - carry;
        if (i < rhs._data.size()) {
            diff -= rhs._data[i];
        }

        carry = 0;
        if (diff < 0) {
            carry = 1;
            diff += TSuperAlg::BASE;
        }
        res._data[i] = diff % TSuperAlg::BASE;
    }

    res.DeleteLeadingZeros();
    return res;
}

TSuperAlg TSuperAlg::operator*(const TSuperAlg &rhs) const {
    size_t n = _data.size() * rhs._data.size();
    TSuperAlg res;
    res._data.resize(n + 1);

    int k = 0;
    int r = 0;
    for (size_t i = 0; i < _data.size(); ++i) {
        for (size_t j = 0; j < rhs._data.size(); ++j) {
            k = rhs._data[j] * _data[i] + res._data[i + j];
            r = k / TSuperAlg::BASE;
            res._data[i + j + 1] = res._data[i + j + 1] + r;
            res._data[i + j] = k % TSuperAlg::BASE;
        }
    }
    res.DeleteLeadingZeros();
    return res; 
}

 TSuperAlg TSuperAlg::operator/(const TSuperAlg &rhs) const {
    TSuperAlg res("0"), cv("0");
    res._data.resize(_data.size());

    for (int i = (int)_data.size() - 1; i >= 0; --i) {
        cv._data.insert(cv._data.begin(), _data[i]);
        if (!cv._data.back()) {
            cv._data.pop_back();
        }
        int x = 0, l = 0, r = BASE;
        while (l <= r) {
            int m = (l + r) / 2;
            TSuperAlg cur = rhs * TSuperAlg(std::to_string(m));
            if ((cur < cv) || (cur == cv)) {
                x = m;
                l = m + 1;
            }
            else {
                r = m - 1;
            }
        }
        res._data[i] = x;
        cv = cv - rhs * TSuperAlg(std::to_string(x));
    }
    res.DeleteLeadingZeros();
    return res;
}

TSuperAlg TSuperAlg::Pow(int p) {
    TSuperAlg res("1");
    while (p > 0) {
        if (p % 2 == 1) {
            res = res * *this;
        }
        *this = *this * *this;
        p /= 2;
    }
    return res;
}


bool TSuperAlg::operator<(const TSuperAlg &rhs) const {
    if (_data.size() != rhs._data.size()) {
        return _data.size() < rhs._data.size();
    }

    for (int i = _data.size() - 1; i >= 0; --i) {
        if (_data[i] != rhs._data[i]) {
            return _data[i] < rhs._data[i];
        }
    }
    return false;
}

bool TSuperAlg::operator==(const TSuperAlg &rhs) const {
    if (_data.size() != rhs._data.size()) {
        return false;
    }

    for (int i = _data.size() - 1; i >= 0; --i) {
        if (_data[i] != rhs._data[i]) {
            return false;
        }
    }
    return true;
}

void TSuperAlg::DeleteLeadingZeros() {
    while (!_data.empty() && _data.back() == 0) _data.pop_back();
}

std::istream& operator>>(std::istream &in, TSuperAlg &rhs) {
    std::string str;
    in >> str;
    rhs.Initialize(str);
    return in;
}

std::ostream& operator<<(std::ostream &out, const TSuperAlg& rhs) {
    if (rhs._data.empty()) {
        out << "0";
        return out;
    }

    out << rhs._data.back();
    for (int i = rhs._data.size() - 2; i >= 0; --i) {
        out << std::setfill('0') << std::setw(TSuperAlg::RADIX) << rhs._data[i];
    }
    return out;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string str1, str2;
    char action;
    while (std::cin >> str1 >> str2 >> action) {
        int100500_t num1(str1), num2(str2);
        if (action == '+') {
            int100500_t res = num1 + num2;
            std::cout << res << std::endl;
        }
        else if (action == '-') {
            if (num1 < num2) {
                std::cout << "Error\n";
                continue;
            }
            int100500_t res = num1 - num2;
            std::cout << res << "\n";
        }
        else if (action == '*') {
            int100500_t res = num1 * num2;
            std::cout << res << "\n";
        }
        else if (action == '/') {
            if (str2 == "0") {
                std::cout << "Error\n";
                continue;
            }
            int100500_t res = num1 / num2;
            std::cout << res << "\n";
        }
        else if (action == '^') {
            if (str1 == "0") {
                if (str2 == "0") {
                    std::cout << "Error\n";
                    continue;
                }
                else {
                    std::cout << "0\n";
                    continue;
                }
            }
            if (str1 == "1") {
                std::cout << "1\n";
                continue;
            }
            int100500_t res = num1.Pow(std::stoi(str2));
            std::cout << res << "\n";
        }
        else if (action == '<') {
            std::cout << ((num1 < num2) ? "true\n" : "false\n");
        }
        else if (action == '>') {
            std::cout << ((num2 < num1) ? "true\n" : "false\n");
        }
        else if (action == '=') {
            std::cout << ((num1 == num2) ? "true\n" : "false\n");
        }
    }
    return 0;
}