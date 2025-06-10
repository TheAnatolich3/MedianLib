
#ifndef MEDIAN_FILTER_H
#define MEDIAN_FILTER_H

#include <cstdint>

// Sorting network implementation
uint16_t median9_network(const uint16_t* samples);

// Selection algorithm implementation
uint16_t median9_selection(const uint16_t* samples);

// Counting sort implementation (12-bit input)
uint16_t median9_counting(const uint16_t* samples);

#endif