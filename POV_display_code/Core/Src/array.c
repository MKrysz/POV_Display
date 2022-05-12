
#include "array.h"

void ARRAY_BitwiseOR(uint8_t *x, uint8_t *y, uint8_t *result, size_t lenght)
{
    for (size_t i = 0; i < lenght; i++)
    {
        result[i] = x[i] | y[i];
    }
}

void ARRAY_Copy(uint8_t *src, uint8_t *dest, size_t lenght)
{
    for (size_t i = 0; i < lenght; i++)
    {
        dest[i] = src[i];
    }
}

void ARRAY_Fill(uint8_t *arr, uint8_t value, size_t lenght)
{
    for (size_t i = 0; i < lenght; i++)
    {
        arr[i] = value;
    }
}

void ARRAY_Clear(uint8_t *arr, size_t lenght)
{
    ARRAY_Fill(arr, 0, lenght);
}

void ARRAY_Clear_16(uint16_t *arr, size_t lenght)
{
    ARRAY_Fill_16(arr, 0, lenght);
}

void ARRAY_Fill_16(uint16_t *arr, uint16_t value, size_t lenght)
{
    for (size_t i = 0; i < lenght; i++)
    {
        arr[i] = value;
    }
    
}