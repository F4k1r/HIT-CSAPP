# 第五章
## 5.14
```
 +----+                          +----+
 |sum |                          | i  |
 +----+                          +----+
   |                               |
   v                               |
 +----+       +----+  +----+       |
 |add |<------|mul |<-|load|<------+
 +----+       +----+  +----+       |
   |                               |
   v                               |
 +----+       +----+  +----+       |
 |add |<------|mul |<-|load|<------+
 +----+       +----+  +----+       |
   |                               |
   v                               |
 +----+       +----+  +----+       |
 |add |<------|mul |<-|load|<------+
 +----+       +----+  +----+       |
   |                               |
   v                               |
 +----+       +----+  +----+       |
 |add |<------|mul |<-|load|<------+
 +----+       +----+  +----+       |
   |                               |
   v                               |
 +----+       +----+  +----+       |
 |add |<------|mul |<-|load|<------+
 +----+       +----+  +----+       |
   |                               |
   v                               |
 +----+       +----+  +----+       |
 |add |<------|mul |<-|load|<------+
 +----+       +----+  +----+       |
   |                               |
   |                               v
   |                             +----+
   |                             |add |
   |  <------- 关键路径           +----+
   |                               |
   |                               |
   v                               v
 +----+                          +-+--+
 |sum |                          | i  |
 +----+                          +----+
```

A:sum的每一次更新需要6个时钟周期，采用6x1展开，循环次数为n/6，而n/6*6=n,CPE接近1，
已经达到了CPE下界，不可能比1更小了。(对于标量)

B:浮点数据的加法运算器延迟为3，做k展开，n/k*(3*k)=3n,展开也无法改变延迟界限，所以展开无法改善性能。
对于浮点运算来说，循环展开带来的索引计算的操作本身就不是瓶颈，所以不会有所改善。

```c
void inner4(vec_ptr u, vec_ptr v, data_t *dest) {
  long i;
  long length = vec_length(u);
  data_t *udata = get_vec_start(u);
  data_t *vdata = get_vec_start(v);
  data_t sum = (data_t) 0;

  for (i = 0; i < length-6; i+=6) {
    sum = sum + udata[i] * vdata[i] +
      udata[i+1] * vdata[i+1] +
      udata[i+2] * vdata[i+2] +
      udata[i+3] * vdata[i+3] +
      udata[i+4] * vdata[i+4] +
      udata[i+5] * vdata[i+5];
  }
  for(; i < length; i++) {
    sum = sum + udata[i] * vdata[i];
  }
  *dest = sum;
}
```

## 5.16

```c
void inner4(vec_ptr u, vec_ptr v, data_t *dest) {
  long i;
  long length = vec_length(u);
  data_t *udata = get_vec_start(u);
  data_t *vdata = get_vec_start(v);
  data_t sum = (data_t) 0;

  for (i = 0; i < length-6; i+=6) {
    sum = sum +
      (
        udata[i] * vdata[i] +
        udata[i+1] * vdata[i+1] +
        udata[i+2] * vdata[i+2] +
        udata[i+3] * vdata[i+3] +
        udata[i+4] * vdata[i+4] +
        udata[i+5] * vdata[i+5]
      );
  }
  for(; i < length; i++) {
    sum = sum + udata[i] * vdata[i];
  }
  *dest = sum;
}
```

## 5.18

```c
// 消除不必要的内存引用
double poly(double a[], double x, long degree) {
  long i;
  double result = a[0];
  double xpwr = x;
  for (i = 1; i <= degree; i++) {
    result += a[i] * xpwr;
    xpwr = x * xpwr;
  }
  return result;
}
```


```c
// 6x3a循环展开
double poly(double a[], double x, long degree) {
  long i = 1;
  double result = a[0];
  double result1 = 0;
  double result2 = 0;

  double xpwr = x;
  double xpwr1 = x * x * x;
  double xpwr2 = x * x * x * x * x;

  double xpwr_step = x * x * x * x * x * x;
  for (; i <= degree - 6; i+=6) {
    result = result + (a[i]*xpwr + a[i+1]*xpwr*x);
    result1 = result1 + (a[i+2]*xpwr1 + a[i+3]*xpwr1*x);
    result2 = result2 + (a[i+4]*xpwr2 + a[i+5]*xpwr2*x);

    xpwr *= xpwr_step;
    xpwr1 *= xpwr_step;
    xpwr2 *= xpwr_step;
  }

  for (; i <= degree; i++) {
    result = result + a[i]*xpwr;
    xpwr *= x;
  }

  return result + result1 + result2;
}
```


```
// honor版本
double poly(double a[], double x, long degree) {
  long i;
  double result = a[degree];
  for (i = degree-1; i >= 0; i--) {
    result = a[i] + x*result;
  }
  return result;
}
```