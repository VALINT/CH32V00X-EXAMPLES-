/*
 * gpio.h
 *
 *  Created on: Feb 7, 2024
 *      Author: VAL
 */

#ifndef USER_GPIO_H_
#define USER_GPIO_H_

#define M_INPUT         0x0
#define M_OUT_2M        0x2
#define M_OUT_10M       0x1
#define M_OUT_50M       0x3

#define C_ANALOG        0x0
#define C_FLOATING_IN   0x1
#define C_IN_PP_PD      0x2

#define C_GP_PP         0x0
#define C_GP_OD         0x1
#define C_AF_PP         0x2
#define C_AF_OD         0x3

#define INPUT_FLOATING          ((C_FLOATING_IN << 2) | M_INPUT)
#define INPUT_PULL_UP           ((C_IN_PP_PD << 2) | M_INPUT)
#define INPUT_PULL_DOWN         ((C_IN_PP_PD << 2) | M_INPUT)
#define ANALOG_MODE             ((C_ANALOG << 2) | M_INPUT)
#define OUTPUT_OPEN_DRAIN_2M    ((C_GP_OD << 2) | M_OUT_2M)
#define OUTPUT_PUSH_PULL_2M     ((C_GP_PP << 2) | M_OUT_2M)
#define OUTPUT_OPEN_DRAIN_10M   ((C_GP_OD << 2) | M_OUT_10M)
#define OUTPUT_PUSH_PULL_10M    ((C_GP_PP << 2) | M_OUT_10M)
#define OUTPUT_OPEN_DRAIN_50M   ((C_GP_OD << 2) | M_OUT_50M)
#define OUTPUT_PUSH_PULL_50M    ((C_GP_PP << 2) | M_OUT_50M)
#define ALTERN_PUSH_PULL_2M     ((C_AF_PP << 2) | M_OUT_2M)
#define ALTERN_OPEN_DRAIN_2M    ((C_AF_OD << 2) | M_OUT_2M)
#define ALTERN_PUSH_PULL_10M    ((C_AF_PP << 2) | M_OUT_10M)
#define ALTERN_OPEN_DRAIN_10M   ((C_AF_OD << 2) | M_OUT_10M)
#define ALTERN_PUSH_PULL_50M    ((C_AF_PP << 2) | M_OUT_50M)
#define ALTERN_OPEN_DRAIN_50M   ((C_AF_OD << 2) | M_OUT_50M)

#define CLEAR_REG_FULL(port,reg)        port->reg = 0;
#define CLEAR_REG_PART(port, reg, val)  port->reg &=~ val;
#define SET_REG_PART(port, reg, val)    port->reg |= val;
#define INIT_PIN(port, pin, func)       port->CFGLR |= (func << ( pin * 4 ))
#define CLEAR_INIT(port, pin)           port->CFGLR &=~ (0xf << ( pin * 4 ))
#define RESET_PIN(port, pin)            port->BCR = (0x1 << pin )
#define CLEAR_PIN(port, pin)            port->OUTDR &= ~(0x1 << pin)
#define SET_PIN(port, pin)              port->OUTDR |=  (0x1 << pin)
#define INVERT_PIN(port, pin)           port->OUTDR = (port->OUTDR^(0x1 << pin))
#define READ_PIN(port, pin)             port_>INDR & (1 << pin)

#define PIN_OUT(x)

#endif /* USER_GPIO_H_ */
