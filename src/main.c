/*
**
**                           Main.c
**
**
**********************************************************************/
/*
   Last committed:     $Revision: 00 $
   Last changed by:    $Author: $
   Last changed date:  $Date:  $
   ID:                 $Id:  $

**********************************************************************/
#include "stm32f0xx_conf.h"
#include <stdio.h>
#include "BMP180.h"




struct bmp180_t Sensor1;

int main(void)
{
    uint32_t i;
    uint8_t data1, data2;
    uint16_t data16=0;
    int32_t pressure1, temperature;
    char debugString[1000]="";

    ///PORT A
    //USART 1 and 2
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_1);//CTS2
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_1);//RTS2
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_1);//TX2
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_1);//RX2
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_1); // TIM3_CH1
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1);//TX1
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1);//RX1
    GPIO_InitTypeDef GPIO_InitStruct;
        GPIO_InitStruct.GPIO_Pin =GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_6|GPIO_Pin_9|GPIO_Pin_10;
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
        GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
        GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA, &GPIO_InitStruct);



    debugInit();
    I2CInit();
    debugSend("Mellow world\n");

    read8(0xD0, &data2);
    _printfU("Sensor ID: ", data2);

    bmp180_get_calib_param(&Sensor1);

    getTemperature(&temperature, &Sensor1);
    _printfLngS("Temperature is ", (int32_t)temperature);

    getPressure(&pressure1, &Sensor1);
    _printfLngS("Pressure is ", (int32_t)pressure1);

    while(1)
    {

    }
}




