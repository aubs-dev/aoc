#define GEM_IMPLEMENTATION
#include "GEM/GEM.h"

#define MAX_LINE_NUMBERS 8
#define VALUE_COUNT 1000

bool is_safe(i32* nums, u32 len) {
    if (len < 2) return false; // skip if sequence is invalid
    
    bool increasing = nums[0] < nums[1];
    for (u32 i = 0; i < len - 1; i++) {
        i32 diff = (i32)math_abs(nums[i] - nums[i + 1]);

        if (diff == 0 || diff > 3) return false;                // difference is out of range
        if (increasing  && nums[i] > nums[i + 1]) return false; // number didn't increase
        if (!increasing && nums[i] < nums[i + 1]) return false; // number didn't decrease
    }

    return true;
}

// NOTE: kind of brute force, I don't like this approach but whatever
bool is_safe_with_dampener(i32* nums, u32 len) {
    // Check if removing a single value makes the report safe
    for (u32 i = 0; i < len; i++) {
        i32 temp[MAX_LINE_NUMBERS] = {0};
        i32 tempIndex = 0;

        // Copy previous array except for one value
        for (u32 j = 0; j < len; j++) {
            if (j != i) { // skip nth value for testing
                temp[tempIndex++] = nums[j];
            }
        }
        
        // Test if removing the value made the report safe 
        // else: try again with another value removed
        if (is_safe(temp, len - 1)) return true;
    }

    return false;
}

i32 main(void) {
    file_t file = file_open("../input.txt", IO_FILE_READ, false);

    i32 safeCounter = 0;
    for (u32 i = 0; i < VALUE_COUNT; i++) {
        // Read line
        char buf[GEM_MAX_STRING_LENGTH] = "";
        file_read_line(&file, buf, GEM_MAX_STRING_LENGTH, NULL);

        // Convert line into array of integers
        // NOTE: Doing this is easier than parsing the string every time
        i32 numbers[MAX_LINE_NUMBERS] = {0};
        u32 numberCount = 0;

        const char* sep = " ";
        char* token = strtok(buf, sep);
        while (token != NULL) {
            numbers[numberCount++] = atoi(token);
            token = strtok(NULL, sep);
        }

        // Check if sequence of numbers (report) is safe or not | short-circuit if the report is valid without needing modification
        if (is_safe(numbers, numberCount) || is_safe_with_dampener(numbers, numberCount)) {
            safeCounter++;
        }
    }

    log_info("safe: %i / %i", safeCounter, VALUE_COUNT);
    file_close(&file);
}
