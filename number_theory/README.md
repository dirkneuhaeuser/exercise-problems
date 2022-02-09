# NUMBER THEORY

Often in Number Theory, you will consider multiples of numbers. Assume we have the numbers from `1` to `n`. For each number, we will go through its multiples up to `n`.
The complexity would then be <img src="https://render.githubusercontent.com/render/math?math=O(n \log n)">, as with the well-known fact:

<img src="https://render.githubusercontent.com/render/math?math=\sum_{k=1}^n \frac{1}{k} = O(\log n)">, we can deduce:
<img src="https://render.githubusercontent.com/render/math?math=\frac{n}{1} %2B \frac{n}{2} %2B \frac{n}{3} %2B \ldots %2B \frac{n}{n} =  n(\sum_{k=1}^n \frac{1}{k}) = O(n \log n) ">
