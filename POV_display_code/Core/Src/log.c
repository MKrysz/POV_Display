#include "log.h"

#define LOG_START_DDR 0x08080000
#define LOG_CAPACITY 2048

void log(log_data_t *data)
{
    static size_t offset = 0;
    if(offset + sizeof(*data) > LOG_CAPACITY)
        return;


	HAL_FLASHEx_DATAEEPROM_Unlock();
    HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_WORD, LOG_START_DDR+offset, data->idx);
    offset += 4;
    HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_WORD, LOG_START_DDR+offset, data->integralSum);
    offset += 4;
    HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_WORD, LOG_START_DDR+offset, data->period);
    offset += 4;
	HAL_FLASHEx_DATAEEPROM_Lock();
}

void log_test()
{
    log_data_t data;
    data.idx = 1;
    data.integralSum = 2;
    data.period = 3;
    log(&data);
    data.idx = 6;
    data.integralSum = 5;
    data.period = 4;
    log(&data);
    data.idx = 7;
    data.integralSum = 8;
    data.period = 9;
    log(&data);
}