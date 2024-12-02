#define GEM_IMPLEMENTATION
#include "GEM/GEM.h"

#define VALUE_COUNT 1000

i32 comparison(const void* a, const void* b) {
    return (*(i32*)a - *(i32*)b);
}

i32 main(void) {
    // Storage
    i32* left  = memory_alloc(VALUE_COUNT * sizeof(i32));
    i32* right = memory_alloc(VALUE_COUNT * sizeof(i32));

    // [Working with assumptions]
    // min value: 10000 (smallest 5 digit) | max value: 99999 (largest 5 digit)
    // total values: 99,999 - 10,000 = 89,999 | 89,999 * 4 bytes (i32) = 359,996 bytes or 0.36 MB (not a lot of memory :P)
    #define FREQUENCY_COUNT  89999
    #define FREQUENCY_OFFSET 10000
    i32* frequencies = memory_alloc(FREQUENCY_COUNT * sizeof(i32));

    // Initial file parsing
    file_t file = file_open("../input.txt", IO_FILE_READ, false);

    for (u32 i = 0; i < VALUE_COUNT; i++) {
        char buf[GEM_MAX_STRING_LENGTH] = "";
        file_read_line(&file, buf, GEM_MAX_STRING_LENGTH, NULL);
        sscanf(buf, "%i %i", &left[i], &right[i]);

        frequencies[right[i] - FREQUENCY_OFFSET]++;
    }

    file_close(&file);
    
    qsort(left , VALUE_COUNT, sizeof(i32), comparison);
    qsort(right, VALUE_COUNT, sizeof(i32), comparison);

    // Get results: "total distance" & "similarity score"
    i32 total = 0, similarity = 0;
    for (u32 i = 0; i < VALUE_COUNT; i++) {
        total += (i32)math_abs(left[i] - right[i]);
        similarity += left[i] * frequencies[left[i] - FREQUENCY_OFFSET];
    }

    log_info("total: %i", total);
    log_info("similarity: %i", similarity);

    // Cleanup
    memory_free(left);
    memory_free(right);
    memory_free(frequencies);
}
