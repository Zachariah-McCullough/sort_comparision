# Sorting Algorithms Benchmark in C++

A C++ program developed for an **Algorithms Master's course -- University of Southern Mississippi -- CSC514** to study and compare the **performance and correctness** of different sorting algorithms. The program implements **Selection Sort, Merge Sort, Heapsort, and Quicksort**, and benchmarks them on randomly generated datasets.

---

## Purpose

The main objectives of this project are:

1. **Algorithm Implementation:** Practice coding classical sorting algorithms from scratch.  
2. **Performance Analysis:** Measure runtime efficiency for different input sizes.  
3. **Correctness Verification:** Ensure all algorithms produce identical sorted outputs.  
4. **Comparative Study:** Understand trade-offs such as time complexity, stability, and memory usage.

---

## Features

- **Random Dataset Generation**
  - Generates large vectors of integers using Mersenne Twister for reproducible randomness.

- **Sorting Algorithms Implemented**
  1. **Selection Sort:** `O(n^2)`, in-place, not stable.
  2. **Merge Sort:** `O(n log n)`, stable, uses auxiliary memory.
  3. **Heapsort:** `O(n log n)`, uses a priority queue, not stable.
  4. **Quicksort:** Average `O(n log n)`, worst-case `O(n^2)`, not stable.

- **Benchmarking**
  - Measures execution time of each algorithm in milliseconds.

- **Correctness Check**
  - Compares all sorted outputs to confirm identical results.

---

## Installation

1. **Clone the repository:**

```bash
git clone https://github.com/yourusername/sort_comparision.git
cd sort_comparision

    Compile the program (requires a C++11 compatible compiler):

g++ -std=c++11 -O2 -o sort_comparision.cpp

    Run the program:

./sort_comparision

Usage

    The program will:

        Generate a random vector of integers.

        Sort it using all four algorithms.

        Print execution times.

        Verify correctness by comparing results.

    To experiment with different input sizes, modify the variable n in main():

const int n = 10000; // Change this to test different sizes

Example Output

Selection Sort: 1500 ms
Merge Sort: 22 ms
Heapsort: 18 ms
Quicksort: 12 ms
All algorithms produced identical sorted results.

Educational Notes
Algorithm	Time Complexity	Stability	In-place	Notes
Selection Sort	O(n^2)	No	Yes	Simple but inefficient for large n
Merge Sort	O(n log n)	Yes	No	Stable, uses extra memory
Heapsort	O(n log n)	No	No	Efficient, uses a min-heap
Quicksort	Avg O(n log n), Worst O(n^2)	No	No	Very fast on average, pivot selection matters

This table is useful for analyzing algorithm trade-offs in real-world scenarios.
File Structure

Sorting-Benchmark/
│
├── main.cpp          # Main program implementing sorting algorithms and benchmarking
└── README.md         # Project documentation

License

MIT License
