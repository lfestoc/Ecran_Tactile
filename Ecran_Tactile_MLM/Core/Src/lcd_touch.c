/*
 * lcd_touch.c
 *
 *  Created on: Oct 29, 2016
 *      Author: Danylo Ulianych
 *
 *
 * An example of an interrupt handler that
 * should be put in stm32f4xx_it.c:
 *
 *	void EXTI4_IRQHandler(void) {
 *		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) == GPIO_PIN_RESET) {
 *			LCD_Touch_OnDown();
 *		} else {
 *			LCD_Touch_OnUp();
 *		}
 *		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
 *	}
 *
 */

#include <stdlib.h>
#include "lcd_touch.h"
#include "MY_ILI9341.h"

#define ADC_NO_TOUCH_X_OUTSIDE (4095 - 100)
#define TOUCH_ADC_X_MAX 3600
#define TOUCH_ADC_X_MIN 500
#define TOUCH_ADC_Y_MIN 300
#define TOUCH_ADC_Y_MAX 3780
#define LCD_TOUCH_DRAW_POINT_RADIUS  3

static LCD_TouchPoint m_last_touch_point = {
		.x=0,
		.y=0,
		.tick=0,
		.state=LCD_TOUCH_IDLE
};

static uint8_t m_is_redraw_needed = 0U;


static const float ADC_UNIT_PX_X = 1.0 / (TOUCH_ADC_X_MAX - TOUCH_ADC_X_MIN);
static const float ADC_UNIT_PX_Y = 1.0 / (TOUCH_ADC_Y_MAX - TOUCH_ADC_Y_MIN);

static ADC_HandleTypeDef* hadcX = NULL;
static ADC_HandleTypeDef* hadcY = NULL;
static uint32_t ADC_ChannelX;
static uint32_t ADC_ChannelY;
static LCD_TouchState m_touch_state = LCD_TOUCH_IDLE;
static LCD_TouchPoint* m_last_point_ref = NULL;

static float fclamp(float x, float l, float u) {
	return x < l ? l : (x > u ? u : x);
}

static float adc_norm_x(uint32_t x) {
	return (x - TOUCH_ADC_X_MIN) * ADC_UNIT_PX_X;
}

static float adc_norm_y(uint32_t y) {
	return (y - TOUCH_ADC_Y_MIN) * ADC_UNIT_PX_Y;
}

static uint32_t ADC_GetValue(ADC_HandleTypeDef* hadc, uint32_t channel) {
	ADC_ChannelConfTypeDef sConfig;

	sConfig.Channel = channel;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	HAL_ADC_ConfigChannel(hadc, &sConfig);

	// start conversion
	HAL_ADC_Start(hadc);

	// wait until finish
	HAL_ADC_PollForConversion(hadc, 100);

	uint32_t value = HAL_ADC_GetValue(hadc);

	HAL_ADC_Stop(hadc);

	return value;
}

static void GPIO_SetPinMode(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin,
		uint32_t GPIO_PinMode) {
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_PinMode;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

static void ADC_GPIOA_init(uint16_t GPIO_Pin) {
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

static uint32_t touchX() {
	GPIO_SetPinMode(GPIOA, GPIO_PIN_1, GPIO_MODE_OUTPUT_PP);
	GPIO_SetPinMode(GPIOA, GPIO_PIN_8, GPIO_MODE_OUTPUT_PP);
	GPIO_SetPinMode(GPIOB, GPIO_PIN_10, GPIO_MODE_INPUT);
	ADC_GPIOA_init(GPIO_PIN_4);

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);

	return ADC_GetValue(hadcX, ADC_ChannelX);
}

static uint32_t touchY() {
	HAL_NVIC_DisableIRQ(EXTI4_IRQn);
	GPIO_SetPinMode(GPIOB, GPIO_PIN_10, GPIO_MODE_OUTPUT_PP);
	GPIO_SetPinMode(GPIOA, GPIO_PIN_4, GPIO_MODE_OUTPUT_PP);
	GPIO_SetPinMode(GPIOA, GPIO_PIN_8, GPIO_MODE_INPUT);
	ADC_GPIOA_init(GPIO_PIN_1);

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

	uint32_t adc_y = ADC_GetValue(hadcY, ADC_ChannelY);

	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_4);
	HAL_NVIC_ClearPendingIRQ(EXTI4_IRQn);
	HAL_NVIC_EnableIRQ(EXTI4_IRQn);

	return adc_y;
}

