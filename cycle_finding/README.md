# Floyds Cycle Detection

Usually it is better to just use a dictionary, however when you need to save memory: For example when dealing with huge strings/vectors:
Floyds Cycle Detection might be favourable.

Implementation:
Let <img src="https://render.githubusercontent.com/render/math?math=\mu"> denote the **start of cycle**, 
<img src="https://render.githubusercontent.com/render/math?math=\lambda"> the **length of cycle** and
f the step function.

We have use two pointers, the **tortoise** t and the **hare** h. h is moving two times as fast as t. When they finally meet, somewhere in the circle, then
t has made i steps, the hare has made these i steps and also circled around in the the circle a bit, thus: <img src="https://render.githubusercontent.com/render/math?math=x_i = x_{i %2B k \cdot \lambda}">.
As the hare is twice as fast, we also derive that <img src="https://render.githubusercontent.com/render/math?math=i = k \cdot \lambda">, and hence <img src="https://render.githubusercontent.com/render/math?math=x_i = x_{i %2B i}">.

### Determine, the start of circle

Setting the tortoise back to the start, then there is a **distance of i** in between both pointers. Now stepping with both one step, we keep the distance of i of both pointers; that means, when both pointers are within the cycle they have a distance of i,
 which is <img src="https://render.githubusercontent.com/render/math?math=0 \equiv i \: (\mod k \cdot \lambda)">.

### Determine, the Length of circle

Leave tortoise at the cycle start and move the hare forward until it is back to the start of the cycle.

Overall code:
```
int t = f(x0), h = f(f(x0));
while(t != h){
    t = f(t); h = f(f(h));
}
int mu = 0; h =x0; // t = k*lambda
while(t != h){ // determining cycle start index
    mu++;
    t = f(t); h = f(h);
}
h = f(t);
int lambda = 1;
while(t != h){ // determining cycle length
    lambda++;
    h = f(h);
}
```


