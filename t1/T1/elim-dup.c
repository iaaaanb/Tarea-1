#include "elim-dup.h"

typedef unsigned long uint64_t;

uint64_t elimDup(uint64_t x) {
    uint64_t result = 0;
    int result_shift = 0;  // Position where next digit should be placed
    uint64_t prev_digit = x & 0xF;  // Extract rightmost digit
    
    // Place the first digit in result
    result = prev_digit;
    result_shift = 4;
    
    // Process remaining 15 digits from right to left
    for (int i = 1; i < 16; i++) {
        // Extract current digit (4 bits at position i*4)
        uint64_t current_digit = (x >> (i << 2)) & 0xF;
        
        // If current digit is different from previous, add it to result
        if (current_digit != prev_digit) {
            result |= (current_digit << result_shift);
            result_shift += 4;
        }
        
        prev_digit = current_digit;
    }
    
    return result;
}
