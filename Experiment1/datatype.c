//
// Created by along on 17-10-10.
//

#include <stdio.h>
#include <string.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, size_t len) {
    size_t i;
    for (i = 0; i < len; ++i)
        printf(" %.2x", start[i]);
    printf("\n");
}

const char *mstring = "冯云龙";
const int intenger = 1160300202;
const long lintenger = 1160300202;
const long long llintenger = 1160300202;
const float floatnum = 411627199805247416.f;
const double doublenum = 411627199805247416;

//变量名、变量值、变量地址、变量对应16进制的内存各字节。
int main() {
    printf("变量名:mstring     变量值:%s   变量地址:%p  内存:", mstring, &mstring);
    show_bytes((byte_pointer) mstring, strlen(mstring));
    printf("变量名:intenger    变量值:%d   变量地址:%p  内存:", intenger, &intenger);
    show_bytes((byte_pointer) &intenger, sizeof(intenger));
    printf("变量名:lintenger   变量值:%ld  变量地址:%p  内存:", lintenger, &lintenger);
    show_bytes((byte_pointer) &lintenger, sizeof(lintenger));
    printf("变量名:llintenger  变量值:%lld 变量地址:%p  内存:", llintenger, &llintenger);
    show_bytes((byte_pointer) &llintenger, sizeof(llintenger));
    printf("变量名:floatnum    变量值:%f   变量地址:%p  内存:", floatnum, &floatnum);
    show_bytes((byte_pointer) &floatnum, sizeof(floatnum));
    printf("变量名:doublenum   变量值:%lf  变量地址:%p  内存:", doublenum, &doublenum);
    show_bytes((byte_pointer) &doublenum, sizeof(doublenum));

    return 0;
}