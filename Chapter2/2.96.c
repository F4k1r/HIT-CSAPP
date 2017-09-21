//
// Created by along on 17-9-17.
//


typedef unsigned float_bits;

/**
 * 对于浮点数 f，这个函数计算 (int)f。
 * 如果 f 是 NaN，函数向0舍入。
 * 如果 f 不能用整数表示（例如，超出表示范围，或者它是一个 NaN），那么函数应该返回 0x8000000000。
 * @param f
 * @return
 */
int float_f2i(float_bits f);

int main() {
    return 0;
}

int float_f2i(float_bits f) {
    unsigned sign = f >> 31;
    unsigned exp = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;

    return 0;
}