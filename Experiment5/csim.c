#include "cachelab.h"
#include <string.h>
#include <stdlib.h>

#define MAXLEN (50)

int main(int argv, char **argc) {
    int hit_count = 0, miss_count = 0, eviction_count = 0;
    /** <s>组索引数 <E>关联度 <b>内存块内地址位数 <t>内存访问轨迹文件名 */
    long s, E, b;
    char tracefile[MAXLEN];
    memset(tracefile, 0, sizeof(tracefile));

    for (int i = 1; i != argv; ++i) {
        if (0 == strncmp("-s", argc[i], 2)) {
            s = atoi(argc[++i]);
        } else if (0 == strncmp("-E", argc[i], 2)) {
            E = atoi(argc[++i]);
        } else if (0 == strncmp("-b", argc[i], 2)) {
            b = atoi(argc[++i]);
        } else if (0 == strncmp("-t", argc[i], 2)) {
            strncpy(tracefile, argc[++i], sizeof(tracefile));
        }
    }

    printSummary(hit_count, miss_count, eviction_count);
    return 0;
}