/**
 * Saves ADC handles references to measure touch screen positions.
 */
void LCD_Touch_Init(ADC_HandleTypeDef* aHadcX, uint32_t aADC_ChannelX,
		ADC_HandleTypeDef* aHadcY, uint32_t aADC_ChannelY) {
	hadcX = aHadcX;
	hadcY = aHadcY;
	ADC_ChannelX = aADC_ChannelX;
	ADC_ChannelY = aADC_ChannelY;
}

static void GPIO_DrawMode() {
	/* GPIO Ports Clock Enable */
	__GPIOA_CLK_ENABLE()
	;
	__GPIOB_CLK_ENABLE()
	;
	HAL_NVIC_DisableIRQ(EXTI4_IRQn);

	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

	/*Configure GPIO pins: PA1 PA4 PA8 */
	GPIO_InitStruct.Pin = GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_8;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO data pin PB10 */
	GPIO_InitStruct.Pin = GPIO_PIN_10;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}


// TOUCH mode GPIO setup
static void GPIO_InterruptMode() {
	__GPIOA_CLK_ENABLE()
	;

	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

	/* X- PA1 */
	GPIO_InitStruct.Pin = GPIO_PIN_1;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);

	/* X+ PA8 */
	GPIO_InitStruct.Pin = GPIO_PIN_8;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/* Y- PB10 */
	GPIO_InitStruct.Pin = GPIO_PIN_10;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/* Y+ PA4 */
	GPIO_InitStruct.Pin = GPIO_PIN_4;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI4_IRQn);
}


/**
 * Set LCD's mode to either DRAW or TOUCH.
 *
 * Set LCD_Mode to DRAW to draw or print text on LCD,
 * then switch back to TOUCH, if you want to receive touches.
 */
HAL_StatusTypeDef LCD_SetMode(LCD_Mode mode) {
	switch (mode) {
	case LCD_MODE_TOUCH:
		GPIO_InterruptMode();
		return HAL_OK;

	case LCD_MODE_DRAW:
		GPIO_DrawMode();
		return HAL_OK;

	default:
		return HAL_ERROR;
	}
}

/*
 * Reads raw touch x- and y-positions and, if successful,
 * stores them in the LCD_TouchPoint point.
 */
LCD_TouchReadState LCD_Touch_Read(LCD_TouchPoint* p) {
	if (hadcX == NULL || hadcY == NULL) {
		return LCD_TOUCH_READ_NOT_INITIALIZED;
	}
	if (m_touch_state == LCD_TOUCH_IDLE) {
		return LCD_TOUCH_READ_NO_TOUCH;
	}
	uint32_t x = touchX();

	if (x > ADC_NO_TOUCH_X_OUTSIDE) {
		return LCD_TOUCH_READ_OUTSIDE;
	}

	uint32_t y = touchY();

	p->x = (int16_t) ((1 - fclamp(adc_norm_x(x), 0.0f, 1.0f)) * TFTWIDTH);
	p->y = (int16_t) ((1 - fclamp(adc_norm_y(y), 0.0f, 1.0f)) * TFTHEIGHT);
	p->tick = HAL_GetTick();
	p->state = m_touch_state;

	m_last_point_ref = p;
	m_touch_state = LCD_TOUCH_MOVE;

	return LCD_TOUCH_READ_SUCCESS;
}


/*
 * Indicates the start of a touch.
 * Should be called from EXTIx_IRQHandler interrupt only.
 */
void LCD_Touch_OnDown() {
	if (m_touch_state == LCD_TOUCH_IDLE) {
		m_touch_state = LCD_TOUCH_DOWN;
	}
}


/*
 * Indicates the finish of a touch.
 * Should be called from EXTIx_IRQHandler interrupt only.
 */
void LCD_Touch_OnUp() {
	m_touch_state = LCD_TOUCH_IDLE;

	if (m_last_point_ref != NULL) {
		// Mark the last read touch point as TOUCH_UP.
		// Note that it changes the point state that the user specified
		// as an argument to LCD_Touch_Read function.
		m_last_point_ref->state = LCD_TOUCH_UP;
	}
	//LCD_Touch_Draw_OnUp();
}



/*
 * Returns the current touch state.
 */
LCD_TouchState LCD_Touch_GetState() {
	return m_touch_state;
}

