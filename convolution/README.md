# Convolution

Let A and B be polynomials of degree n.
With Fast-Fourir-Transformation (FFT), the **multiplication of polynomials** A and B can be solved in <img src="https://render.githubusercontent.com/render/math?math=O(n \log (n))"> instead of <img src="https://render.githubusercontent.com/render/math?math=O(n^2)">.


**Naive Code** in <img src="https://render.githubusercontent.com/render/math?math=O(n^2)">:
```
for(int j=0; j<=n; ++j){
    for(int k=0; k<=n; ++k){
	res[j+k] += A[j] * B[k];
    }
}
```

**Better Idea** in <img src="https://render.githubusercontent.com/render/math?math=O(n \log (n))">:
1. Convert polynoms to point-value (degree n polynom needs n+1 distrinct points) representation  <img src="https://render.githubusercontent.com/render/math?math=O(n \log (n))">) by FFT)
2. Do polynomial multiplication in point-value representation (<img src="https://render.githubusercontent.com/render/math?math=O(n)">)
3. Convert back to coefficient representation. (<img src="https://render.githubusercontent.com/render/math?math=O(n \log (n))"> by inversed FFT)



### FFT-Intuition

Given A, a vector of coefficents, FFT will evaluate the polynomial at n + 1 (`A.size()`) different positions in place.

To evaluate the Ploynom at the position x, use D&C:
<img src="https://render.githubusercontent.com/render/math?math=A(x) = A_0(x^2) %2B x \cdot A_1(x^2)"> ,where
<img src="https://render.githubusercontent.com/render/math?math=A_0"> is the polynom of all the even indicies of A,
and <img src="https://render.githubusercontent.com/render/math?math=A_1"> all the odds. Note, you need bit-reversal order for iterating through <img src="https://render.githubusercontent.com/render/math?math=A_0"> first and then <img src="https://render.githubusercontent.com/render/math?math=A_1">.

<img src="https://render.githubusercontent.com/render/math?math=A(x) = (a_0, a_1,a_2, \ldots, a_n) = a_0 %2B a_1x^1 %2B a_2x^2 %2B \ldots %2B a_nx^n"> <br/>
<img src="https://render.githubusercontent.com/render/math?math=A_0(x) = (a_0, a_2, a_4 \ldots) = a_0 %2B a_2x^1 %2B a_4x^2 %2B \ldots"> <br/>
<img src="https://render.githubusercontent.com/render/math?math=A_1(x) = (a_1, a_3, a_5 \ldots) = a_1 %2B a_3x^1 %2B a_5x^2 %2B \ldots">

Fast way: Use the nth-root, as the the square of the n-th root of unity can complety be reduced to the the n/2-root of unity. <br/>
All n-th roots are give by: <img src="https://render.githubusercontent.com/render/math?math=e^{i2\pi k/n} = \cos(2 \pi k/n) %2B i \sin(2 \pi k/n) \:\: \forall k \in \{0, 1, \ldots, n-1\}"> <br/>

Note:
1. A is always halved, at each iterations (due to D&C)
2. Choosing x smart (take all n-th root elements), we can retrieve all n values for A from <img src="https://render.githubusercontent.com/render/math?math=A_0"> and <img src="https://render.githubusercontent.com/render/math?math=A_1"> in one go and do not need to calculate them for each value x again (collapsing property of the n-th root of unity). 


In a nutshell, we calculate y in <img src="https://render.githubusercontent.com/render/math?math=WA = y">, given W and A, 
where W is a nxn matrix, with <img src="https://render.githubusercontent.com/render/math?math=w_{k,j} = e^{i2\pi k/n \cdot j} \:\:  \forall k,j \in \{0, 1, \ldots, n-1\} "> all elements
from the n-th root and their exponentials. The collapsing-property can now be written as <img src="https://render.githubusercontent.com/render/math?math=w_{2k, n} = w_{k, n/2}">.

**Putting things togther**:<br/>
Suppose, we have already the subproblems <img src="https://render.githubusercontent.com/render/math?math=Y_0[k] = A_0(w_{k, n/2})">
and <img src="https://render.githubusercontent.com/render/math?math=Y_1[k] = A_1(w_{k, n/2}), k \in \{ 0, \ldots ,\frac{n}{2}-1 \}">,
both vectors of length n/2. We have to combine them, to calculate Y.

First half for all <img src="https://render.githubusercontent.com/render/math?math=k, k \in \{ 0, \ldots ,\frac{n}{2}-1 \}">: <br/>
<img src="https://render.githubusercontent.com/render/math?math=Y[k] = Aw_{k,n} = A_0 w_{2k, n} %2B w_{k,n} \cdot A_1 w_{2k, n} "> <br/>
<img src="https://render.githubusercontent.com/render/math?math=\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:= Y_0[k] %2B w_{k,n} \cdot Y_1[k]">

