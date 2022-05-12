
#include "led.h"

void LED_Send(uint8_t* col)
{
    HAL_SPI_Transmit(&LED_HSPI, col, 8, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(LED_RCLK_GPIO_Port, LED_RCLK_Pin, 1);
    HAL_GPIO_WritePin(LED_RCLK_GPIO_Port, LED_RCLK_Pin, 0);
}

void LED_AllBlack()
{
    HAL_GPIO_WritePin(LED_CLEAR_GPIO_Port, LED_CLEAR_Pin, 0);
    HAL_GPIO_WritePin(LED_CLEAR_GPIO_Port, LED_CLEAR_Pin, 1);
    HAL_GPIO_WritePin(RCLK_GPIO_Port, RCLK_Pin, 1);
    HAL_GPIO_WritePin(RCLK_GPIO_Port, RCLK_Pin, 0);

}

void LED_AllWhite()
{
    uint8_t buffer[LED_BUFFER_SIZE];
    for (size_t i = 0; i < LED_BUFFER_SIZE; i++)
    {
        buffer[i] = 0xff;
    }

    LED_Send(buffer);
}

void LED_Init()
{
    HAL_GPIO_WritePin(LED_CLEAR_GPIO_Port, LED_CLEAR_Pin, 1);
    LED_AllBlack();
}
