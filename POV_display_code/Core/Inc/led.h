#ifndef B151BCEC_B11B_4DFD_A1FB_020300F10A77
#define B151BCEC_B11B_4DFD_A1FB_020300F10A77


#include "main.h"
#include "stdbool.h"
#include "spi.h"

#define NR_OF_COLS 135
#define NR_OF_ROWS 21
#define LED_BUFFER_SIZE 8

#define LED_HSPI hspi2

#define LED_RCLK_GPIO_Port RCLK_GPIO_Port
#define LED_RCLK_Pin RCLK_Pin

#define LED_OE_GPIO_PORT NOT_OE_GPIO_Port
#define LED_OE_Pin NOT_OE_Pin

#define LED_CLEAR_GPIO_Port NOT_CLEAR_GPIO_Port
#define LED_CLEAR_Pin NOT_CLEAR_Pin

typedef struct LED_CompiledData{
    uint8_t data[NR_OF_COLS][LED_BUFFER_SIZE];
} LED_CompiledData_t;

void LED_Send(uint8_t* col);
void LED_AllBlack();
void LED_AllWhite();
void LED_Init();

#endif /* B151BCEC_B11B_4DFD_A1FB_020300F10A77 */