/*
 * Return TRUE if the point belong to the interval
 */
int LCD_Touch_Belong_Interval(LCD_TouchPoint* p,int16_t xmin,int16_t xmax,int16_t ymin,int16_t ymax)
{
	 if(p->x>xmin && p->x<xmax && p->y>ymin && p->y<ymax) return 1;
	 return 0;

}

/*
 * Draw the last touch point on the bottom
 * to use in touch mode
 */
void LCD_Touch_Draw_LastPoint_Bottom(const LCD_TouchPoint* p)
{
	char TextPos[] = "Last touch point X=000  Y=000";
	char PosX[3];
	char PosY[3];
	LCD_SetMode(LCD_MODE_DRAW);
	//ILI9341_printText("touche ", 60 ,60, COLOR_WHITE, COLOR_GREEN, 1);
	strcpy(TextPos,"Last touch point X=");
	sprintf(PosX,"%d",p->x);
	strncat(TextPos,PosX,sizeof(int));
	strncat(TextPos," Y=",3);
	sprintf(PosY,"%d",p->y);
	strncat(TextPos,PosY,sizeof(PosY));
	ILI9341_Fill_Rect(5, 215, 315, 235, COLOR_ORANGE);
	ILI9341_printText(TextPos, 70, 221, COLOR_WHITE, COLOR_ORANGE, 1);
	LCD_SetMode(LCD_MODE_TOUCH);
}


/** Function DrawTouchPoint
 * It draws one green circle where you click and stay printed
 *
 * */

void DrawTouchPoint(const LCD_TouchPoint* p) {

		ILI9341_fillCircle(320-p->y, p->x, LCD_TOUCH_DRAW_POINT_RADIUS, COLOR_GREEN);

}

/** Function MovingTouchDrawLineRefresh
 * It draws a line when you move during a touch and refresh to clear it
 * to use in draw mode
 * */
/*
void MovingTouchDrawLineRefresh(const LCD_TouchPoint* p,const LCD_TouchPoint* New_p) {
	char TextPos[] = "Last touch point X=000  Y=000";
		char PosX[3];
		char PosY[3];
		ILI9341_drawLine(320-p->y,p->x,320-New_p->y,New_p->x,COLOR_BLACK);
		strcpy(TextPos,"Last touch point X=");
			sprintf(PosX,"%d",New_p->x);
			strncat(TextPos,PosX,sizeof(int));
			strncat(TextPos," Y=",3);
			sprintf(PosY,"%d",New_p->y);
			strncat(TextPos,PosY,sizeof(PosY));
			ILI9341_Fill_Rect(0, 0, 320, 240, COLOR_WHITE);

					ILI9341_Fill_Rect(20, 140, 140, 180, COLOR_BLUE);
					ILI9341_printText("LED ON", 55,  155, COLOR_WHITE, COLOR_BLUE, 1);
					ILI9341_Fill_Rect(180, 140, 300, 180, COLOR_RED);
					ILI9341_printText("LED OFF", 215,  155, COLOR_WHITE, COLOR_RED, 1);

				ILI9341_Fill_Rect(60, 30, 260, 90, COLOR_RED);

			ILI9341_Fill_Rect(5, 215, 315, 235, COLOR_ORANGE);
			ILI9341_printText(TextPos, 70, 221, COLOR_WHITE, COLOR_ORANGE, 1);
		ILI9341_Fill_Rect(5, 215, 5, 25, COLOR_GREEN);
		ILI9341_printText("Max, Leo, Margot, time to move ", 60 ,5, COLOR_WHITE, COLOR_BLACK, 1);
		ILI9341_Fill_Rect(280, 0, 320, 40, COLOR_RED);
		ILI9341_printText("X", 292, 5, COLOR_WHITE, COLOR_RED, 4);
}

*/
void LCD_Touch_Draw_Update() {
	// special care for the LCD_TOUCH_UP event
	if (m_is_redraw_needed) {
		LCD_SetMode(LCD_MODE_DRAW);
		DrawTouchPoint(&m_last_touch_point);
		LCD_SetMode(LCD_MODE_TOUCH);
		//LCD_Touch_Draw_PrintInfo();
	}
	m_is_redraw_needed = 0U;
}

void LCD_Touch_Draw_OnUp() {
	m_last_touch_point.state = LCD_TOUCH_UP;
	m_is_redraw_needed = 1U;
}
