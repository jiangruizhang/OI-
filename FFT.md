# FFT

### DFT

把系数表示把转化为点值表示法。

有多项式$f_n(x)=\sum_{i=0}^{n-1}a_{i}x^{i}$，其中$n$是一个$2$的幂，现在要快速求出$\forall i,0 \le i <n$的$f(\omega_{n}^{i})$。

首先把$f_n(x)$的系数按照奇偶性分成两组，分别为$h_{\frac{n}{2}}(x)=\sum_{i=0}^{\frac{n}{2}-1}a_{2i}x^i$和$g_{\frac{n}{2}}(x)=\sum_{i=0}^{\frac{n}{2}-1}a_{2i+1}x^i$

那么把$f_n(\omega_{n}^{i})$拆一下，就有如下：
$$
\begin{aligned}
f_n(\omega_{n}^{i}) & = \sum_{j=0}^{\frac{n}{2}-1}a_{2j}(\omega_{n}^{i})^{2j}+\sum_{j=0}^{\frac{n}{2}-1}a_{2j+1}(\omega_{n}^{i})^{2j+1} \\
& =  \sum_{j=0}^{\frac{n}{2}-1}a_{2j}(\omega_{n}^{2i})^{j}+\sum_{j=0}^{\frac{n}{2}-1}a_{2j+1}(\omega_{n}^{2i})^{j}\omega_{n}^{i} \\
& = \sum_{j=0}^{\frac{n}{2}-1}a_{2j}(\omega_{\frac{n}{2}}^{i})^{j}+\sum_{j=0}^{\frac{n}{2}-1}a_{2j+1}(\omega_{\frac{n}{2}}^{i})^{j}\omega_{n}^{i} \\
& = h_{\frac{n}{2}}(\omega_{\frac{n}{2}}^{i})+\omega_{n}^{i}g_{\frac{n}{2}}(\omega_{\frac{n}{2}}^{i})
\end{aligned}
$$
发现$g,h$​和$f$​是类似的，那么可以分治处理。

然后发现位置的变换是蝴蝶变换，就可以非递归计算了。

##### 蝴蝶变换

可以发现在分治过程中，位置$i$的值会唯一的变换到$i'$的位置，那么可否快速计算，然后从低到高合并呢？这样就可以降低常数。

当然是可以的，$i'$的二进制表达式和$i$的二进制表达式是前后对调的，证明就不写了。

### IDFT

把点值化为系数表示法。

假设现在要做多项式乘法$C(x)=A(x)B(x)$，那么可以把他们都拓展到$(n-1)$次的多项式，其中$n$是$2$的幂。接着对$A(x),B(x)$做$DFT$，将其转化为点值表示法，那么对于带入的$n$个$\omega_{n}^{i}$，都有$C(\omega_{n}^{i})=A(\omega_{n}^{i})B(\omega_{n}^{i})$，就是把对应位置的点值乘到一块就好了，然后对其做$IDFT$即可。

假设$C(x)=\sum_{i=0}^{n-1}a_ix^i$，$y_i=C(\omega_{n}^{i})$，那么有如下的矩阵乘法：
$$
\begin{bmatrix}1 & 1 & 1 & 1 & \cdots & 1 \\ 1 & \omega_n^1 & \omega_n^2 & \omega_n^3 & \cdots & \omega_n^{n-1} \\ 1 & \omega_n^2 & \omega_n^4 & \omega_n^6 & \cdots & \omega_n^{2(n-1)} \\ 1 & \omega_n^3 & \omega_n^6 & \omega_n^9 & \cdots & \omega_n^{3(n-1)} \\ \vdots & \vdots & \vdots & \vdots & \ddots & \vdots \\ 1 & \omega_n^{n-1} & \omega_n^{2(n-1)} & \omega_n^{3(n-1)} & \cdots & \omega_n^{(n-1)^2} \end{bmatrix}
 \begin{bmatrix} a_0 \\ a_1 \\ a_2 \\ a_3 \\ \vdots \\ a_{n-1} \end{bmatrix}
 =
 
 \begin{bmatrix}y_0 \\ y_1 \\ y_2 \\ y_3 \\ \vdots \\ y_{n-1} \end{bmatrix}
$$
只要两边都乘上这个方阵的逆矩阵就好了，然后我们发现它的逆矩阵就是对应每一项取倒数并再除以$n$，如下：
$$
\frac{1}{n}
\begin{bmatrix}
1 & 1 & 1 & 1 & \cdots & 1 \\
1 & \omega_n^{-1} & \omega_n^{-2} & \omega_n^{-3} & \cdots & \omega_n^{-(n-1)} \\
1 & \omega_n^{-2} & \omega_n^{-4} & \omega_n^{-6} & \cdots & \omega_n^{-2(n-1)} \\
1 & \omega_n^{-3} & \omega_n^{-6} & \omega_n^{-9} & \cdots & \omega_n^{-3(n-1)} \\
\vdots & \vdots & \vdots & \vdots & \ddots & \vdots \\
1 & \omega_n^{-(n-1)} & \omega_n^{-2(n-1)} & \omega_n^{-3(n-1)} & \cdots & \omega_n^{-(n-1)^2}
\end{bmatrix}
$$
那么现在来证明：

对于乘完之后的方阵，第$i$行第$i$列的值可任意这样计算：$\sum_{k=0}^{n-1} \omega_{n}^{i}\omega_{n}^{-i}=\sum_{k=0}^{n-1}\omega_{n}^{0}=n$

对于第$i$行$j$列，其中$i \not = j$，可以这样计算：$\sum_{k=0}^{n-1}(\omega_{n}^{i-j})^{k}=\frac{(\omega_{n}^{i-j})^n-(\omega_{n}^{i-j})^0}{\omega_{n}^{i-j}-1}=0$

再乘上矩阵前面的$\frac{1}{n}$，那么逆矩阵就得证了，于是又是一个$DFT$。这次的系数是计算出来的点值，带入的是$\omega_{n}^{-i}$，最后把$\frac{1}{n}$乘进去就好了。

