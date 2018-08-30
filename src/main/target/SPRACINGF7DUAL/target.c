/*
 * This file is part of Cleanflight and Betaflight.
 *
 * Cleanflight and Betaflight are free software. You can redistribute
 * this software and/or modify this software under the terms of the
 * GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * Cleanflight and Betaflight are distributed in the hope that they
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software.
 *
 * If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdint.h>

#include "platform.h"
#include "drivers/io.h"

#include "drivers/timer.h"

// tim, ioTag, channel, output, ioMode, alternateFunction, usageFlags

const timerHardware_t timerHardware[USABLE_TIMER_CHANNEL_COUNT] = {

    {TIM9,  IO_TAG(PA3), TIM_CHANNEL_2, 0, IOCFG_AF_PP, GPIO_AF3_TIM9, TIM_USE_PPM | TIM_USE_PWM}, // PPM / PWM1 / UART2 RX
    {TIM9,  IO_TAG(PA2), TIM_CHANNEL_1, 0, IOCFG_AF_PP, GPIO_AF3_TIM9, TIM_USE_PWM}, // PPM / PWM2 / UART2 TX

#if (SPRACINGF7DUAL_REV <= 1)
    {TIM8,  IO_TAG(PC7), TIM_CHANNEL_2, 0, IOCFG_AF_PP, GPIO_AF3_TIM8, TIM_USE_MC_MOTOR}, // ESC 1
#else
    {TIM8,  IO_TAG(PC8), TIM_CHANNEL_3, 0, IOCFG_AF_PP, GPIO_AF3_TIM8, TIM_USE_MC_MOTOR}, // ESC 1
#endif
    {TIM8,  IO_TAG(PC6), TIM_CHANNEL_1, 0, IOCFG_AF_PP, GPIO_AF3_TIM8, TIM_USE_MC_MOTOR}, // ESC 2
    {TIM8,  IO_TAG(PC9), TIM_CHANNEL_4, 0, IOCFG_AF_PP, GPIO_AF3_TIM8, TIM_USE_MC_MOTOR}, // ESC 3
#if (SPRACINGF7DUAL_REV <= 1)
    {TIM8,  IO_TAG(PC8), TIM_CHANNEL_3, 0, IOCFG_AF_PP, GPIO_AF3_TIM8, TIM_USE_MC_MOTOR}, // ESC 4
#else
    {TIM8,  IO_TAG(PC7), TIM_CHANNEL_2, 0, IOCFG_AF_PP, GPIO_AF3_TIM8, TIM_USE_MC_MOTOR}, // ESC 4
#endif

    {TIM4,  IO_TAG(PB6), TIM_CHANNEL_1, 0, IOCFG_AF_PP, GPIO_AF2_TIM4, TIM_USE_MC_MOTOR}, // ESC 5 / Conflicts with USART5_RX / SPI3_RX - SPI3_RX can be mapped to DMA1_ST3_CH0
    {TIM4,  IO_TAG(PB7), TIM_CHANNEL_2, 0, IOCFG_AF_PP, GPIO_AF2_TIM4, TIM_USE_MC_MOTOR}, // ESC 6 / Conflicts with USART3_RX
    {TIM3,  IO_TAG(PB1), TIM_CHANNEL_4, 0, IOCFG_AF_PP, GPIO_AF2_TIM3, TIM_USE_MC_MOTOR}, // ESC 7
    {TIM3,  IO_TAG(PB0), TIM_CHANNEL_3, 0, IOCFG_AF_PP, GPIO_AF2_TIM3, TIM_USE_MC_MOTOR}, // ESC 8

    {TIM2,  IO_TAG(PA1), TIM_CHANNEL_2, 0, IOCFG_AF_PP, GPIO_AF1_TIM2, TIM_USE_LED}, // LED Strip
    // Additional 2 PWM channels available on UART3 RX/TX pins
    // However, when using led strip the timer cannot be used, but no code appears to prevent that right now
    {TIM2,  IO_TAG(PB10), TIM_CHANNEL_3, 0, IOCFG_AF_PP, GPIO_AF1_TIM2, TIM_USE_MC_MOTOR}, // Shared with UART3 TX PIN and SPI3 TX (OSD)
    {TIM2,  IO_TAG(PB11), TIM_CHANNEL_4, 0, IOCFG_AF_PP, GPIO_AF1_TIM2, TIM_USE_MC_MOTOR}, // Shared with UART3 RX PIN

    //{TIM1,  IO_TAG(PA8), TIM_Channel_1, TIM_USE_TRANSPONDER}, // Transponder
    // Additional 2 PWM channels available on UART1 RX/TX pins
    // However, when using transponder the timer cannot be used, but no code appears to prevent that right now
    {TIM1,  IO_TAG(PA9), TIM_CHANNEL_2, 0, IOCFG_AF_PP, GPIO_AF1_TIM1, TIM_USE_FW_SERVO | TIM_USE_PWM}, // PWM 3
    {TIM1,  IO_TAG(PA10), TIM_CHANNEL_3, 0, IOCFG_AF_PP, GPIO_AF1_TIM1, TIM_USE_FW_SERVO | TIM_USE_PWM}, // PWM 4
};

#if (SPRACINGF7DUAL_REV <= 1)

#include "drivers/serial.h"
#include "drivers/serial_uart.h"

void usartTargetConfigure(uartPort_t *uartPort)
{
    if (uartPort->USARTx == USART3) {
        uartPort->Handle.AdvancedInit.AdvFeatureInit |= UART_ADVFEATURE_SWAP_INIT;
        uartPort->Handle.AdvancedInit.Swap = UART_ADVFEATURE_SWAP_ENABLE;
    }
}
#endif