Second half for all <img src="https://render.githubusercontent.com/render/math?math=\frac{n}{2} %2B k, k \in \{ 0, \ldots ,\frac{n}{2}-1 \}">: <br/>
<img src="https://render.githubusercontent.com/render/math?math=Y[k] = Aw_{k,n} = A_0 w_{2k, n} - w_{k,n} \cdot A_1 w_{2k, n} "> <br/>
<img src="https://render.githubusercontent.com/render/math?math=\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:= Y_0[k] - w_{k,n} \cdot Y_1[k]">

### Inverse FFT

FFT calcualted n+1 different points, <img src="https://render.githubusercontent.com/render/math?math=WA = y">,
now reverse and calcualte <img src="https://render.githubusercontent.com/render/math?math=W^{-1}Y = A"> for given <img src="https://render.githubusercontent.com/render/math?math=W^{-1}">
and <img src="https://render.githubusercontent.com/render/math?math=Y">.

It can be shown: <img src="https://render.githubusercontent.com/render/math?math=w^{-1}_{k,j} = \frac{1}{n} (1/w_{k, j})">,
in polar coordinates is that just scaling <img src="https://render.githubusercontent.com/render/math?math=(\frac{1}{n})">
and conjugation <img src="https://render.githubusercontent.com/render/math?math=w^{-1}_{k,1} = w_{k,-1} = e^{-i2\pi k/n} = \cos(-2 \pi k/n) %2B i \sin(-2 \pi k/n) = \cos(2 \pi k/n) - i \sin(2 \pi k/n)">

Thus,
<img src="https://render.githubusercontent.com/render/math?math=y_j \cdot e^{-i \Theta} = \overline{\overline{y_j} \cdot e^{i \Theta}}">
```
void IFFT(vector<cd> &Y){
    for(auto &p:Y)p=conj(p);
    FFT(Y);
    for(auto &p:Y)p = conj(p); // conjugate here acutally not neccessary, as we only need real units in our problems
    for(auto &p:Y)p /= Y.size();
}
```

## When to use
Convolution are often hidden, and do not need to come in the form of polynomial-multiplication. In the following we denote * as convolution and thus the sth element is defined as <img src="https://render.githubusercontent.com/render/math?math=(f*g)_s = \sum_{j+k=s} f_j \cdot g_k">.
* **Frequency Convolution (All Possible Sums)** <br/>
Given two arrays of non-negative integers A and B. How many ways are there to get a sum <img src="https://render.githubusercontent.com/render/math?math=y = A_j %2B B_k"> for all possible y? <br/>
Example: <br/>
<img src="https://render.githubusercontent.com/render/math?math=A = \{1, 1, 1, 3, 3, 4\}"> and
<img src="https://render.githubusercontent.com/render/math?math=B = \{1, 1, 2, 3, 3\}">. <br/>
Transform them to frequency array: <br/>
<img src="https://render.githubusercontent.com/render/math?math=f_A = [0, 3, 0, 2, 1]"> and
<img src="https://render.githubusercontent.com/render/math?math=f_B = [0, 2, 1, 2]">. <br/>
Then the convolution <img src="https://render.githubusercontent.com/render/math?math=f_A * f_B = [0, 0, 6, 3, 10, 4, 5, 2] "> gives the possibilities a sum (the index is the sum) can be calculated. <br/> 
 <img src="https://render.githubusercontent.com/render/math?math=\:\:\:\:\:\:\:\:f_A = [\color{red} 0\color{black}, 3, 0, 2, 1] \:\:\: f_A = [\color{red} 0\color{black}, \color{blue} 3\color{black}, 0, 2, 1] \:\:\: f_A = [\color{red} 0\color{black}, \color{blue} 3\color{black}, \color{green} 0\color{black}, 2, 1] \:\:\: f_A = [\color{red} 0\color{black}, \color{blue} 3\color{black}, \color{green} 0\color{black}, \color{purple} 2\color{black}, 1] \:\:  \ldots">
 <img src="https://render.githubusercontent.com/render/math?math=\:\:\:\:\:\:\:\:f_B = [\color{red}0\color{black}, 2, 1, 2] \:\:\:\:\:\:\:\: f_B = [\color{blue}0\color{black}, \color{red}2\color{black}, 1, 2] \:\:\:\:\:\:\:\: f_B = [\color{green}0\color{black}, \color{blue}2\color{black}, \color{red}1\color{black}, 2] \:\:\:\:\:\:\:\: f_B = [\color{purple}0\color{black}, \color{green}2\color{black}, \color{blue}1\color{black}, \color{red}2\color{black}] \:\: \ldots">
 
