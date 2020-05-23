
#include <stdio.h>
#include "stm32f1xx_hal.h"

#include "global.h"

#include "ILI9341.h"
#include "lcd_lib.h"
#include "utils.h"

SPI_HandleTypeDef hspi1;
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;


extern "C" void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc);



/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

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
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
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


  /*Configure GPIO pin : PB12 */
  GPIO_InitStruct.Pin = GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
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
  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;//ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 2;
  hadc1.Init.NbrOfDiscConversion = 0;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_8;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_71CYCLES_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_9;
  sConfig.Rank = ADC_REGULAR_RANK_2;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}


/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);

}


void Error_Handler(void)
{
    while(1);
}



int32_t GetWeight(void) 
{
    uint8_t i = 0;
    uint32_t adc_value = 0;

    // PB12 - CLK (output)
    // PB13 - DATA (input)

    // Set CLK low
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
    // When data conversion is ready, DATA is set LOW by ADC
    while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13) > 0);

    for(i=0; i<24; i++)
    {
        // CLK pulse
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
        // Capture DATA
        adc_value <<= 1;
        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13) > 0)
            adc_value++;
    }

    // Channel A, gain = 128 => 25 CLK pulses total
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
    // Leave CLK high for power-down
    //HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);

    // Sign - extend result
    if (adc_value & (1 << 23))
        adc_value += 0xFF000000;

    return (int32_t)adc_value;
}


volatile uint8_t adcDone = 0;



int main()
{
    char str[50];
    volatile uint16_t adc[2];
    int w_res;
    float f_res;
    
    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();
    
    /* Configure the system clock */
	SystemClock_Config();

	MX_GPIO_Init();
	MX_DMA_Init();
    MX_SPI1_Init();
    MX_ADC1_Init();
    

    //HAL_ADCEx_Calibration_Start(&hadc1);

    ILI9341_Init(SCREEN_HORIZONTAL_2);
    ILI9341_Fill_Screen(BLACK);

    LCD_SetPenMode(PEN_SOLID);
    LCD_SetAltPenMode(PEN_SOLID);

    //HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc, 2); // стартуем АЦП
    
    while (1)
    {
        LCD_SetFont(&font_12x16_mono);
        LCD_SetPenColor(CL_GREEN);
        LCD_PrintString("Panel #1", 10, 0);

        while(1)
        {
            w_res = GetWeight();
//            //sprintf(str, "% 8d", w_res);
//            sprintf(str, "%08d", w_res);
//            //i32toa_align_right(w_res, str, 10, 8, -1);
//            LCD_SetFont(&font_h48);
//            LCD_SetPenColor(CL_GREEN);
//            LCD_PrintString(str, 0, 20);
            
            f_res = (float)w_res / 100000;
            f_res += 1.58;
            f_res /= 4;
            if (f_res >= 0)
            {
                str[0] = ' ';
                sprintf(&str[1], "%.3f", f_res);
            }
            else
            {
                sprintf(&str[0], "%.3f", f_res);
            }
            LCD_SetFont(&font_h48);
            LCD_SetPenColor(CL_GREEN);
            LCD_PrintString(str, 0, 20);
/*
            HAL_ADC_Start(&hadc1);
            HAL_ADC_PollForConversion(&hadc1, 100);
            adc1 = HAL_ADC_GetValue(&hadc1);
            HAL_ADC_Start(&hadc1);
            HAL_ADC_PollForConversion(&hadc1, 100);
            adc2 = HAL_ADC_GetValue(&hadc1);
            HAL_ADC_Stop(&hadc1);
  */
            adcDone = 0;
            HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc, 2); // стартуем АЦП
            while(!adcDone);

            LCD_SetFont(&font_12x16_mono);
            LCD_SetPenColor(CL_YELLOW);
            sprintf(str, "PB[0] % 8d", adc[0]);
            LCD_PrintString(str, 0, 120);
            sprintf(str, "PB[1] % 8d", adc[1]);
            LCD_PrintString(str, 0, 136);


            //HAL_Delay(100);
        }
    }
	return 0;
}


void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    //HAL_ADC_Stop_DMA(&hadc1);
    adcDone = 1;
}

