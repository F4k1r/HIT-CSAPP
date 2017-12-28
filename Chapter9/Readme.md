---
title: 第九章
author: 冯云龙
date: 2017/12/16
geometry: margin=2cm
documentclass: ctexart
output: pdf_document
---

# 9.12
A.
!ditaa(Answer)
~~~~~~
   13  12  11  10  9  8  7  6  5  4  3  2  1  0
 +---+---+---+---+--+--+--+--+--+--+--+--+--+--+
 | 0 | 0 | 0 | 0 | 1| 1| 1| 0| 1| 0| 1| 0| 0| 1|
 +---+---+---+---+--+--+--+--+--+--+--+--+--+--+
~~~~~~

B.

|    参数   |   值    |
|-----------|---------|
|   VPN     |   0x0E  |
|  TLP索引  |   0x02  |
|  TLB标记  |   0x03  |
|  TLB命中？|   否    |
|  缺页？   |   否    |
|  PPN      |  0x11   |

C.
!ditaa(Answer2)
~~~~~~
 11  10  9  8  7  6  5  4  3  2  1  0
+---+---+--+--+--+--+--+--+--+--+--+--+
| 0 | 1 | 0| 0| 0| 1| 1| 0| 1| 0| 0| 1|
+---+---+--+--+--+--+--+--+--+--+--+--+
~~~~~~

D.

|  参数   |   值   |
|---------|--------|
|字节索引 |  0x01  |
|缓存索引 |  0x0a  |
|缓存标记 |  0x11  |
|缓存命中?|   否   |
|返回的缓存字节| - |

# 9.14
假设有一个输入文件 hello.txt ，由字符串"Hello,world!\n"组成，编写一个C语言程序，
使用mmap将 hello.txt 的内容改变为"Jello,world!\n"。

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>

int main() {
    int fd;
    char *buf = NULL;
    struct stat stat;
    const char *path = "hello.txt";

    // 使用文件描述符
    fd = open(path, O_RDWR | O_CLOEXEC, 0);
    if (fd < 0) {
        perror("open()");
        exit(EXIT_FAILURE);
    }
    fstat(fd, &stat);

    // 使用mmap函数将文件映射到内存中
    buf = mmap(NULL, (size_t) stat.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    buf[0] = 'J';
    close(fd);
    exit(EXIT_SUCCESS);
}
```

# 9.16
确定下面对齐要求的每个组合的最小块大小。
假设：显式空闲链表、每个空闲块中有四个字节的pred和succ指针、不允许有效载荷的大小为0,并且头部和脚部存放在一个四字节的字中。

|对齐要求|已分配块|空闲块|最小块大小(字节)|
|---|---------|-------|--------------|
|单字|头部和脚部|头部和脚部|              |
|单字|头部无脚部|头部和脚部|              |
|双字|头部和脚部|头部和脚部|              |
|双字|头部无脚部|头部和脚部|              |

# 9.18
编写你自己的malloc和free版本，将它的运行时间和空间利用率与标准C库提供的malloc版本比较。