```
vector<ll> multiply(vector<ll> &p1, vector<ll> &p2){ // O(n*log(n))
    int n = 1;
    while(n < p1.size() + p2.size() -1) n <<=1;
    vector<cd> A(p1.begin(), p1.end());
    vector<cd> B(p2.begin(), p2.end());
    A.resize(n);
    B.resize(n);
    FFT(A);
    FFT(B);
    vector<cd> mult(n);
    for(int i=0; i<n; ++i){
        mult[i] = A[i]*B[i];
    }
    IFFT(mult);
    vector<ll>ret;
    for(cd a: mult){
        ret.push_back(round(a.real()));  // rounding might be changed. When dealing with frequencies/integer-values this sould be ok!
    }
    ret.resize(p1.size() + p2.size() -1);
    return ret;
}
```

* **All Dot Products** <br/>
Given two arrays of integers A and B. Determine the dot product of B with all possible contiguous subsequences of A. <br/>
As here the multiplication is not athwart, we need to reverse B, then normal convolution. <br/>
Example: <br/>
Let <img src="https://render.githubusercontent.com/render/math?math=f = [5, 7, 2, 2, 3, 6]"> and
<img src="https://render.githubusercontent.com/render/math?math=g = [2, 1, 3, 4]"> and <img src="https://render.githubusercontent.com/render/math?math=\bar{g} = [4, 3, 1, 2]"> the reversed of g.<br/>
Then, <img src="https://render.githubusercontent.com/render/math?math=f*\bar{g} = [20, 43, 34, \textbf{27, 31, 38,} 23, 12, 12]">.

* **Bitstring Alignments** <br/>
Let A and B be bitstrings with <img src="https://render.githubusercontent.com/render/math?math=|A| \ge |B|"> . How many substrings A' of A of length B are there, such that, if <img src="https://render.githubusercontent.com/render/math?math=B_k = 1 \rightarrow A_k^' =1">? <br/>
Reverse B and convolution will give you the alignment score at each index. Add up all 1's in B and if you can find this number in <img src="https://render.githubusercontent.com/render/math?math=f*\bar{g}"> you have a perfect alignment. <br/>
Example: <br/>
Let <img src="https://render.githubusercontent.com/render/math?math=f = [1, 1, 0, 1, 1, 1, 1, 0]"> and
<img src="https://render.githubusercontent.com/render/math?math=g = [1, 1, 0, 1]"> and <img src="https://render.githubusercontent.com/render/math?math=\bar{g} = [1, 0, 1, 1]"> the reversed of g.<br/>
Then, <img src="https://render.githubusercontent.com/render/math?math=f*\bar{g} = [1, 1, 1, \textbf{3, 2, 2, 3, 2}, 2, 1, 0]">.

* **Bitstring Matching** <br/>
Same as Bitstring Alignments, but we need to align both 0 and 1. <br/>
Run Alignments <img src="https://render.githubusercontent.com/render/math?math=p=f*\bar{g}"> and then flip both vectors and calculate it again, lets name it q. The alignment score at each index k is given by  <img src="https://render.githubusercontent.com/render/math?math=(p%2Bq)[k]">

* **String Matching** <br/>
More general version of Bitstring Matching. Let A and B be strings, how many times does B appear in A as substring? <br/>
Compute array f: Translate each element from A to a value <img src="https://render.githubusercontent.com/render/math?math=e^{i2\pi k/n}"> with k as encoding of the character <img src="https://render.githubusercontent.com/render/math?math=(a \rightarrow 0, b\rightarrow 1, \ldots, z \rightarrow 25)"> and <img src="https://render.githubusercontent.com/render/math?math=n=25">.
Vice versa calcualte g from B, but use <img src="https://render.githubusercontent.com/render/math?math=e^{-i2\pi k/n}">. As this is again is alignment, reverse g. <br/>
Then, only when two characters are matching, the multiplcation is 1, and else less than 1.
Thus if there is a match, you will find the `B.size()` in <img src="https://render.githubusercontent.com/render/math?math=f*\bar{g}">. Note that other string processing methods like KMP or Rabin-Karp are better, performance-wise.
* **String Matching with Wildcards** <br/>
You can search with wildcards, therefore set the specific value in g to 0 and do not look for the `B.size()` in the convultion, but for `B.size() - numsWildcards`.

* **All Distances** <br/>
Let A be a bitstring, how many ways are to choose i and j, such that, <img src="https://render.githubusercontent.com/render/math?math=A_i = A_j = 1"> and  <img src="https://render.githubusercontent.com/render/math?math=j-i = k">? <br/>
The dot-product of A with itself solves this problem for all possible k, namely:  <img src="https://render.githubusercontent.com/render/math?math=\ldots, -2, -1, 0, 1, 2, \ldots ">. Note the center is then for k=0 and left and right sides are symmetric<br/>
Example: <br/>
Let <img src="https://render.githubusercontent.com/render/math?math=A = [1, 0, 1, 1, 1]">
Then, <img src="https://render.githubusercontent.com/render/math?math=A*\bar{A} = [1, 1, 2, 2, 4, 2, 2, 1, 1]">. So there are 4 possible ways to choose p and q, such that the difference is 0, and both are 1.
