#include <gtest/gtest.h>
#include "../src/median_filter.h"
#include <algorithm>
#include <vector>
#include <random>

class MedianFilterTest : public ::testing::Test {
protected:
    // Helper function to calculate reference median
    static uint16_t calculateMedian(const uint16_t* values, size_t size) {
        std::vector<uint16_t> sorted(values, values + size);
        std::sort(sorted.begin(), sorted.end());
        return sorted[size / 2];
    }
    
    // Test data arrays
    uint16_t sorted_ascending[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    uint16_t sorted_descending[9] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    uint16_t all_same[9] = {5, 5, 5, 5, 5, 5, 5, 5, 5};
    uint16_t typical_case[9] = {4, 8, 2, 9, 5, 1, 7, 3, 6};
    uint16_t edge_values[9] = {0, 0, 0, 4095, 4095, 4095, 2048, 2048, 2048};
};

// Test all implementations with sorted ascending input
TEST_F(MedianFilterTest, SortedAscending) {
    uint16_t expected = calculateMedian(sorted_ascending, 9);
    EXPECT_EQ(median9_network(sorted_ascending), expected);
    EXPECT_EQ(median9_selection(sorted_ascending), expected);
    EXPECT_EQ(median9_counting(sorted_ascending), expected);
}

// Test all implementations with sorted descending input
TEST_F(MedianFilterTest, SortedDescending) {
    uint16_t expected = calculateMedian(sorted_descending, 9);
    EXPECT_EQ(median9_network(sorted_descending), expected);
    EXPECT_EQ(median9_selection(sorted_descending), expected);
    EXPECT_EQ(median9_counting(sorted_descending), expected);
}

// Test all implementations with same value input
TEST_F(MedianFilterTest, AllSameValue) {
    uint16_t expected = calculateMedian(all_same, 9);
    EXPECT_EQ(median9_network(all_same), expected);
    EXPECT_EQ(median9_selection(all_same), expected);
    EXPECT_EQ(median9_counting(all_same), expected);
}

// Test all implementations with typical unsorted input
TEST_F(MedianFilterTest, TypicalCase) {
    uint16_t expected = calculateMedian(typical_case, 9);
    EXPECT_EQ(median9_network(typical_case), expected);
    EXPECT_EQ(median9_selection(typical_case), expected);
    EXPECT_EQ(median9_counting(typical_case), expected);
}

// Test all implementations with edge values (0, 4095 for 12-bit)
TEST_F(MedianFilterTest, EdgeValues) {
    uint16_t expected = calculateMedian(edge_values, 9);
    EXPECT_EQ(median9_network(edge_values), expected);
    EXPECT_EQ(median9_selection(edge_values), expected);
    EXPECT_EQ(median9_counting(edge_values), expected);
}

// Random input test
TEST_F(MedianFilterTest, RandomValues) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint16_t> dis(0, 4095); // 12-bit range
    
    // Run multiple random tests
    for (int test = 0; test < 100; ++test) {
        uint16_t random_input[9];
        for (int i = 0; i < 9; i++) {
            random_input[i] = dis(gen);
        }
        
        uint16_t expected = calculateMedian(random_input, 9);
        EXPECT_EQ(median9_network(random_input), expected);
        EXPECT_EQ(median9_selection(random_input), expected);
        EXPECT_EQ(median9_counting(random_input), expected);
    }
}

// Test that original input is not modified
TEST_F(MedianFilterTest, InputPreservation) {
    uint16_t original[9];
    std::copy(typical_case, typical_case + 9, original);
    
    median9_network(typical_case);
    EXPECT_TRUE(std::equal(typical_case, typical_case + 9, original));
    
    median9_selection(typical_case);
    EXPECT_TRUE(std::equal(typical_case, typical_case + 9, original));
    
    median9_counting(typical_case);
    EXPECT_TRUE(std::equal(typical_case, typical_case + 9, original));
}

// Specific edge cases
TEST_F(MedianFilterTest, SpecificPatterns) {
    uint16_t v_pattern[9] = {9, 7, 5, 3, 1, 2, 4, 6, 8};
    uint16_t plateau[9] = {1, 2, 5, 5, 5, 5, 5, 8, 9};
    uint16_t valley[9] = {9, 8, 7, 6, 1, 2, 3, 4, 5};
    
    EXPECT_EQ(median9_network(v_pattern), calculateMedian(v_pattern, 9));
    EXPECT_EQ(median9_selection(v_pattern), calculateMedian(v_pattern, 9));
    EXPECT_EQ(median9_counting(v_pattern), calculateMedian(v_pattern, 9));
    
    EXPECT_EQ(median9_network(plateau), calculateMedian(plateau, 9));
    EXPECT_EQ(median9_selection(plateau), calculateMedian(plateau, 9));
    EXPECT_EQ(median9_counting(plateau), calculateMedian(plateau, 9));
    
    EXPECT_EQ(median9_network(valley), calculateMedian(valley, 9));
    EXPECT_EQ(median9_selection(valley), calculateMedian(valley, 9));
    EXPECT_EQ(median9_counting(valley), calculateMedian(valley, 9));
}

// Test boundary values for 12-bit input
TEST_F(MedianFilterTest, BoundaryValues) {
    uint16_t boundary_test[9] = {0, 4095, 2048, 4094, 1, 4093, 2, 4092, 3};
    uint16_t expected = calculateMedian(boundary_test, 9);
    
    EXPECT_EQ(median9_network(boundary_test), expected);
    EXPECT_EQ(median9_selection(boundary_test), expected);
    EXPECT_EQ(median9_counting(boundary_test), expected);
}