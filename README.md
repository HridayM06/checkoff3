# Benchmarking Array Search: C vs Python

**Question:** how much faster is C than Python when searching arrays of increasing size, and does the language matter more than the algorithm?

## What I explored
- Linear search (check every element) and binary search (halve a sorted array) in both C and Python
- Python's built-in `in` operator vs a hand-written loop
- Sizes from 1,000 to 10,000,000 elements, worst case (target is missing)

## Results (my machine: Python 3.12.3, gcc 13.3 -O2)
| Array size | C linear | Python loop | Python `in` | Binary: C | Binary: Python |
|---|---|---|---|---|---|
| 1,000 | 0.0006 ms | 0.020 ms | 0.006 ms | 0.039 µs | 0.289 µs |
| 100,000 | 0.036 ms | 2.24 ms | 0.66 ms | 0.062 µs | 0.368 µs |
| 1,000,000 | 0.36 ms | 23.6 ms | 6.6 ms | 0.069 µs | 0.369 µs |
| 10,000,000 | 3.8 ms | 240 ms | 77 ms | 0.076 µs | 0.414 µs |

## Discoveries
1. C's plain loop is about 60x faster than Python's, and the gap stays steady as arrays grow.
2. Python's built-in `in` is about 3x faster than a hand-written loop, but still about 20x slower than C.
3. Algorithm beats language: Python binary search beat C linear search by roughly 9,000x at 10M elements. (Python's `bisect` is implemented in C.)

## Run it
```
gcc -O2 bench.c -o bench_c && ./bench_c
python3 bench.py
```
Both print CSV. Timings vary by machine, so rerun them.

## Notes and caveats
- Best of several runs, worst-case search, same algorithm in both languages.
- C's speed probably includes compiler vectorization at -O2 (not verified).

## Files
`bench.c`, `bench.py`, slides (export from the deck as PDF or PPTX into this folder), `REFLECTION.md`.

## Resources
- Python docs: `time.perf_counter` (https://docs.python.org/3/library/time.html#time.perf_counter) and `bisect` (https://docs.python.org/3/library/bisect.html)
- GCC optimization options (-O2) and `clock_gettime` man page
