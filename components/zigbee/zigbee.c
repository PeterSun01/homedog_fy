#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "esp_log.h"
#include "driver/uart.h"
#include "driver/gpio.h"

#include "Led.h"
#include "zigbee.h"


#define UART1_TXD  (UART_PIN_NO_CHANGE)
#define UART1_RXD  (GPIO_NUM_34)
#define UART1_RTS  (UART_PIN_NO_CHANGE)
#define UART1_CTS  (UART_PIN_NO_CHANGE)

#define BUF_SIZE    100


static const char *TAG = "ZIGBEE";

void ZIGBEE_Read_Task(void* arg);


void ZIGBEE_Init(void)
{
     //配置GPIO
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pin_bit_mask =  1ULL << UART1_RXD;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    
    
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };

    uart_param_config(UART_NUM_1, &uart_config);
    uart_set_pin(UART_NUM_1, UART1_TXD, UART1_RXD, UART1_RTS, UART1_CTS);
    uart_driver_install(UART_NUM_1, BUF_SIZE * 2, 0, 0, NULL, 0);
    xTaskCreate(&ZIGBEE_Read_Task, "ZIGBEE_Read_Task", 4096, NULL, 10, NULL);
}

unsigned char CheckSum(unsigned char *pdata, unsigned char len)
{
    unsigned char i;
    unsigned char check_sum=0;
    for(i=0; i<len; i++)
    {
        check_sum += pdata[i];
    }
    return check_sum;
}


void ZIGBEE_Read_Task(void* arg)
{
    uint8_t data_u1[BUF_SIZE];
    while(1)
    {
        int len1 = uart_read_bytes(UART_NUM_1, data_u1, BUF_SIZE, 20 / portTICK_RATE_MS);
        if(len1!=0)  //读取到传感器数据
        {
            printf("ZIGBEE=");
            for(int i=0;i<len1;i++)
            {
                printf("0x%x ",data_u1[i]);
            }
            printf("\r\n");  

            //printf("check=%x\r\n",CheckSum(data_u1+2,5));
            if(data_u1[1]==CheckSum(data_u1+2,5))//校验成功
            {
                Temperature =data_u1[4];
                Humidity    =data_u1[5];
                mq2         =data_u1[6];
                


            }
            printf("mq2=%f\r\n",mq2);
            len1=0;
            bzero(data_u1,sizeof(data_u1));                 
        }  
        vTaskDelay(1000 / portTICK_RATE_MS);
    }   
}


