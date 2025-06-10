# MedianLib: Median Filter Implementation Summary

This library provides three different implementations of a median filter for 9-element arrays, each with different performance characteristics and memory requirements.

## Implementation Overview

### 1. Sorting Network (`median9_network`)
A deterministic implementation using a sorting network with direct pointer comparisons.

```c++
uint16_t median9_network(const uint16_t* samples);
```


- **Approach**: Uses a carefully designed network of compare-and-swap operations
- **Key Feature**: Fixed number of operations regardless of input pattern
- **Best For**: Real-time applications with strict timing requirements

### 2. Selection Sort (`median9_selection`)
A classic algorithm that finds the median through partial sorting.

```c++
uint16_t median9_selection(const uint16_t* samples);
```


- **Approach**: Creates a copy of input and partially sorts until finding middle element
- **Key Feature**: Simple implementation with reasonable memory usage
- **Best For**: General-purpose applications without extreme constraints

### 3. Counting Sort (`median9_counting`)
A distribution-based approach leveraging the known range of values.

```c++
uint16_t median9_counting(const uint16_t* samples);
```


- **Approach**: Uses a frequency histogram to count occurrences of each value
- **Key Feature**: Runtime independent of input distribution
- **Best For**: Applications with sufficient RAM but CPU constraints

## Performance Comparison

| Implementation | Flash (bytes) | RAM (bytes) | Worst-case Cycles | Time Complexity | Deterministic |
|----------------|---------------|-------------|-------------------|-----------------|--------------|
| Sorting Network| ~220         | 18          | ~300              | O(1)            | Yes          |
| Selection Sort | ~300         | 18          | ~500              | O(n²)           | No           |
| Counting Sort  | ~100         | 8192        | ~8200             | O(n+k)*         | Yes          |

\* Where k is the range of values (4096 for 12-bit values)

## Key Characteristics

### Sorting Network
- Fixed execution time regardless of input
- Extremely memory efficient
- No branches (predictable on any architecture)
- Moderate code size
- Optimal for real-time applications
- Handles all input patterns reliably

### Selection Sort
- Simple implementation
- Small memory footprint
- Variable execution time based on input
- Good trade-off between code size and performance
- Reasonable for non-time-critical applications

### Counting Sort
- Extremely small code size
- Very high memory usage (requires histogram buffer)
- Linear time complexity relative to value range
- Fixed execution time
- Best when memory constraints are relaxed

## Usage Guidelines

1. **Memory-constrained systems**: Use sorting network
2. **Extremely code-size constrained systems**: Use counting sort if RAM allows
3. **Real-time systems with strict deadlines**: Use sorting network
4. **General purpose applications**: Use selection sort for simplicity

## Build Information

MedianLib is built as a static library using CMake with C++20 standard. The tests directory contains comprehensive test cases to verify the implementations.

```cmake
cmake_minimum_required(VERSION 3.31)
project(MedianLib)

set(CMAKE_CXX_STANDARD 20)

add_library(MedianLib STATIC src/median_filter_algorithms.cpp)

add_subdirectory(tests)
```


All implementations preserve the input array and return a single uint16_t value representing the median of the 9-element input array.
