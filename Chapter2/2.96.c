//
// Created by along on 17-9-17.
//

#include <stdio.h>
typedef unsigned float_bits;

/**
 * 对于浮点数 f，这个函数计算 (int)f。
 * 如果 f 是 NaN，函数向0舍入。
 * 如果 f 不能用整数表示（例如，超出表示范围，或者它是一个 NaN），那么函数应该返回 0x80000000。
 * @param f
 * @return
 */
int float_f2i(float_bits f);
float U2F_BIT(unsigned U) {
    return *((float *) &U);
}
int main() {
    for (float_bits i = 0; i != 0xFF; ++i) {
        printf("%d   |  %d\n", (int) U2F_BIT(i), float_f2i(i));
    }

    return 0;
}
int float_f2i(float_bits f) {
    unsigned sign = f >> 31;
    unsigned exp = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;
    if (exp == 0xFF && frac != 0)
        return 0x80000000;
    else if (exp > 150) {
        frac = ((1 << 23) | frac) << ((exp - 150));
        return sign ? -frac : frac;
    } else {
        frac = ((1 << 23) | frac) >> ((150 - exp));
        return sign ? -frac : frac;
    }
}