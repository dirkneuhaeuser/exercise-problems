# Catalan Numbers

The sequence 1, 1, 2, 5, 14, 42, 132, 429, 1430, ... is called Catalan Numbers.

Recursive Formula:
without mod (wachstum <img src="https://render.githubusercontent.com/render/math?math=4^n">, thus long long **overflows at n>32**)
```
long long cat[33];
cat[0] = 1;
for(int i=1; i<33; ++i){
    cat[i] = (4*i+1) * cat[i-1] / (i+2);
    cout << cat[i] << endl;
}
```

with mod:
```
int max_n = 100001;
ll cat[max_n];
cat[0] = 1;
for(int i=1; i<=max_n; ++i){
    cat[i] = ((4*i+2)%MOD * cat[i-1]%MOD *invEea(i+2, MOD)) % MOD;
    cout << cat[i] << endl;
}

```

## When to use
* Number of **distinct binary** trees with n vertices
* Number of ways n pairs of **parentheses** could match: n=2 pairs: ()() (()) 
* Number of ways an expression with **binary operations** can be **bracketet**
* Number of ways a **polygon** with n+2 sides can be **triangled**
* Number of ways you can pass from (0, 0) to (n, n) in a **grid without passing/touching the diagonal** (being only in the lower half)
* More complex examples: [Totorial by Dardy](https://codeforces.com/blog/entry/87585)


# Suber-Catalan 
The sequence 1, 1, 3, 11, 45, 197, 903, 4279, 20793, 103049, ... is called Super-Catalan Numbers.

Recursive Formula:
Note, long long **overflows at n>27**
```
long long super[28];
super[0] = 0;
super[1] = 1;
for(int i=2; i<28; ++i){
    super[i] = ((6*i - 9) * super[i-1] - (i-3) * super[i-2]) / i;
    cout << super[i] << endl;
}
```
## When to use
* Number of ways you can pass from (0, 0) to (n, n) in a **grid without passing the diagonal** (toching the diagonal is ok) (being only in the lower half)
* number of **trees** with n leaves & non-leaves **>=2 childern**
* Number of **non binary bracketing**: x(xxx)x here (xxx) has 3 and not 2 elements 


Note that there are bijective mappings between the specific usecases, e.g., between the number of non-binary backeting and the number of trees with >= 2 children.


