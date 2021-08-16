# Fibonacci Numbers
The sequence 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, ... is called fibonaccie sequence

Code (Growth ca <img src="https://render.githubusercontent.com/render/math?math=2^n">; long long will **overflow for n>64**) for <img src="https://render.githubusercontent.com/render/math?math=O(n)"> runtime: 
```
vector<int>fibs={0,1};
for(int i =2; i<65; i++){
    fibs.push_back(fibs[i-1] + fibs[i-2]);
}
```

## Pisano Period

If calculating the Fibonaccis modulo m, eventually there will be a **circle**. Let the circle be of length l, then assume that <img src="https://render.githubusercontent.com/render/math?math=F(k \cdot l) \equiv 0 (\mod m)"> it will be on 0:

```
int pisanoPeriod(int mod){ // O(n^2)
    int fib1 = 0, fib2=1;
    int period = 0;
    while(true){ // assume, that there is indead a pisano period
        // by pigoen hole principle there is at least on tuple fib_i fib_i+1 which whill be equal to another one after n**2
        // doesnt have to be start though
        period++;
        int newFib = (fib1+fib2) % mod;
        fib1 = fib2;
        fib2 = newFib;
        if(fib1==0 && fib2==1){
            return period;
        }
    }
}
```

## Zeckendorf Theorem:
Fibonacci can be presented as a binary string 1010 means: <img src="https://render.githubusercontent.com/render/math?math=0 \cdot 1 %2B 1 \cdot 2 %2B 0 \cdot 3 %2B 1 \cdot 5">.
It can be shown that two 1 are never together, as for example, 2 and 3 would form the 5, which then sets the bit of 5 and unset bits for 2 and 3

## Fibonacci Number in Logarithmic Time with fast Matrix Power
With divide and conquer, the power p of a quadratic matrix can be computed in <img src="https://render.githubusercontent.com/render/math?math=O(\log(n))"> runtime. Note that here the dimension d of the matrix is small,
and the matrix-multiplication of <img src="https://render.githubusercontent.com/render/math?math=O(d^3)"> is neglectable. For implementation see [matrix power](https://github.com/dirkneuhaeuser/algorithms/blob/master/templates/mod_pow_mat.cpp).

Recursive Formula:

<img src="https://latex.codecogs.com/gif.latex?\begin{bmatrix}1&space;&&space;1\\1&space;&&space;0\end{bmatrix}\begin{bmatrix}\text{fib}(n&plus;1)\\\text{fib}(n)\end{bmatrix}&space;=&space;\begin{bmatrix}\text{fib}(n&plus;2)\\\text{fib}(n&plus;1)\end{bmatrix}" title="\begin{bmatrix}1 & 1\\1 & 0\end{bmatrix}\begin{bmatrix}\text{fib}(n+1)\\\text{fib}(n)\end{bmatrix} = \begin{bmatrix}\text{fib}(n+2)\\\text{fib}(n+1)\end{bmatrix}" />

```
Matrix A(2);
A.mat[0][0] = 1;
A.mat[0][1] = 1;
A.mat[1][0] = 1;
A.mat[1][1] = 0;
    
Matrix ret = modPowMat(A, n);
cout << ret.mat[0][1] << endl;  //the n-th fib number, modulo MOD in O(log n)
```
