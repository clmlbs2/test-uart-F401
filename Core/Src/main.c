/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include <stdio.h>
#include <string.h>
#include <time.h>
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
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
#define BUFFER_SIZE 4
uint8_t dataReceived[BUFFER_SIZE] = {7};
uint8_t receiveSize = 0;
HAL_StatusTypeDef status_rx = 0;
uint8_t buttonOnOff = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int	_write(int file, char *ptr, int len) {
//	for (int i = 0; i < len; i++) {
//		ITM_SendChar((*ptr++));
//	}
	HAL_UART_Transmit(&huart2, (uint8_t *)ptr, len, HAL_MAX_DELAY);
		return (len);
}
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
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\r\nDEBUT BUENO\n\n\n\n\n\n\n\n\n\n\n");
  HAL_UART_Receive_IT(&huart1, dataReceived, BUFFER_SIZE);
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  if (HAL_GPIO_ReadPin(on_GPIO_Port, on_Pin) == GPIO_PIN_RESET) {
		  if (buttonOnOff == 1) {
			  buttonOnOff = 0;
			  uint8_t msg[BUFFER_SIZE] = "S0\r\n";
			  printf("buttonOnOff = 0\r\n");
			  HAL_UART_Transmit_IT(&huart1, msg, BUFFER_SIZE);
			  HAL_Delay(500);
		  } else {
			  buttonOnOff = 1;
			  uint8_t msg[BUFFER_SIZE] = "S1\r\n";
			  printf("buttonOnOff = 1\r\n");
			  HAL_UART_Transmit_IT(&huart1, msg, BUFFER_SIZE);
			  HAL_Delay(500);
		  }
	  }

//	  printf("EXO_STATUS: %d\r\n", HAL_GPIO_ReadPin(on_GPIO_Port, on_Pin));
//	  if (HAL_GPIO_ReadPin(on_GPIO_Port, on_Pin) == GPIO_PIN_RESET && buttonOnOff == 0) {
//		  buttonOnOff = 1;
//		  uint8_t msg[BUFFER_SIZE] = "S1\r\n";
//		  printf("exo_status = 1\r\n");
//		  	HAL_UART_Transmit_IT(&huart1, msg, BUFFER_SIZE);
//	  } else if (HAL_GPIO_ReadPin(on_GPIO_Port, on_Pin) == GPIO_PIN_SET && buttonOnOff == 1) {
//		  buttonOnOff = 0;
//		  uint8_t msg[BUFFER_SIZE] = "S0\r\n";
//		  printf("exo_status = 0\r\n");
//		  HAL_UART_Transmit_IT(&huart1, msg, BUFFER_SIZE);
//	  }
  }
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
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

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, walk_Pin|stand_Pin|sit_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : walk_Pin stand_Pin sit_Pin */
  GPIO_InitStruct.Pin = walk_Pin|stand_Pin|sit_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : on_Pin */
  GPIO_InitStruct.Pin = on_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(on_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void analyze_positions(uint8_t *msg)
{
	if (strlen((char *)msg) < 2) {
		printf("Erreur msg trop court\n");
		return;
	}
	if (msg[0] == 'P') {
		HAL_GPIO_WritePin(sit_GPIO_Port, sit_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(stand_GPIO_Port, stand_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(walk_GPIO_Port, walk_Pin, GPIO_PIN_RESET);
		switch (msg[1]) {
			case '1':
				printf("Assis\n");
				HAL_GPIO_WritePin(sit_GPIO_Port, sit_Pin, GPIO_PIN_SET);
				break;
			case '2':
				printf("Debout\n");
				HAL_GPIO_WritePin(stand_GPIO_Port, stand_Pin, GPIO_PIN_SET);
				break;
			case '3':
				printf("Walk\n");
				HAL_GPIO_WritePin(walk_GPIO_Port, walk_Pin, GPIO_PIN_SET);
				break;
			default:
				printf("Erreur : analyze_positions msg[1] = %c\n", msg[1]);
				break;
		}
	}
}



void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	printf("%s\r\n", dataReceived);
	analyze_positions(dataReceived);
	HAL_UART_Transmit_IT(&huart1, dataReceived, BUFFER_SIZE);
	HAL_UART_Receive_IT(&huart1, dataReceived, BUFFER_SIZE);

}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	printf("BIEN ENVOYE\r\n");

}
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
