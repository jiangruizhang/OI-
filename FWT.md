# FWT

快速计算如下形式的卷积：
$$
C_{i}=\sum_{j\bigoplus k=i}A_jB_k
$$
其中$\bigoplus$代表一种二进制运算，$A_jB_k$就是简单的乘法。

基本思路就是对数组进行$FWT$，得到$FWT[A],FWT[B]$，这两个也是数组且长度与原数组相同，都是一个$2$的幂。然后对应位置相乘，得到同样意义下的$FWT[C]$，然后对$FWT[C]$进行逆变换得到$C$，但是对于不同二进制处理方法不同，所以分类讨论。

设$FA,FB,FC$分别表示$A,B,C$进行$FWT$后得到的数组。

### OR

对于一个一个数组$a$，其$FWT$后得到的$Fa$数组，定义如下：
$$
Fa_{i}=\sum_{j|i=i}a_j
$$
首先证明这个是对的：
$$
\begin{aligned}
FA_iFB_i & = \sum_{j_1|i=i}A_{j1}\sum_{j_2|i=i}B_{j_2}\\
 & =\sum_{j_1|i=i}\sum_{j_2|i=i}A_{j1}B_{j_2}\\
 & = \sum_{(j1|j2)|i=i}A_{j_1}B_{j_2}\\
 & = \sum_{k|i=i}\sum_{j_1|j_2=k}A_{j_1}B_{j_2}\\
 & = \sum_{k|i=i}C_k\\
 & = FC_{i}
\end{aligned}
$$
那么考虑对于一个数组$a$怎么计算$Fa$，这里用分治，这里直接用非递归。

考虑将整个数组分成许多个长度为$2$的幂的区间，从小到大合并（逆分治），此时的$Fa_i$是对其和式中的$j$再加一个$j$和$i$目前在同一个区间中，为了方便用$Fa_{L,i}$，表示合并到长度为$L$的时候$Fa_{i}$的取值。

可以发现对于目前要计算的一个区间$[l,r]$，因为所有区间的长度都是$2$的幂，所以这个区间中的数在二进制表示下有一段相同的前缀，然后区间前一半的数和后一半的数最高位分别为$0$和$1$，之后的二进制位在两半中会各出现一次，并且相对位置差为$\frac{L}{2}$，那么就可以合并了。

相同的前缀可以不考虑。对于前一半，由于最高位是$0$，所以它的子集最高位不能是$1$，那么就有$\forall 0\le i <\frac{L}{2},Fa_{L,l+i}=Fa_{\frac{L}{2},l+i}$；同理，后一半的最高位是$1$，它子集的最高位可以是$0$或$1$，那么就有$\forall 0 \le i < \frac{L}{2},Fa_{L,l+\frac{L}{2}+i}=Fa_{\frac{L}{2},l+i}+Fa_{\frac{L}{2},l+\frac{L}{2}+i}$。这样就合并完了。

对于逆变换，可以从大到小逆推，即用$Fa_{L}$计算$Fa_{\frac{L}{2}}$。这个就是解二元一次方程组，解就是
$$
\forall 0\le i <\frac{L}{2},Fa_{\frac{L}{2},l+i}=Fa_{L,l+i},Fa_{\frac{L}{2},l+\frac{L}{2}+i}=Fa_{L,l+\frac{L}{2}+i}-Fa_{L,l+i}
$$

### AND

$AND$其实和$OR$差不多，其$FWT$定义如下：
$$
Fa_{i}=\sum_{j\&i=i}a_j
$$
证明也类似：
$$
\begin{aligned}
FA_iFB_i & = \sum_{j_1\&i=i}A_{j1}\sum_{j_2\&i=i}B_{j_2}\\
 & =\sum_{j_1\&i=i}\sum_{j_2\&i=i}A_{j1}B_{j_2}\\
 & = \sum_{(j1\&j2)\&i=i}A_{j_1}B_{j_2}\\
 & = \sum_{k\&i=i}\sum_{j_1\&j_2=k}A_{j_1}B_{j_2}\\
 & = \sum_{k\&i=i}C_k\\
 & = FC_{i}
