# Linear + binary search benchmark. Run: python3 bench.py
import time, bisect
def linear(a, x):
    for i in range(len(a)):
        if a[i] == x: return i
    return -1
def binary(a, x):
    i = bisect.bisect_left(a, x)
    return i if i < len(a) and a[i] == x else -1
print("n,linear_loop_ms,in_operator_ms,binary_us")
for n in [1000,10000,100000,1000000,10000000]:
    a = [2*i for i in range(n)]
    reps = 200 if n <= 100000 else (5 if n <= 1000000 else 2)
    def timeit(f, reps):
        best = 1e9
        for _ in range(5 if n<=1000000 else 3):
            t = time.perf_counter()
            for _ in range(reps): f()
            best = min(best, (time.perf_counter()-t)/reps)
        return best
    lin = timeit(lambda: linear(a, -1), reps)
    inop = timeit(lambda: (-1 in a), reps)
    breps = 100000
    t = time.perf_counter()
    for k in range(breps): binary(a, 2*(k%n)+1)
    b = (time.perf_counter()-t)/breps
    print(f"{n},{lin*1e3:.4f},{inop*1e3:.4f},{b*1e6:.3f}")
