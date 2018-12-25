/**
 * File              : basesTest.cpp
 * Author            : recurze
 * Date              : 16:30 25.12.2018
 * Last Modified Date: 17:04 25.12.2018
 */

#include "bases.cpp"

#include <iostream>

std::string testStrings[37][10000];
int ans[37][100000];
void test_toDecimal() {
    for (int i = 2; i < 37; ++i) {
        for (int j = 0; j < 10000; ++j) {
            std::cin >> testStrings[i][j];
            ans[i][j] = toDecimal(testStrings[i][j], i);
            std::cout<<ans[i][j]<<'\n';
        }
    }
}

#include <cassert>
void test_fromDecimal() {
    for (int i = 2; i < 37; ++i) {
        for (int j = 0; j < 10000; ++j) {
            assert (fromDecimal(ans[i][j], i) == testStrings[i][j]);
        }
    }
}

int main(){
    test_toDecimal();
    test_fromDecimal();
}