\end{aligned}
$$
计算方法也类似，也是根据在高位的$0$，$1$快速计算，$FWT$如下：
$$
\forall 0\le i < \frac{L}{2},
Fa_{L,l+i}=Fa_{\frac{L}{2},l+i}+Fa_{\frac{L}{2},l+\frac{L}{2}+i},
Fa_{L,l+\frac{L}{2}+i}=Fa_{\frac{L}{2},l+\frac{L}{2}+i}
$$
逆变换也是解方程，$UFWT$如下：
$$
\forall 0\le i < \frac{L}{2},
Fa_{\frac{L}{2},l+i}=Fa_{L,l+i}-Fa_{L,l+\frac{L}{2}+i},
Fa_{\frac{L}{2},l+\frac{L}{2}+i}=Fa_{L,l+\frac{L}{2}+i}
$$

### XOR

$XOR$的$FWT$很神奇，不知道怎么是怎么想出来的，它利用了一个函数的性质：

##### $f(x)$的性质

有函数$f(x)$，表示$x$在二进制下$1$的个数的奇偶性，那么$\forall i,j,k,f(i\&k) \operatorname{xor} f(j\&k)=f((i \operatorname{xor} j)\&k)$

证明：考虑$i,j,k$在某一位上分别选了$0,1$，对三个函数值的影响，发现若$k$选了$0$，三个函数值都不变，于是考虑$k=1$，$i,j$任意的情况，这里就省略了

##### 应用

这里的$FWT$如下：
$$
Fa_{i}=\sum_{f(j \& i)=0}a_{j}-\sum_{f(j\&i)=1} a_{j}
$$
证明：
$$
\begin{aligned}
FA_iFB_i & =\Big(\sum_{f(k_1\&i)=0}a_{k_1}-\sum_{f(k_1\&i)=1}a_{k_1}\Big)\Big( \sum_{f(k_2\&i)=0} b_{k_2}-\sum_{f(k_2\&i)=1} b_{k_2} \Big) \\
& = \sum_{f(k_1\&i)=0,f(k_2\&i)=0}a_{k_1}b_{k_2}+
\sum_{f(k_1\&i)=1,f(k_2\&i)=1}a_{k_1}b_{k_2}-
\sum_{f(k_1\&i)=0,f(k_2\&i)=1}a_{k_1}b_{k_2}-
\sum_{f(k_1\&i)=1,f(k_2\&i)=0}a_{k_1}b_{k_2}\\
& = \sum_{f(k_1\&i) \operatorname{xor} f(k_2\&i)=0} a_{k_1}b_{k_2}-\sum_{f(k_1\&i) \operatorname{xor} f(k_2\&i)=1} a_{k_1}b_{k_2} \\ 
& = \sum_{f((k_1\operatorname{xor}k_2)\&i)=0}a_{k_1}b_{k_2}-\sum_{f((k_1\operatorname{xor}k_2)\&i)=1}a_{k_1}b_{k_2}\\
& = FC_{i}
\end{aligned}
$$
还是老套路分治，按最高位是$0$还是$1$进行合并。考虑到最高位是$0$时，$AND$不会影响函数值，所以
$$
\forall 0 \le i < \frac{L}{2},Fa_{L,l+i}=Fa_{\frac{L}{2},l+i}+Fa_{\frac{L}{2},l+\frac{L}{2}+i}
$$
对于最高位是$1$，那么前半部分$AND$之后不会影响函数值，但是后半部分$AND$之后会使函数值奇偶性改变，于是正负交换
$$
\forall 0 \le i < \frac{L}{2},Fa_{L,l+\frac{L}{2}+i}=Fa_{\frac{L}{2},l+i}-Fa_{\frac{L}{2},l+\frac{L}{2}+i}
$$
于是逆变换解一下方程就好了
$$
\forall 0\le i<\frac{L}{2},Fa_{\frac{L}{2},l+i}=\frac{Fa_{L,l+i}+Fa_{L,l+\frac{L}{2}+i}}{2},
Fa_{\frac{L}{2},l+\frac{L}{2}+i}=\frac{Fa_{L,l+i}-Fa_{L,l+\frac{L}{2}+i}}{2}
$$
