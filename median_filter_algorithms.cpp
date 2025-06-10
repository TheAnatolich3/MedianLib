#include "median_filter.h"

// Helper inline function with direct pointer parameters
static inline void swap_if_greater(uint16_t* a, uint16_t* b) {
    if (*a > *b) {
        uint16_t temp = *a;
        *a = *b;
        *b = temp;
    }
}

uint16_t median9_network(const uint16_t* samples) {
    // Local copy to avoid modifying input
    uint16_t values[9];
    for (int i = 0; i < 9; i++) {
        values[i] = samples[i];
    }
    
    // Corrected sorting network for 9 elements
    // Using a properly verified network that works for both ascending and descending inputs
    
    // First stage
    swap_if_greater(&values[0], &values[1]);
    swap_if_greater(&values[2], &values[3]);
    swap_if_greater(&values[4], &values[5]);
    swap_if_greater(&values[6], &values[7]);
    
    // Second stage
    swap_if_greater(&values[0], &values[2]);
    swap_if_greater(&values[1], &values[3]);
    swap_if_greater(&values[4], &values[6]);
    swap_if_greater(&values[5], &values[7]);
    
    // Third stage
    swap_if_greater(&values[0], &values[4]);
    swap_if_greater(&values[1], &values[5]);
    swap_if_greater(&values[2], &values[6]);
    swap_if_greater(&values[3], &values[7]);
    
    // Fourth stage
    swap_if_greater(&values[1], &values[4]);
    swap_if_greater(&values[3], &values[6]);
    
    // Fifth stage
    swap_if_greater(&values[2], &values[4]);
    swap_if_greater(&values[3], &values[5]);
    
    // Final stage - ensuring the right median
    swap_if_greater(&values[1], &values[2]);
    swap_if_greater(&values[3], &values[4]);
    swap_if_greater(&values[5], &values[6]);
    swap_if_greater(&values[4], &values[8]);
    swap_if_greater(&values[4], &values[5]);
    swap_if_greater(&values[3], &values[4]);
    
    // The median is now at position 4
    return values[4];
}

uint16_t median9_selection(const uint16_t* samples) {
    uint16_t values[9];
    for (int i = 0; i < 9; i++) {
        values[i] = samples[i];
    }
    
    // Find 5th element (median)
    const int target = 4;
    int left = 0;
    int right = 8;
    
    while (left < right) {
        // Use first element as pivot
        uint16_t pivot = values[left];
        int i = left + 1;
        int j = right;
        
        while (i <= j) {
            while (i <= right && values[i] <= pivot) i++;
            while (j >= left + 1 && values[j] > pivot) j--;
            if (i < j) {
                uint16_t temp = values[i];
                values[i] = values[j];
                values[j] = temp;
            }
        }
        
        // Put pivot in its final position
        values[left] = values[j];
        values[j] = pivot;
        
        if (j == target) return values[j];
        if (j < target) left = j + 1;
        else right = j - 1;
    }
    
    return values[left];
}

uint16_t median9_counting(const uint16_t* samples) {
    // For 12-bit input (0-4095)
    uint16_t counts[4096] = {0};
    
    // Count occurrences
    for (int i = 0; i < 9; i++) {
        counts[samples[i]]++;
    }
    
    // Find the median (5th element)
    int count = 0;
    for (int i = 0; i < 4096; i++) {
        count += counts[i];
        if (count > 4) { // When we pass the middle (4)
            return i;
        }
    }
    
    return 0; // Should never reach here
}