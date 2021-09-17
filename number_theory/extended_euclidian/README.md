## Greatest Common Divisor (GCD)
The GCD is the largest positive integer that divides each of the integers.
The GCD of two numbers is the product of **minimal primefactors** supported by both: e.g. <img src="https://render.githubusercontent.com/render/math?math=8=2^3">
and <img src="https://render.githubusercontent.com/render/math?math=12=2^2 \cdot 3^1">. Thus, supported in both: <img src="https://render.githubusercontent.com/render/math?math=2^2">


### Euclidean Algorithm

The Euclidean Algorithm retuns the GCD of two integers. It runs in <img src="https://render.githubusercontent.com/render/math?math=\log(\max(a,b))">,
as parameters are always halfing: `a’ = b` and `b’ <a/2`.
```
gcd(int a, int b){
  if ( a < b ) return gcd( b, a );
  if ( b == 0 ) return a;
  return gcd( b, a % b );
```
Or simply the c++ builtin:
```
int g = __gcd(x,y)
```

### Extended Euclidean Algorithm (EEA)


**Bézout’s identity**: Let `a` and `b` be integers with GCD `d`. Then there exist integers `x` and `y` coprime, sucht that `ax+by = d`. 
These coeffitions are not unique and a single example can be found using the EEA:
```
int eea(int a, int n, int &s, int &t){
    int xx = t = 0;
    int yy = s = 1;
    while(n){
        int q = a/n;
        int u = n; n =a%n; a=u;
        u = xx; xx = s-q*xx; s = u;
        u = yy; yy = t-q*yy; t = u;

    }
    return a; // gcd(a,n)
}
```
Note that the EEA gives a pair of `s` and `t` which is minimal in absolute values.

## Linear Diophantine Equation
Linear Diophantine Equation is an equatuion if form <img src="https://render.githubusercontent.com/render/math?math=\sum a_ix_i = c">,
where the <img src="https://render.githubusercontent.com/render/math?math=x_i"> are unknown.
The specific Linear Diophantine Equation of only 2 variables <img src="https://render.githubusercontent.com/render/math?math=a_1x_1 %2B a_2b_2  = c">
can be solved with the help of the Extended Euclidean Algorithm (EEA):

1. Use EEA to get Bézout's coefficients `s`, `t` and GCD `d` in <img src="https://render.githubusercontent.com/render/math?math=a_1s %2B a_2t = d">
2. Check if d|c. If not, there is no solution. Otherwise, there are infinite solutions. <br/>
   To see that, consider 
   <img src="https://render.githubusercontent.com/render/math?math=a_1s %2B a_2t - \frac{a_1a_2}{d} %2B \frac{a_1a_2}{d} = d"> <br/>
   This can be written as
   <img src="https://render.githubusercontent.com/render/math?math=a_1(s- \frac{a_2}{d}) %2B a_2(t %2B \frac{a_1}{d}) = d">
3. Adjust for real formula and multiply `s` and `t` with `c/d`. Now you have <img src="https://render.githubusercontent.com/render/math?math=a_1s\frac{c}{d} %2B a_2t\frac{c}{d} = c">
4. prepare shift-parameters
    1. `left` = <img src="https://render.githubusercontent.com/render/math?math=a_2/d">
    2. `right` = <img src="https://render.githubusercontent.com/render/math?math=a_1/d">
5. Sometimes is useful to create a positiveLeftLeft, postiveLeftRight (vice versa for right)
   ```
   ll positiveLeftLeft = left<0? (-1)*left: left;
   ll postiveLeftRight = left<0? (-1)*right: right;
   ```
6. Now traverse all solutions which meet the requirements: <br?>
   ```s = s - left```
   ```t = t + right```
    
### Example
Adam bought apples and oranges for 8.39 Euros, apple costs 25 cents, orange 18 cents. How many apples and oranges did Adam bought? <br/>
Linear Diophantine Equation: <img src="https://render.githubusercontent.com/render/math?math=25s %2B 18t = 839">.
