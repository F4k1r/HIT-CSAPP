# 第四章
## 4.46
A: 并非如此，当REG为rsp时，这段代码修改了REG的值
B:
```asm
addq $8, REG
movq -8(%rsp), REG
```

## 4.48
```c
void bubble_p(long* data, long count) {
  long *i, *last;
  for (last = data+count-1; last > data; last--) {
    for (i = data; i < last; i++) {
      if (*(i+1) < *i) {
        /* swap adjacent elements */
        long t = *(i+1);
        *(i+1) = *i;
        *i = t;
      }
    }
  }
}
```

使用gcc编译`gcc -S -Og sort.c`获得如下代码：

```asm
	.file	"sort.c"
	.text
	.globl	bubble_p
	.type	bubble_p, @function
bubble_p:
.LFB0:
	.cfi_startproc
	leaq	-8(%rdi,%rsi,8), %rsi
	jmp	.L2
.L3:
	addq	$8, %rax
.L5:
	cmpq	%rsi, %rax
	jnb	.L7
	movq	8(%rax), %rdx
	movq	(%rax), %rcx
	cmpq	%rcx, %rdx
	jge	.L3
	movq	%rcx, 8(%rax)
	movq	%rdx, (%rax)
	jmp	.L3
.L7:
	subq	$8, %rsi
.L2:
	cmpq	%rdi, %rsi
	jbe	.L8
	movq	%rdi, %rax
	jmp	.L5
.L8:
	rep ret
	.cfi_endproc
.LFE0:
	.size	bubble_p, .-bubble_p
	.ident	"GCC: (GNU) 7.2.0"
	.section	.note.GNU-stack,"",@progbits
```

翻译成Y86代码：

```asm
.pos 0
    irmovq stack, %rsp
    call main
    halt
    
/** 测试数据 */
.align 8
data:
  .quad 0x0000000000000004
  .quad 0x0000000000000003
  .quad 0x0000000000000002
data_end:
  .quad 0x0000000000000001

main:
    irmovq data, %rdi
    irmovq data_end, %rsi
    call sort
    ret
    
sort:
    jmp L2
L3:
    irmovq  $8, %r8
	addq	%r8, %rax
L5:
/** cmpq	%rsi, %rax */
    rrmovq  %rax, %r8
    subq    %rsi, %r8 
	
	jge	L7
	mrmovq	8(%rax), %rdx
	mrmovq	(%rax), %rcx
	
/** cmpq	%rcx, %rdx */
    rrmovq  %rdx, %r8
    subq    %rcx, %r8 
	
	jge	L3
	rmmovq	%rcx, 8(%rax)
	rmmovq	%rdx, (%rax)
	jmp	L3
L7:
    irmovq  $8, %r8
	subq	%r8, %rsi
L2:
/** cmpq	%rdi, %rsi */
	rrmovq  %rsi, %r8
    subq    %rdi, %r8 
  
	jle	L8
	rrmovq	%rdi, %rax
	jmp	L5
L8:
	ret

.pos 500
stack:

```

使用条件传送修改代码

```asm
.pos 0
    irmovq stack, %rsp
    call main
    halt
    
/** 测试数据 */
.align 8
data:
  .quad 0x0000000000000004
  .quad 0x0000000000000003
  .quad 0x0000000000000002
data_end:
  .quad 0x0000000000000001

main:
    irmovq data, %rdi
    irmovq data_end, %rsi
    call sort
    ret
    
sort:
    jmp L2
L3:
    irmovq  $8, %r8
	addq	%r8, %rax
L5:
/** cmpq	%rsi, %rax */
    rrmovq  %rax, %r8
    subq    %rsi, %r8 
	
	jge	L7
	mrmovq	8(%rax), %rdx
	mrmovq	(%rax), %rcx
	
/**--------------------*/
/**     此处进行改写      */
    rrmovq  %rdx, %r8
    subq    %rcx, %r8
	
	cmovl	%rcx, 8(%rax)
	cmovl	%rdx, (%rax)
/**---------------------*/
	jmp	L3
L7:
    irmovq  $8, %r8
	subq	%r8, %rsi
L2:
/** cmpq	%rdi, %rsi */
	rrmovq  %rsi, %r8
    subq    %rdi, %r8 
  
	jle	L8
	rrmovq	%rdi, %rax
	jmp	L5
L8:
	ret

.pos 500
stack:

```

## 4.50

## 4.52

## 4.54

## 4.56

## 4.58