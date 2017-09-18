//
// Created by along on 17-9-17.
//

#include <stdio.h>
#include <limits.h>

unsigned int f2u(float f) {
    unsigned *u = (unsigned *) &f;
    return *u;
}

int float_le(float x, float y) {
    unsigned ux = f2u(x);
    unsigned uy = f2u(y);

    // 获取符号位
    unsigned sx = ux >> 31;
    unsigned sy = uy >> 31;

    // 比较下x,y的大小（仅使用ux,uy,sx,sy)
    return ((ux ^ uy) == 0) ||                                            // x,y完全相等
           (((ux & INT_MAX) == 0) && ((uy & INT_MAX) == 0)) ||            // 去除最高位x,y等于0
           ((sx == 1) && (sy == 0)) ||                                    // x为负，y为正并且都不是0
           ((sx == 0) && (sy == 0) && ((ux - uy) >> 31 == 1)) ||          // 符号同正 ux < uy
           ((sx == 1) && (sy == 1) && ((ux - uy) >> 31 == 0));            // 符号同负 ux > uy
}

int main() {
    printf("%x", float_le(3.0f,2.0f));
    return 0;
}