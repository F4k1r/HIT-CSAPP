//
// Created by along on 17-9-17.
//

#include <stdio.h>

/**
 * 如果是偶数则返回1,否则返回零
 * @param x
 * @return
 */
int any_odd_one(unsigned x) {
    return (x & 0x00000001) == 1;
}

int main() {
    for (unsigned i = 0; i < 10; ++i) {
        printf("Key:%d IsOdd:%d\n", i, any_odd_one(i));
    }
    return 0;
}