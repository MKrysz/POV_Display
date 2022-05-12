#ifndef CFCF82AE_8600_4F21_97CD_F3E48D9E0E3E
#define CFCF82AE_8600_4F21_97CD_F3E48D9E0E3E

#include "stdint.h"
#include "stdlib.h"

void ARRAY_BitwiseOR(uint8_t *x, uint8_t *y, uint8_t *result, size_t lenght);
void ARRAY_Copy(uint8_t *src, uint8_t *dest, size_t lenght);
void ARRAY_Fill(uint8_t *arr, uint8_t value, size_t lenght);
void ARRAY_Clear(uint8_t *arr, size_t lenght);

void ARRAY_Clear_16(uint16_t *arr, size_t lenght);
void ARRAY_Fill_16(uint16_t *arr, uint16_t value, size_t lenght);

#endif /* CFCF82AE_8600_4F21_97CD_F3E48D9E0E3E */
