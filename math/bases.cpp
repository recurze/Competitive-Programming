/**
 * File              : bases.cpp
 * Author            : recurze
 * Date              : 13:20 25.12.2018
 * Last Modified Date: 17:03 25.12.2018
 */

#include <string>
#include <algorithm>
#include <iostream>

int toDecimal(std::string n, int b) {
    std::string chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int res = 0, m = 1;
    std::reverse(n.begin(), n.end());
    for (int i = 0; n[i]; ++i) {
        res += chars.find(n[i], 0) * m;
        m *= b;
    }
    return res;
}

std::string fromDecimal(int n, int b) {
    std::string res = "";
    std::string chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    while (n) {
        res = res + chars[n%b];
        n /= b;
    }
    std::reverse(res.begin(), res.end());
    return res;
}

// std::stoi(str)
// to_string(n)
