#define GEM_IMPLEMENTATION
#include "GEM/GEM.h"

#define VALUE_COUNT 1000

i32 main(void) {
    // File parsing
    file_t file = file_open("../input.txt", IO_FILE_READ, false);

    i32 safeCounter = 0;
    for (u32 i = 0; i < VALUE_COUNT; i++) {
        char buf[GEM_MAX_STRING_LENGTH] = "";
        file_read_line(&file, buf, GEM_MAX_STRING_LENGTH, NULL);

        const char* sep = " ";
        char* token = strtok(buf, sep);

        i32 prevNum = 0;
        bool prevState = false;

        bool success = true;

        i32 counter = 0;
        while(token != NULL) {
            i32 num = atoi(token);

            if (counter != 0) {
                i32 dif = num - prevNum;

                if (math_abs(dif) >= 1 && math_abs(dif) <= 3) {
                    bool state = dif > 0; // going up

                    if (counter != 1) {
                        if (prevState != state) {
                            success = false;
                            break;
                        }
                    }

                    prevState = state;
                } else {
                    success = false;
                    break;
                }
            }

            prevNum = num;
            token = strtok(NULL, sep);
            counter++;
        }
        
        if (success) safeCounter++;
    }

    log_info("safe: %i", safeCounter);

    file_close(&file);
}
