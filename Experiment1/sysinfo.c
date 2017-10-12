//
// Created by along on 17-10-12.
// 获取计算机系统的基本信息
// 大小端判断   		bool isLittleEndian()
// CPU的位数/字长		int cpuWordSize()
// CPUID（略）       调用cpuid机器指令
// MAC（略）         调用驱动程序函数
//

#include<stdio.h>
#include<stdbool.h>

#define cpuid(in, a, b, c, d)  asm("cpuid": "=a" (a), "=b" (b), "=c" (c), "=d" (d) : "a" (in))

bool isLittleEndian(void) {
    int var = 1;
    char *p = (char *) &var;
    return *p == 1;
}

int cpuWordSize(void) {
    return sizeof(void *);
}


void getMac() {

}

void get_cpuid() {

}

int main() {
    printf("本机CPU为\"%s\"。\n", isLittleEndian() ? "小端序" : "大端序");
    printf("本机器是%d位机\n", 8 * cpuWordSize());
    return 0;
}