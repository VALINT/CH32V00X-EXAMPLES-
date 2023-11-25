/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : VAL
 * Date               : 2023/11/25
 * Description        : Blink program body.
 *********************************************************************************/

/*
 *@Note
 *First simple program for CH32V003
 *LED blink.
 *For LED control using PORTC PIN 1
 */

#include "debug.h"

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    SystemCoreClockUpdate();
    Delay_Init();

    GPIO_InitTypeDef  GPIO_InitStructure = {0};
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    while(1)
    {
        for(int i = 0; i < 5; i++)
        {
            GPIO_WriteBit(GPIOC, GPIO_Pin_1, 1);
            Delay_Ms(500);
            GPIO_WriteBit(GPIOC, GPIO_Pin_1, 0);
            Delay_Ms(500);
        }
        for(int i = 0; i < 5; i++)
        {
            GPIO_WriteBit(GPIOC, GPIO_Pin_1, 1);
            Delay_Ms(200);
            GPIO_WriteBit(GPIOC, GPIO_Pin_1, 0);
            Delay_Ms(200);
        }
        GPIO_WriteBit(GPIOC, GPIO_Pin_1, 1);
        Delay_Ms(2000);
        GPIO_WriteBit(GPIOC, GPIO_Pin_1, 0);
        Delay_Ms(2000);
    }
}
