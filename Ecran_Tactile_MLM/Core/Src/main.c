/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "MY_ILI9341.h"
#include "lcd_touch.h"
#include "string.h"
#include "image.h"
/* USER CODE END Includes */
/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
ADC_HandleTypeDef hadc2;

SPI_HandleTypeDef hspi1;
SPI_HandleTypeDef hspi2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
static void MX_SPI2_Init(void);
static void MX_ADC1_Init(void);
static void MX_ADC2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
//TS_TOUCH_DATA_Def myTS_Handle;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_SPI2_Init();
  MX_ADC1_Init();
  MX_ADC2_Init();
  /* USER CODE BEGIN 2 */
	ILI9341_Init(&hspi1, LCD_CS_GPIO_Port, LCD_CS_Pin, LCD_DC_GPIO_Port, LCD_DC_Pin, LCD_RST_GPIO_Port, LCD_RST_Pin);
	ILI9341_setRotation(2);
	ILI9341_Fill(COLOR_NAVY);

	//TSC2046_Begin(&hspi2, TS_CS_GPIO_Port, TS_CS_Pin);
	//TSC2046_Calibrate();
	ILI9341_Fill(COLOR_WHITE);

		ILI9341_Fill_Rect(20, 140, 140, 180, COLOR_BLUE);
		ILI9341_printText("BLUE", 55,  155, COLOR_WHITE, COLOR_BLUE, 1);
		ILI9341_Fill_Rect(180, 140, 300, 180, COLOR_RED);
		ILI9341_printText("RED", 215,  155, COLOR_WHITE, COLOR_RED, 1);

	ILI9341_Fill_Rect(60, 30, 260, 90, COLOR_RED);


	ILI9341_Fill_Rect(5, 215, 315, 235, COLOR_ORANGE);
	ILI9341_printText("Last touch point X=000  Y=000", 70, 221, COLOR_WHITE, COLOR_ORANGE, 1);
	ILI9341_Fill_Rect(5, 215, 5, 25, COLOR_GREEN);
	ILI9341_printText("Max, Leo, Margot, time to start ", 60 ,5, COLOR_WHITE, COLOR_BLACK, 1);
	ILI9341_Fill_Rect(280, 0, 320, 40, COLOR_RED);
	ILI9341_printText("X", 292, 5, COLOR_WHITE, COLOR_RED, 4);
	LCD_Touch_Init(&hadc2, ADC_CHANNEL_4, &hadc1, ADC_CHANNEL_1);
		LCD_SetMode(LCD_MODE_TOUCH);
		uint8_t flag=0;
		LCD_TouchPoint p;
		p.x=0;
		p.y=0;
		p.state=LCD_TOUCH_IDLE;
		LCD_TouchPoint New_p;
				New_p.x=0;
				New_p.y=0;
				New_p.state=LCD_TOUCH_IDLE;
		char TextPos[] = "Last touch point X=000  Y=000";
		char PosX[3];
		char PosY[3];
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {
  	  /*** main test 3 draw last point and touch at start of touch BEG***/
/*

		  if(LCD_Touch_GetState()==LCD_TOUCH_DOWN ) /if there is a touch starting
		  {		LCD_Touch_Read(&p);
			  LCD_Touch_Draw_LastPoint_Bottom(&p);
			  DrawTouchPoint(&p);



			  if(LCD_Touch_Belong_Interval(&p,140,180,180,300))  // carré LED ON
			 			  {

			 					  LCD_SetMode(LCD_MODE_DRAW);

			 					  ILI9341_Fill_Rect(20, 140, 140, 180, COLOR_BLUE);
			 					  ILI9341_printText("LED ON 0", 55,  155, COLOR_WHITE, COLOR_BLUE, 1);
			 					  ILI9341_Fill_Rect(180, 140, 300, 180, COLOR_RED);
			 					  ILI9341_printText("LED OFF 0", 215,  155, COLOR_WHITE, COLOR_RED, 1);
			 					  LCD_SetMode(LCD_MODE_TOUCH);
			 			  }

			 if(LCD_Touch_Belong_Interval(&p,140,180,30,140))  // carré LED OFF
			 			{
			 					 LCD_SetMode(LCD_MODE_DRAW);
			 					 ILI9341_Fill_Rect(20, 140, 140, 180, COLOR_RED);
			 					 ILI9341_printText("LED ON 1", 55,  155, COLOR_WHITE, COLOR_RED, 1);
			 					 ILI9341_Fill_Rect(180, 140, 300, 180, COLOR_BLUE);
			 					 ILI9341_printText("LED OFF 1", 215,  155, COLOR_WHITE, COLOR_BLUE, 1);
			 					 LCD_SetMode(LCD_MODE_TOUCH);
			 			}

			 if(LCD_Touch_Belong_Interval(&p,50,80,60,180))  // rectangle
			 {
				 ILI9341_printImage(60,30, 100,100,Banane1, sizeof(Banane1));
				 HAL_Delay(100);
				 ILI9341_printImage(60,30, 100,100,Banane2, sizeof(Banane2));
				 HAL_Delay(100);
				 ILI9341_printImage(60,30, 100,100,Banane3, sizeof(Banane3));
				 HAL_Delay(100);
				 ILI9341_printImage(60,30, 100,100,Banane4, sizeof(Banane4));
				 HAL_Delay(100);
				 ILI9341_printImage(60,30, 100,100,Banane5, sizeof(Banane5));
				 HAL_Delay(100);
				 ILI9341_printImage(60,30, 100,100,Banane6, sizeof(Banane6));
				 HAL_Delay(100);
				 ILI9341_printImage(60,30, 100,100,Banane7, sizeof(Banane7));
				 HAL_Delay(100);
				 ILI9341_printImage(60,30, 100,100,Banane8, sizeof(Banane8));
				 HAL_Delay(100);
			 }
			 if(LCD_Touch_Belong_Interval(&p,0,40,0,40))  // Clear
			 			 {
				 	 	 	 ILI9341_Fill(COLOR_WHITE);
				 	 	 	 ILI9341_Fill_Rect(20, 140, 140, 180, COLOR_BLUE);
				 	 	 	 ILI9341_printText("LED ON", 55,  155, COLOR_WHITE, COLOR_BLUE, 1);
				 	 	 	 ILI9341_Fill_Rect(180, 140, 300, 180, COLOR_RED);
				 	 	 	 ILI9341_printText("LED OFF", 215,  155, COLOR_WHITE, COLOR_RED, 1);
				 	 	 	 ILI9341_Fill_Rect(60, 30, 260, 90, COLOR_RED);
				 	 	 	 ILI9341_Fill_Rect(5, 215, 315, 235, COLOR_ORANGE);
				 	 	 	 ILI9341_printText("Last touch point X=000  Y=000", 70, 221, COLOR_WHITE, COLOR_ORANGE, 1);
				 	 	 	 ILI9341_Fill_Rect(5, 215, 5, 25, COLOR_GREEN);
				 	 	 	 ILI9341_printText("Max, Leo, Margot, time to start ", 60 ,5, COLOR_WHITE, COLOR_BLACK, 1);
				 	 	 	 ILI9341_Fill_Rect(280, 0, 320, 40, COLOR_RED);
				 	 	 	 ILI9341_printText("X", 292, 5, COLOR_WHITE, COLOR_RED, 4);
			 			 }



		  }
		  else if(LCD_Touch_GetState()==LCD_TOUCH_UP){ //if the touch end
			  LCD_Touch_Read(&p);
			  LCD_SetMode(LCD_MODE_DRAW);
			  if (p.tick>1000){
				  	  char  BUF[3600];
				  	  sprintf(BUF,"Ticktime : %ld",p.tick);
				  	  ILI9341_printText(BUF, 60 ,60, COLOR_WHITE, COLOR_ORANGE, 1);

			  	  }
			  	  else{
			  		ILI9341_Fill_Rect(60, 30, 260, 90, COLOR_RED);
			  		}
			  ILI9341_printText("Max, Leo, Margot, time to start ", 60 ,5, COLOR_WHITE, COLOR_BLACK, 1);
			  LCD_SetMode(LCD_MODE_TOUCH);


		  }
		  else if(LCD_Touch_GetState()==LCD_TOUCH_MOVE){ //if there is a move during the touch
			  New_p.x=0;
			  New_p.y=0;
			  LCD_Touch_Read(&New_p);
			  if(New_p.y!=0){ //if there really is a move
				  LCD_Touch_Draw_LastPoint_Bottom(&New_p);
	  			  DrawTouchPoint(&p);

	  			  LCD_SetMode(LCD_MODE_DRAW);
	  			 // ILI9341_drawLine(320-p.y,p.x,320-New_p.y,New_p.x,COLOR_BLACK);
	  			  ILI9341_printText("Max, Leo, Margot, time to leave ", 60 ,5, COLOR_WHITE, COLOR_BLACK, 1);
	  			  ILI9341_Fill_Rect(60, 30, 260, 90, COLOR_RED);
	  			  ILI9341_Fill_Rect(0, 0, 20, 20, COLOR_WHITE);

	  			  //ILI9341_printText("MOVE ", 60 ,60, COLOR_WHITE, COLOR_ORANGE, 1);
	  			  LCD_SetMode(LCD_MODE_TOUCH);

			  }

		  }
		  else{ //IDLE

		  __WFI();
		//  }

*/
		  	  /*** main test 3 draw last point and touch at start of a touch  END ***/

	  /*** main test 4 draw when moving BEG ***/
	  if(LCD_Touch_GetState()==LCD_TOUCH_DOWN ) //if there is a touch starting
	  		  {		LCD_Touch_Read(&p);
	  			  	LCD_Touch_Draw_LastPoint_Bottom(&p);
	  			  	DrawTouchPoint(&p);






	  		  }

	  		  else if(LCD_Touch_GetState()==LCD_TOUCH_MOVE){ //if there is a move during the touch
	  			  if (flag==0)
	  			  {
	  				LCD_Touch_Read(&p);
	  				LCD_Touch_Draw_LastPoint_Bottom(&p);
	  				DrawTouchPoint(&p);
	  				flag=1;
	  			  }
	  			  	  	  	  New_p.x=0;
	  						  New_p.y=0;
	  						  LCD_Touch_Read(&New_p);
	  						  if(New_p.y>2&&New_p.x>5){ //if there really is a move
	  							 LCD_Touch_Draw_LastPoint_Bottom(&New_p);
	  				  			 DrawTouchPoint(&New_p);


	  				  			  if(LCD_Touch_Belong_Interval(&New_p,140,180,180,300))  // carré LED ON
	  				  			 			  {

	  				  			 					  LCD_SetMode(LCD_MODE_DRAW);

	  				  			 					  ILI9341_Fill_Rect(20, 140, 140, 180, COLOR_BLUE);
	  				  			 					  ILI9341_printText("BLUE", 55,  155, COLOR_WHITE, COLOR_BLUE, 1);
	  				  			 					  ILI9341_Fill_Rect(180, 140, 300, 180, COLOR_RED);
	  				  			 					  ILI9341_printText("RED", 215,  155, COLOR_WHITE, COLOR_RED, 1);
	  				  			 					  LCD_SetMode(LCD_MODE_TOUCH);
	  				  			 			  }

	  				  			 if(LCD_Touch_Belong_Interval(&New_p,140,180,30,140))  // carré LED OFF
	  				  			 			{
	  				  			 					 LCD_SetMode(LCD_MODE_DRAW);
	  				  			 					 ILI9341_Fill_Rect(20, 140, 140, 180, COLOR_RED);
	  				  			 					 ILI9341_printText("RED", 55,  155, COLOR_WHITE, COLOR_RED, 1);
	  				  			 					 ILI9341_Fill_Rect(180, 140, 300, 180, COLOR_BLUE);
	  				  			 					 ILI9341_printText("BLUE", 215,  155, COLOR_WHITE, COLOR_BLUE, 1);


	  				  			 					 LCD_SetMode(LCD_MODE_TOUCH);
	  				  			 			}

	  				  			 if(LCD_Touch_Belong_Interval(&New_p,50,80,60,180))  // rectangle
	  				  			 {
	  				  				 LCD_SetMode(LCD_MODE_DRAW);
	  				  				 ILI9341_printImage(60,30, 100,100,Banane1, sizeof(Banane1));
	  				  				 HAL_Delay(100);
	  				  				 ILI9341_printImage(60,30, 100,100,Banane2, sizeof(Banane2));
	  				  				 HAL_Delay(100);
	  				  				 ILI9341_printImage(60,30, 100,100,Banane3, sizeof(Banane3));
	  				  				 HAL_Delay(100);
	  				  				 ILI9341_printImage(60,30, 100,100,Banane4, sizeof(Banane4));
	  				  				 HAL_Delay(100);
	  				  				 ILI9341_printImage(60,30, 100,100,Banane5, sizeof(Banane5));
	  				  				 HAL_Delay(100);
	  				  				 ILI9341_printImage(60,30, 100,100,Banane6, sizeof(Banane6));
	  				  				 HAL_Delay(100);
	  				  				 ILI9341_printImage(60,30, 100,100,Banane7, sizeof(Banane7));
	  				  				 HAL_Delay(100);
	  				  				 ILI9341_printImage(60,30, 100,100,Banane8, sizeof(Banane8));
	  				  				 HAL_Delay(100);
	  				  				 ILI9341_Fill_Rect(60, 30, 260, 90, COLOR_RED);
	  				  				 LCD_SetMode(LCD_MODE_TOUCH);
	  				  			 }
	  				  			 if(LCD_Touch_Belong_Interval(&New_p,1,50,1,50))  // Clear
	  				  			 			 {
	  				  				 	 	 	 LCD_SetMode(LCD_MODE_DRAW);
	  				  				 	 	 	 ILI9341_Fill(COLOR_WHITE);
	  				  				 	 	 	 ILI9341_Fill_Rect(20, 140, 140, 180, COLOR_BLUE);
	  				  				 	 	 	 ILI9341_printText("BLUE", 55,  155, COLOR_WHITE, COLOR_BLUE, 1);
	  				  				 	 	 	 ILI9341_Fill_Rect(180, 140, 300, 180, COLOR_RED);
	  				  				 	 	 	 ILI9341_printText("RED", 215,  155, COLOR_WHITE, COLOR_RED, 1);
	  				  				 	 	 	 ILI9341_Fill_Rect(60, 30, 260, 90, COLOR_RED);
	  				  				 	 	 	 ILI9341_Fill_Rect(5, 215, 315, 235, COLOR_ORANGE);
	  				  				 	 	 	 ILI9341_printText("Last touch point X=000  Y=000", 70, 221, COLOR_WHITE, COLOR_ORANGE, 1);
	  				  				 	 	 	 ILI9341_Fill_Rect(5, 215, 5, 25, COLOR_GREEN);
	  				  				 	 	 	 ILI9341_printText("Max, Leo, Margot, time to start ", 60 ,5, COLOR_WHITE, COLOR_BLACK, 1);
	  				  				 	 	 	 ILI9341_Fill_Rect(280, 0, 320, 40, COLOR_RED);
	  				  				 	 	 	 ILI9341_printText("X", 292, 5, COLOR_WHITE, COLOR_RED, 4);
	  				  				 	 	 	 LCD_SetMode(LCD_MODE_TOUCH);
	  				  				 	 	 	 New_p.x=0;
	  				  				 	 		 New_p.y=0;
	  				  				 	 		 p.y=0;
	  				  				 	 		 p.x=0;
	  				  				 	 	flag=0;
	  				  				 	//ILI9341_SendCommand(ILI9341_DISPLAY_OFF); // test reset l'écran
	  				  			 			 }
	  				  			 if(New_p.y>p.y+20 && p.y>250 && p.x>70 && p.x<170) //swipe left to the right
	  				  			 {
	  				  				 LCD_SetMode(LCD_MODE_DRAW);
	  				  				 ILI9341_Fill(COLOR_BLUE);
	  				  				 ILI9341_Fill_Rect(20, 140, 140, 180, COLOR_BLUE);
	  				  				 ILI9341_printText("BLUE", 55,  155, COLOR_WHITE, COLOR_BLUE, 1);
	  				  				 ILI9341_Fill_Rect(180, 140, 300, 180, COLOR_RED);
	  				  				 ILI9341_printText("RED", 215,  155, COLOR_WHITE, COLOR_RED, 1);
	  				  				 ILI9341_Fill_Rect(60, 30, 260, 90, COLOR_RED);
	  				  				 ILI9341_Fill_Rect(5, 215, 315, 235, COLOR_ORANGE);
	  				  				 ILI9341_printText("Last touch point X=000  Y=000", 70, 221, COLOR_WHITE, COLOR_ORANGE, 1);
	  				  				 ILI9341_Fill_Rect(5, 215, 5, 25, COLOR_GREEN);
	  				  				 ILI9341_printText("Max, Leo, Margot, time to start ", 60 ,5, COLOR_WHITE, COLOR_BLACK, 1);
	  				  				 ILI9341_Fill_Rect(280, 0, 320, 40, COLOR_RED);
	  				  				 ILI9341_printText("X", 292, 5, COLOR_WHITE, COLOR_RED, 4);
	  				  				 LCD_SetMode(LCD_MODE_TOUCH);
								}
	  				  			if(p.y<70 && New_p.y<p.y-20 && New_p.x>70 && New_p.x<170) //swipe right to the left
	  				  			{
	  				  				LCD_SetMode(LCD_MODE_DRAW);
									ILI9341_Fill(COLOR_RED);
									ILI9341_Fill_Rect(20, 140, 140, 180, COLOR_BLUE);
									ILI9341_printText("LED ON", 55,  155, COLOR_WHITE, COLOR_BLUE, 1);
									ILI9341_Fill_Rect(180, 140, 300, 180, COLOR_RED);
									ILI9341_printText("LED OFF", 215,  155, COLOR_WHITE, COLOR_RED, 1);
									ILI9341_Fill_Rect(60, 30, 260, 90, COLOR_RED);
									ILI9341_Fill_Rect(5, 215, 315, 235, COLOR_ORANGE);
									ILI9341_printText("Last touch point X=000  Y=000", 70, 221, COLOR_WHITE, COLOR_ORANGE, 1);
									ILI9341_Fill_Rect(5, 215, 5, 25, COLOR_GREEN);
									ILI9341_printText("Max, Leo, Margot, time to start ", 60 ,5, COLOR_WHITE, COLOR_BLACK, 1);
									ILI9341_Fill_Rect(280, 0, 320, 40, COLOR_RED);
									ILI9341_printText("X", 292, 5, COLOR_WHITE, COLOR_RED, 4);
									LCD_SetMode(LCD_MODE_TOUCH);
	  				  			}
	  				  		if(p.y>70 &&  p.y<170 && New_p.x<p.x-15 && p.x>150 ) //swipe up
	  				  			{
	  				  			 	 LCD_SetMode(LCD_MODE_DRAW);
	  				  			 	 ILI9341_Fill(COLOR_BLACK);
	  				  			 	 ILI9341_printImage(100,100, 100,100,VB2, sizeof(VB2));
	  				  			 	 ILI9341_Fill_Rect(280, 0, 320, 40, COLOR_RED);
	  				  			 	 ILI9341_printText("X", 292, 5, COLOR_WHITE, COLOR_RED, 4);
	  				  			 	 LCD_SetMode(LCD_MODE_TOUCH);

	  				  			}


	  		  }
	  		 else if(LCD_Touch_GetState()==LCD_TOUCH_UP){ //if the touch end
	  			 	 char  BUF[3600];
	  				  sprintf(BUF,"Ticktime : %ld",p.tick);
	  				  ILI9341_printText(BUF, 60 ,60, COLOR_WHITE, COLOR_ORANGE, 1);
	  				  BUF[0]='\0';
	  				  p.tick=0;
	  				  flag=0;

	  			  		  }
	  		  else{ //IDLE
	  			 /* LCD_SetMode(LCD_MODE_DRAW);
	  			  ILI9341_Fill_Rect(60, 30, 260, 90, COLOR_RED);
	  			  ILI9341_printText("NO TOUCH ", 60 ,60, COLOR_WHITE, COLOR_ORANGE, 1);
	  			  HAL_Delay(1000);
	  			  LCD_SetMode(LCD_MODE_TOUCH);*/
	  			flag=0;
	  			  __WFI();
	  		  }
	  /*** main test 4 draw  when moving END ***/
	  		  }
  }

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief ADC2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC2_Init(void)
{

  /* USER CODE BEGIN ADC2_Init 0 */

  /* USER CODE END ADC2_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC2_Init 1 */

  /* USER CODE END ADC2_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc2.Instance = ADC2;
  hadc2.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc2.Init.Resolution = ADC_RESOLUTION_12B;
  hadc2.Init.ScanConvMode = DISABLE;
  hadc2.Init.ContinuousConvMode = DISABLE;
  hadc2.Init.DiscontinuousConvMode = DISABLE;
  hadc2.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc2.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc2.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc2.Init.NbrOfConversion = 1;
  hadc2.Init.DMAContinuousRequests = DISABLE;
  hadc2.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc2) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_4;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC2_Init 2 */

  /* USER CODE END ADC2_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED_Pin|LCD_DC_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, TS_CS_Pin|LCD_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED_Pin LCD_DC_Pin */
  GPIO_InitStruct.Pin = LED_Pin|LCD_DC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : LCD_RST_Pin */
  GPIO_InitStruct.Pin = LCD_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LCD_RST_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : TS_CS_Pin LCD_CS_Pin */
  GPIO_InitStruct.Pin = TS_CS_Pin|LCD_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
