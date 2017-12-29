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
    munmap(buf, (size_t) stat.st_size);
    close(fd);
    exit(EXIT_SUCCESS);
}
```

# 9.16

!ditaa(block)
~~~~~~
 31                         3  2  1  0
+----------------------------+--------+
|          块大小               |  a/f   |  头部
+----------------------------+--------+
|           pred(祖先)                  |
+-------------------------------------+
|           succ(后继)                  |
+-------------------------------------+
|                                     |
|                                     |
+-------------------------------------+
|                                     |
|            填充(可选)                   |
|                                     |
+----------------------------+--------+
|          块大小               |  a/f   |  脚部
+----------------------------+--------+
~~~~~~

|对齐要求|已分配块|空闲块|最小块大小(字节)|
|----|----------|-----------|------------|
|单字|头部 & 脚部|头部 & 脚部|     16     |
|单字|    头部   |头部 & 脚部|     16     |
|双字|头部 & 脚部|头部 & 脚部|     16     |
|双字|    头部   |头部 & 脚部|     16     |

# 9.18

```c
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "mm.h"
#include "memlib.h"

/* single word (4) or double word (8) alignment */
#define ALIGNMENT 8

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~0x7)

#define SIZE_T_SIZE (ALIGN(sizeof(size_t)))

int mm_init(void)
{
    return 0;
}

void *mm_malloc(size_t size)
{
    int newsize = ALIGN(size + SIZE_T_SIZE);
    void *p = mem_sbrk(newsize);
    if (p == (void *)-1)
	return NULL;
    else {
        *(size_t *)p = size;
        return (void *)((char *)p + SIZE_T_SIZE);
    }
}

void mm_free(void *ptr)
{
}

void *mm_realloc(void *ptr, size_t size)
{
    void *oldptr = ptr;
    void *newptr;
    size_t copySize;
    
    newptr = mm_malloc(size);
    if (newptr == NULL)
      return NULL;
    copySize = *(size_t *)((char *)oldptr - SIZE_T_SIZE);
    if (size < copySize)
      copySize = size;
    memcpy(newptr, oldptr, copySize);
    mm_free(oldptr);
    return newptr;
}
```