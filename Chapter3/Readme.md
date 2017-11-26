# 第三章作业
## 3.58
```asm
decode2:
    subq    %rdx, %rsi # %rsi = y - z;
    imulq   %rsi, %rdi # %rdi = (y - z) * x;
    movq    %rsi, %rax # %rax = y - z;
    salq    $63,  %rax # %rax = (y - z) << 63;
    sarq    $63,  %rax # %rax = ((y - z) << 63) >> 63;
    xorq    %rdi, %rax # %rax = (((y - z) << 63) >> 63) ^ ((y - z) * x)
    ret
```
所以翻译为C代码即为:
```c
long decode2(long x, long y, long z) {
    return (((y - z) << 63) >> 63) ^ ((y - z) * x);
}
```

## 3.60
```asm
loop:
    movl  %esi, %ecx # %ecx=n;
    movl  $1,   %edx # %edx=1; --> mask 
    movl  $0,   %eax # %eax=0; --> result
    jmp   .L2
.L3:
    movq  %rdi, %r8  # %r8=x;
    andq  %rdx, %r8  # %r8=x&%rdx; -->x&mask
    orq   %r8,  %rax # %rax=%rax | (x&%rdx); -->result |= x & mask
    salq  %cl,  %rdx # %rdx=%rdx<<(n&0xFF);  -->mask = mask<<(n&0xFF)
.L2:
    testq %rdx, %rdx
    jne   .L3.       # if %rdx!=0 goto L3. -->mask!=0
    rep; ret
```
A:

|  变量   |        寄存器      |
|--------|-------------------|
|   x    |     %rdi,%r8      |
|   n    |     %esi,%ecx     |
|  mask  |       %rdx        |
| result |       %rax        |

B: 
```c
result = 0;
mask = 1;
```

C:
```c
mask != 0;
```

D:
```c
mask = mask << (n&0xFF)
```

E:
```c
result |= x & mask
```

F:
```c
long loop(long x, int n)
{
    long result = 0;
    long mask;
    for(mask = 1;mask != 0;mask = mask << (n&0xFF)){
        result |= x & mask;
    }
    return result;
}
```

## 3.62
```c
/* Enumerated type creates set of constants numbered 0 and upward */
typedef enum { MODE_A, MODE_B, MODE_C, MODE_D, MODE_E } mode_t;

long switch3(long *p1, long *p2, mode_t action) {
    long result = 0;
    switch (action) {
    case MODE_A:result = *p2;
        action = *p1;
        *p2 = action;
        break;
    case MODE_B:result = *p1 + *p2;
        *p1 = result;
        break;
    case MODE_C:*p1 = 59;
        result = *p2;
        break;
    case MODE_D:result = *p2;
        *p1 = result;
        result = 27;
        break;
    case MODE_E:result = 27;
        break;
    default:result = 12;
    }
    return result;
}
```

## 3.64
```c
store_ele:
    leaq  (%rsi, %rsi, 2), %rax  # %rax = 3 * j
    leaq  (%rsi, %rax, 4), %rax  # %rax = 13 * j
    leaq  %rdi, %rsi             # %rsi = i
    salq  $6, %rsi               # %rsi * = 64
    addq  %rsi, %rdi             # %rdi = 65 * i
    addq  %rax, %rdi             # %rdi = 65 * i + 13 * j
    addq  %rdi, %rdx             # %rdx = 65 * i + 13 * j + k
    movq  A(, %rdx, 8), %rax     # %rax = A + 8 * (65 * i + 13 * j + k)
    movq  %rax, (%rcx)           # *dest = A[65 * i + 13 * j + k]
    movl  $3640, %eax            # sizeof(A) = 3640
    ret
```

A:
```c
&D[i][j][k] = XD + L(i * S * T + j * T + k)
```

B:
```c
S * T == 65                   R = 7
T == 13                  ==>  S = 5
S * T * R * 8 == 3640         T = 13
```

## 3.66
```asm
sum_col:
    leaq   1(, %rdi, 4), %r8        # %r8 = 4 * n + 1
    leaq   (%rdi, %rdi, 2), %rax    # result = 3 * n
    movq   %rax, %rdi               # %rdi = 3 * n
    testq  %rax, %rax
    jle    .L4                      # if %rax <= 0, goto L4
    salq   $3, %r8                  # %r8 = 8 * (4 * n + 1)
    leaq   (%rsi, %rdx, 8), %rcx    # %rcx = A[0][j]
    movl   $0, %eax                 # result = 0
    movl   $0, %edx                 # i = 0
.L3:
    addq   (%rcx), %rax             # result = result + A[i][j]
    addq   $1, %rdx                 # i += 1
    addq   %r8, %rcx                # 这里每次+8*(4n+1),说明每一行有4n+1个，因此NC(n)为4*n+1
    cmpq   %rdi, %rdx
    jne    .L3                      # 这里说明一直循环到3*n才结束，所以可以说明一共有3n行，因此NR(n)为3*n
    rep; ret
.L4:
    movl $0, %eax
    ret
```
