/*
 * lcd_touch.h
 *
 * This library implements touch screen capabilities of TFTLCD,
 * based on lcd.h driver. To change the type of ILIxxxx driver
 * of your TFTLCD, refer to lcd.h.
 *
 * 29 Oct 2016 by Danylo Ulianych
 *
 * Changelog:
 *   - v1.0   03 Aug 2020   Updated lcd lib to v1.14.
 *                          Converted the project to STMCubeIDE.
 *                          Fixed bug in touchY() by clearing EXTI4 pending interrupt.
 *   - v0.4   17 Jun 2019   Updated lcd lib to v1.8.
 *   - v0.3   07 Mar 2019   Moved drawing-related functions to lcd_touch_draw.c.
 *   - v0.2   29 Jan 2019   Updated lcd lib to v1.7.
 *                          Converted the project to Atollic TrueStudio.
 *   - v0.1   29 Oct 2016   First working prototype. SystemWorkbench IDE.
 *
 * LCD Touch pinout:
 *   Y- PB10
 *   Y+ PA4, EXTI4
 *   X- PA1
 *   X+ PA8
 *
 * In idle state, PA4 is in interrupt mode awaiting for touches.
 * You can't draw and await for touches simultaneously.
 * Set LCD_Mode to DRAW to draw or print text on LCD,
 * then switch back to TOUCH.
 *
 */

#ifndef __LCD_TOUCH_H
#define __LCD_TOUCH_H
#define TFTWIDTH			240
#define TFTHEIGHT			320

//#include "lcd.h"
#include "stm32f4xx_hal.h"

typedef enum {
	LCD_MODE_DRAW = 0,
	LCD_MODE_TOUCH
} LCD_Mode;

typedef enum {
	LCD_TOUCH_IDLE = 0,  // idle; no touch is made yet
	LCD_TOUCH_DOWN, 	//Down :Start of a touch
	LCD_TOUCH_MOVE,		//MOVE :move during a touch
	LCD_TOUCH_UP 		//Up :End of a touch
} LCD_TouchState;

typedef enum {
	LCD_TOUCH_READ_SUCCESS = 0,
	LCD_TOUCH_READ_NOT_INITIALIZED,  // user did not call LCD_Touch_Init()
	LCD_TOUCH_READ_NO_TOUCH,  // idle
	LCD_TOUCH_READ_OUTSIDE    // ADC value is outside of the acceptable range
} LCD_TouchReadState;

typedef struct LCD_TouchPoint {
	int16_t x, y;
	uint32_t tick;  // touch time in ms
	LCD_TouchState state;
} LCD_TouchPoint;



// ------------------- Initialization and setup -------------------

/**
 * Saves ADC handles references to measure touch screen positions.
 */
void LCD_Touch_Init(ADC_HandleTypeDef* hadcX, uint32_t ADC_ChannelX,
		            ADC_HandleTypeDef* hadcY, uint32_t ADC_ChannelY);


/**
 * Set LCD's mode to either DRAW or TOUCH.
 *
 * Set LCD_Mode to DRAW to draw or print text on LCD,
 * then switch back to TOUCH, if you want to receive touches.
 */
HAL_StatusTypeDef LCD_SetMode(LCD_Mode mode);



// ------------------- Reading a touch -------------------

/*
 * Reads raw touch x- and y-positions and, if successful,
 * stores them in the LCD_TouchPoint point.
 */
LCD_TouchReadState LCD_Touch_Read(LCD_TouchPoint* p);

/*
 * Indicates the start of a touch.
 * Should be called from EXTIx_IRQHandler interrupt only.
 */
void LCD_Touch_OnDown();


/*
 * Indicates the finish of a touch.
 * Should be called from EXTIx_IRQHandler interrupt only.
 */
void LCD_Touch_OnUp();


/*
 * Returns the current touch state.
 */
LCD_TouchState LCD_Touch_GetState();

/*
 * Return TRUE if the point belong to the interval
 */
int LCD_Touch_Belong_Interval(LCD_TouchPoint* p,int16_t xmin,int16_t xmax,int16_t ymin,int16_t ymax);


/*
 * Draw the last touch point on the bottom
 */
void LCD_Touch_Draw_LastPoint_Bottom(const LCD_TouchPoint* p);
// -------------------- Drawing the last touch --------------------
// These functions are supplementary and provide a simple interface
// of connecting the last touch points by drawing a line.

void LCD_Touch_Draw_ConnectLastPoint(const LCD_TouchPoint* p);
void LCD_Touch_Draw_PrintInfo();
void LCD_Touch_Draw_OnUp();
void LCD_Touch_Draw_Update();
void DrawTouchPoint(const LCD_TouchPoint* p);

#endif /* __LCD_TOUCH_H */
