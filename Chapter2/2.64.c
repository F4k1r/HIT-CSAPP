//
// Created by along on 17-9-17.
//

#include <stdio.h>

/**
 * 如果x的任何一个奇数位为1则返回1,否则返回零
 * @param x
 * @return
 */
int any_odd_one(unsigned x) {

    unsigned bit_1 = (x & 0x01);
    unsigned bit_3 = ((x >> 2) & 0x01);
    unsigned bit_5 = ((x >> 4) & 0x01);
    unsigned bit_7 = ((x >> 6) & 0x01);
    unsigned bit_9 = ((x >> 8) & 0x01);
    unsigned bit_11 = ((x >> 10) & 0x01);
    unsigned bit_13 = ((x >> 12) & 0x01);
    unsigned bit_15 = ((x >> 14) & 0x01);
    unsigned bit_17 = ((x >> 16) & 0x01);
    unsigned bit_19 = ((x >> 18) & 0x01);
    unsigned bit_21 = ((x >> 20) & 0x01);
    unsigned bit_23 = ((x >> 22) & 0x01);
    unsigned bit_25 = ((x >> 24) & 0x01);
    unsigned bit_27 = ((x >> 26) & 0x01);
    unsigned bit_29 = ((x >> 28) & 0x01);
    unsigned bit_31 = ((x >> 30) & 0x01);

    return bit_1 | bit_3 | bit_5 | bit_7 | bit_9
           | bit_11 | bit_13 | bit_15 | bit_17
           | bit_19 | bit_21 | bit_23 | bit_25
           | bit_27 | bit_29 | bit_31;
}

int main() {
    for (unsigned i = 0; i < 10; ++i) {
        printf("Bits:%x Key:%ud IsOdd:%d\n", i, i, any_odd_one(i));
    }
    return 0;
}
