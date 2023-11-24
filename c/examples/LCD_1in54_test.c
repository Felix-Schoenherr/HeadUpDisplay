#include "DEV_Config.h"
#include "LCD_1in54.h"
#include "GUI_Paint.h"
#include "GUI_BMP.h"
#include "test.h"
#include <stdio.h>  //printf()
#include <stdlib.h> //exit()
#include <signal.h> //signal()

void LCD_1IN54_test(void)
{
    // Exception handling:ctrl + c
    signal(SIGINT, Handler_1IN54_LCD);

    /* Module Init */
    if (DEV_ModuleInit() != 0)
    {
        DEV_ModuleExit();
        exit(0);
    }

    /* LCD Init */
    printf("1.54inch LCD demo...\r\n");
    LCD_1IN54_Init(HORIZONTAL);
    LCD_1IN54_Clear(WHITE);
    // LCD_SetBacklight(1023);
    UDOUBLE Imagesize = LCD_1IN54_HEIGHT * LCD_1IN54_WIDTH * 2;
    UWORD *BlackImage;
    if ((BlackImage = (UWORD *)malloc(Imagesize)) == NULL)
    {
        printf("Failed to apply for black memory...\r\n");
        exit(0);
    }
    // /*1.Create a new image cache named IMAGE_RGB and fill it with white*/
    Paint_NewImage(BlackImage, LCD_1IN54_WIDTH, LCD_1IN54_HEIGHT, 0, WHITE, 16);
    Paint_Clear(WHITE);
    Paint_SetRotate(ROTATE_90);

    // /* show bmp */
    printf("show bmp\r\n");

    GUI_ReadBmp("./pic/test1.bmp");
    LCD_1IN54_Display(BlackImage);
    DEV_Delay_ms(100000);

    GUI_ReadBmp("./pic/test2.bmp");
    LCD_1IN54_Display(BlackImage);
    DEV_Delay_ms(100000);

    /* Module Exit */
    free(BlackImage);
    BlackImage = NULL;
    DEV_ModuleExit();
}
