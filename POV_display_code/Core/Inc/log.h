#ifndef B97F7376_6C03_40A4_B262_2AC1DB32D978
#define B97F7376_6C03_40A4_B262_2AC1DB32D978

#include <stdint.h>
#include "main.h"

typedef struct _log_data {
    uint32_t idx;
    float integralSum;
    uint32_t period;
} log_data_t;

void log(log_data_t *data);
void log_test();

#endif /* B97F7376_6C03_40A4_B262_2AC1DB32D978 */
