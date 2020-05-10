
#include "stm32f1xx_hal.h"

#include "global.h"

#include "ILI9341_STM32_Driver.h"
#include "ILI9341_GFX.h"
#include "lcd_lib.h"


SPI_HandleTypeDef hspi1;


/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}


static void MX_SPI1_Init(void)
{   
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
        Error_Handler();
  }
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
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4, GPIO_PIN_RESET);

  /*Configure GPIO pins*/
  GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}


void Error_Handler(void)
{
    while(1);
}
  
  
int main()
{
    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();
    
    /* Configure the system clock */
	SystemClock_Config();

    
    
	MX_GPIO_Init();
	MX_SPI1_Init();


	ILI9341_Init();
    
      while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

/*		ILI9341_Fill_Screen(BLACK);
		ILI9341_Set_Rotation(SCREEN_HORIZONTAL_2);
		ILI9341_Draw_Text("FPS TEST", 10, 10, WHITE, 1, BLACK);
		ILI9341_Draw_Text("FPS TEST", 10, 50, RED, 1, BLACK);
		ILI9341_Draw_Text("FPS TEST", 10, 100, BLUE, 1, BLACK);
		ILI9341_Draw_Text("FPS TEST", 10, 150, YELLOW, 1, BLACK);
		ILI9341_Draw_Text("FPS TEST", 10, 200, GREEN, 1, BLACK); */
	  //LCD_FillRectWH(0, 0, LCD_XSIZE, LCD_YSIZE);

	  ILI9341_Set_Rotation(SCREEN_HORIZONTAL_2);
	  ILI9341_Fill_Screen(BLACK);

      LCD_SetFont(&font_h12);
      LCD_SetPenColor(CL_BLUE);
      LCD_SetPenMode(PEN_SOLID);
      LCD_PrintString("Panel #1", 10, 10);
      LCD_SetPenColor(CL_RED);
      LCD_PrintString("Panel #2", 10, 25);
      LCD_SetPenColor(CL_YELLOW);
      LCD_PrintString("Panel #2", 10, 50);
      LCD_SetPenColor(CL_GREEN);
      LCD_PrintString("Panel #2", 10, 75);

      LCD_SetFont(&font_h32);
      LCD_PrintString("58", 100, 10);
      
      LCD_SetPenColor(CL_YELLOW);
      LCD_PrintString("42", 100, 50);
      
      //ILI9341_Draw_Rectangle(0, 100, 300, 100, CL_RED);

		HAL_Delay(2000);
  }
	return 0;
}
