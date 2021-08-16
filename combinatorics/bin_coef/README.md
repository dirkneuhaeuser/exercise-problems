# Binomial Coefficient

When calculating it wihout modulo, use Pascal's Formula to prevent unneccesary overflow when calculating the binomial coefficent.

**Pascal's Formula** for <img src="https://render.githubusercontent.com/render/math?math=\binom{n}{m}">:

<img src="https://render.githubusercontent.com/render/math?math=\binom{n}{m}=\begin{cases}1,  \:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\: \text{if } m=0\\1 , \:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\:\: \text{if } n=m\\\binom{n-1}{m} %2B\binom{n-1}{m-1} , \:\: \text{else}\end{cases}">

Pascal's formula In code (long long overflows for n>66):
```
vector<vector<ll>>bincoefs(66, vector<ll>(66, 1));
for(int n = 1; n<66; ++n){
    for(int m = 1; m< n; ++m){
        bincoefs[n][m] = bincoefs[n-1][m] + bincoefs[n-1][m-1];
    }
}
```

With Modulo (precalculate factorials and use modulo arithmetic) - use normal Formula <img src="https://render.githubusercontent.com/render/math?math=\binom{n}{m} = \frac{n!}{(n-m)! \cdot m!}">:
```
// out of main:
long long C(long long n, long long k, long long m, long long fact[]){
    // binomial coeffiecents with modulo m
    // n! / ((n-k)! k!) 
    // to use the modular arithmetic, we need to finde the inverse of (n-k)! and k! 
    // factorials need to be precalculated and taken modulo
    if(n < k) return 0;
    return (((fact[n] * invEea(fact[k], m)) % m) * invEea(fact[n-k], m)) % m;
}
// in main:
long long fact[100001];
// precalcualte factorials
fact[0]=1;
for(int i=1; i<100001;++i){
    fact[i] = (fact[i-1]*i)%MOD;
}
// 100000 C 5000:
long long ret = C(100000, 50000, MOD, fact);  // (100000 choose 50000)%1000000007 = 149033233
```
Note: 
* Growth for fixed m, approx: <img src="https://render.githubusercontent.com/render/math?math=O(n^m)">
* <img src="https://render.githubusercontent.com/render/math?math=\binom{n}{p}"> is even iff you can find in the binary representation of n a zero where in p is a 1 at the same position.
* To find odd Coeficients: print pascals-triangle
* Difference to Permutations: Order doesn't matter, thus there are fewer combinations than permutations.


## When to use
* combinations of n elements taken r: <img src="https://render.githubusercontent.com/render/math?math=\binom{n}{r}">
* Binomial Theorem <img src="https://render.githubusercontent.com/render/math?math=(a %2B b)^k = x_0 a^k %2B x_1 a^{k-1}b^1 %2B \ldots %2B x_{k}b^k">, where <img src="https://render.githubusercontent.com/render/math?math=x_i = \binom{k}{i}">.
* To get all subsets of size k from a set of size n (<img src="https://render.githubusercontent.com/render/math?math=\binom{n}{k}"> many), use backtracking: 
[comb1 and comb2
](https://github.com/dirkneuhaeuser/algorithms/blob/master/templates/combinatorics.cpp)
* **Combinations to put r elements in k bins**: <img src="https://render.githubusercontent.com/render/math?math=\binom{r %2B k-1}{r}">. To see that, create bijection: separate bins with k-1 stripes "|" (here k=4) and now calculate how many possibiliters there are, to put r dots: <img width="126" alt="Screenshot 2021-05-04 at 03 10 23" src="https://user-images.githubusercontent.com/44442845/126899072-42140c0b-4880-4b5b-bcdb-2934fd517969.png">

# Multinomial Coefficient


Let <img src="https://render.githubusercontent.com/render/math?math=n = b_1 %2B b_2 %2B \ldots %2B b_k"> the multinomial coefficient <img src="https://render.githubusercontent.com/render/math?math=\binom{n}{b_1, b_2, \ldots, b_k}"> is given by:

<img src="https://render.githubusercontent.com/render/math?math=\binom{n}{b_1, b_2, \ldots, b_k} = \binom{n}{b_1} \cdot \binom{n-b_1}{b_2} \cdot \binom{n-b_1-b_2}{b_3} \cdot \ldots \cdot \binom{b_k}{b_k} = \frac{n!}{b_1! \cdot b_2! \cdot \ldots \cdot b_k!} ">

## Interpretations:
1. Number of ways to put n interchangeable objets into k boxes, s.t. in box i are <img src="https://render.githubusercontent.com/render/math?math=b_i"> elements
2. Number of **unique permutations** of a word with n letters and k distinct letters, s.t. i-th letter occurs <img src="https://render.githubusercontent.com/render/math?math=b_i"> times

# Permutations
Difference to Binomial-Coefficients: Now the Order matters. Total Permutations of sequence of length n: <img src="https://render.githubusercontent.com/render/math?math=n!">. 


Implementation via backtracking. In c++, sortable container can be permutated lexicographically (already adjusted for same elements) via in-build
`prev_permutation` and `next_permutation`:
```
vector<int> test = {1,2,3};
while (next_permutation(test.begin(), test.end())){
    // do sth
}
```
## When to use
* permutations of n elements **taken only r**: <img src="https://render.githubusercontent.com/render/math?math=\frac{n!}{(n-r)!}">, meaning the permutatins of the remaining (n-r) are not included
* **Derangement count**: Count all permutations in which all elements are at different positions (from their initial position). Formula: `derange(n) = (n - 1) * [derange(n - 1) + derange(n - 2)]`

Recusive Forumula (long long overflows for n>21):
```
long long derange[22];
derange[1] = 0;
derange[2] = 1;
for(int i =3; i<22; ++i){
    derange[i] = (i-1) * (derange[i-1] + derange[i-2]);
    cout << derange[i] <<endl;
}
```
*Proof Derangement*: Let's consider a random permuation (e.g., [1, 2, 3, 4, 5])
Then, for the first element you have (n-1) options. Lets assume it goes to i. Now there are two possible options: <br />
**Case 1**: You have a perfect swap (i and 1) -> derange(i-2) <br />
**Case 2**: You don’t have a perfect swap. Then, the i-th element can choose all elements apart of 1 and i, the remaining j can choose all apart of j and i. Thus, all remaining (n-1) have (n-2) Possibilities -> derange(i-1)
