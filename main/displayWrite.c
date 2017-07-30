/*
 * displayWrite.c
 *
 *  Created on: 30.07.2017
 *      Author: de1m
 */

#include "xi2c.h"
#include "fonts.h"
#include "ssd1306.h"

#include "driver/gpio.h"
#include "driver/i2c.h"

#include "config.h"

#define I2C_EXAMPLE_MASTER_SCL_IO    22    /*!< gpio number for I2C master clock */
#define I2C_EXAMPLE_MASTER_SDA_IO    21    /*!< gpio number for I2C master data  */
#define I2C_EXAMPLE_MASTER_NUM I2C_NUM_1   /*!< I2C port number for master dev */
#define I2C_EXAMPLE_MASTER_TX_BUF_DISABLE   0   /*!< I2C master do not need buffer */
#define I2C_EXAMPLE_MASTER_RX_BUF_DISABLE   0   /*!< I2C master do not need buffer */
#define I2C_EXAMPLE_MASTER_FREQ_HZ    100000     /*!< I2C master clock frequency */

static void i2c_example_master_init()
{
    int i2c_master_port = I2C_EXAMPLE_MASTER_NUM;
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = I2C_EXAMPLE_MASTER_SDA_IO;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_io_num = I2C_EXAMPLE_MASTER_SCL_IO;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = I2C_EXAMPLE_MASTER_FREQ_HZ;
    i2c_param_config(i2c_master_port, &conf);
    i2c_driver_install(i2c_master_port, conf.mode,
                       I2C_EXAMPLE_MASTER_RX_BUF_DISABLE,
                       I2C_EXAMPLE_MASTER_TX_BUF_DISABLE, 0);

}

void initDisplay(){
	i2c_example_master_init();
	SSD1306_Init();
}

char convertToChar(int n){
    int i = 0;
    for (; n ; n /= 10)
        ++i;
    return i;
}

int writeIcinga2Stat(struct icinInfo ic2){

	printf("\n########### WR DIPL #############\n%d\n", ic2.hostall);

    SSD1306_GotoXY(19, 19);
    SSD1306_Puts("d/c", &Font_7x10, SSD1306_COLOR_WHITE);

    SSD1306_GotoXY(55, 19);
    SSD1306_Puts("u/w", &Font_7x10, SSD1306_COLOR_WHITE);

    SSD1306_GotoXY(95, 19);
    SSD1306_Puts("all", &Font_7x10, SSD1306_COLOR_WHITE);

    SSD1306_GotoXY(3, 32);
    SSD1306_Puts("H", &Font_7x10, SSD1306_COLOR_WHITE);

    char hostdown[convertToChar(ic2.hostdown)];
    sprintf(hostdown, "%d", ic2.hostdown);
    SSD1306_GotoXY(16, 32);
    SSD1306_Puts(hostdown, &Font_7x10, SSD1306_COLOR_WHITE);

    char hostunre[convertToChar(ic2.hostunre)];
    sprintf(hostunre, "%d", ic2.hostunre);
    SSD1306_GotoXY(51, 32);
    SSD1306_Puts(hostunre, &Font_7x10, SSD1306_COLOR_WHITE);

    char hostall[convertToChar(ic2.hostall)];
    sprintf(hostall, "%d", ic2.hostall);
    SSD1306_GotoXY(86, 32);
    SSD1306_Puts(hostall, &Font_7x10, SSD1306_COLOR_WHITE);

    SSD1306_GotoXY(3, 45);
    SSD1306_Puts("S", &Font_7x10, SSD1306_COLOR_WHITE);

    char servcrit[convertToChar(ic2.servcrit)];
    sprintf(servcrit, "%d", ic2.servcrit);
    SSD1306_GotoXY(16, 45);
    SSD1306_Puts(servcrit, &Font_7x10, SSD1306_COLOR_WHITE);

    char servwarn[convertToChar(ic2.servwarn)];
    sprintf(servwarn, "%d", ic2.servwarn);
    SSD1306_GotoXY(51, 45);
    SSD1306_Puts(servwarn, &Font_7x10, SSD1306_COLOR_WHITE);

    char servall[convertToChar(ic2.servall)];
    sprintf(servall, "%d", ic2.servall);
    SSD1306_GotoXY(86, 45);
    SSD1306_Puts(servall, &Font_7x10, SSD1306_COLOR_WHITE);

    //draw lines of table
    SSD1306_DrawLine(1, 29, 126, 29, SSD1306_COLOR_WHITE); //horiz lines
    SSD1306_DrawLine(1, 42, 126, 42, SSD1306_COLOR_WHITE); //horiz lines
    SSD1306_DrawLine(1, 55, 126, 55, SSD1306_COLOR_WHITE); //horiz lines

    SSD1306_DrawLine(12, 30, 12, 33, SSD1306_COLOR_WHITE); //vert H line top
    SSD1306_DrawLine(12, 38, 12, 47, SSD1306_COLOR_WHITE); //vert H,S line bottom/top

    SSD1306_DrawLine(12, 51, 12, 54, SSD1306_COLOR_WHITE); //S line bottom

    SSD1306_DrawLine(47, 29, 47, 55, SSD1306_COLOR_WHITE); //vert line top between d/c and u/w
    SSD1306_DrawLine(82, 29, 82, 55, SSD1306_COLOR_WHITE); //vert line top between d/c and u/w

    //draw line top
    SSD1306_DrawLine(1, 14, 126, 14, SSD1306_COLOR_WHITE);

    //draw wifi logo
    SSD1306_DrawFilledRectangle(68,10, 2,2,SSD1306_COLOR_WHITE);
    SSD1306_DrawPixel(67,12,SSD1306_COLOR_WHITE);
    SSD1306_DrawPixel(71,12,SSD1306_COLOR_WHITE);

    SSD1306_DrawFilledRectangle(67,6, 4,1,SSD1306_COLOR_WHITE);
    SSD1306_DrawFilledRectangle(66,7,1,1,SSD1306_COLOR_WHITE);
    SSD1306_DrawFilledRectangle(71,7,1,1,SSD1306_COLOR_WHITE);
    SSD1306_DrawFilledRectangle(65,8,1,1,SSD1306_COLOR_WHITE);
    SSD1306_DrawFilledRectangle(72,8,1,1,SSD1306_COLOR_WHITE);

    SSD1306_DrawFilledRectangle(66,2,6,1,SSD1306_COLOR_WHITE);
    SSD1306_DrawFilledRectangle(65,3,1,1,SSD1306_COLOR_WHITE);
    SSD1306_DrawFilledRectangle(72,3,1,1,SSD1306_COLOR_WHITE);
    SSD1306_DrawFilledRectangle(64,4,1,1,SSD1306_COLOR_WHITE);
    SSD1306_DrawFilledRectangle(63,4,1,1,SSD1306_COLOR_WHITE);
    SSD1306_DrawFilledRectangle(63,5,1,1,SSD1306_COLOR_WHITE);
    SSD1306_DrawFilledRectangle(74,5,1,1,SSD1306_COLOR_WHITE);

    SSD1306_DrawPixel(63,7,SSD1306_COLOR_WHITE);
    SSD1306_DrawPixel(75,7,SSD1306_COLOR_WHITE);

    /* Update screen, send changes to LCD */
    SSD1306_UpdateScreen();

//    free(hostdown);
//    free(hostunre);
//    free(hostall);
//    free(servcrit);
//    free(servwarn);
//    free(servall);

	return 0;
}

