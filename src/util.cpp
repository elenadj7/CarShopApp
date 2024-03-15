#include <string>
#include <algorithm>
#include <chrono>

namespace csa{
    bool isNumber(const std::string& str) {
        return std::all_of(str.begin(), str.end(), [](unsigned char c) { return std::isdigit(c); });
    }

    bool validYear(const std::string& str){
        return isNumber(str) && std::stoi(str) >= 1900;
    }

    bool validMileage(const std::string& str){
        return isNumber(str) && str.length() < 7;
    }
}
