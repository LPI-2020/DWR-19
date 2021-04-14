https://github.com/xtrinch/stm32f7-demos/tree/master/07-rfid-rc522 - source code for SPI communication with MFRC522

//---------------------------------------------------------------------//
	To use RC522 with SPI select which SPI to use in the STM32CUBEMX.
	Define corresponding SPI pins and CLKs in main.h file like this.
	
/* Definition for SPIx clock resources */
#define SPIx                             SPI1
#define SPIx_CLK_ENABLE()                __HAL_RCC_SPI1_CLK_ENABLE()
#define SPIx_SCK_GPIO_CLK_ENABLE()       __HAL_RCC_GPIOA_CLK_ENABLE()
#define SPIx_NSS_GPIO_CLK_ENABLE()       __HAL_RCC_GPIOA_CLK_ENABLE()
#define SPIx_MISO_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define SPIx_MOSI_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define SPIx_CS_GPIO_CLK_ENABLE()				 __HAL_RCC_GPIOF_CLK_ENABLE()

#define SPIx_FORCE_RESET()               __HAL_RCC_SPI1_FORCE_RESET()
#define SPIx_RELEASE_RESET()             __HAL_RCC_SPI1_RELEASE_RESET()

/* Definition for SPIx Pins */
#define SPIx_SCK_PIN                     GPIO_PIN_5 // A5
#define SPIx_SCK_GPIO_PORT               GPIOA
#define SPIx_SCK_AF                      GPIO_AF5_SPI1
#define SPIx_MISO_PIN                    GPIO_PIN_6 // A6
#define SPIx_MISO_GPIO_PORT              GPIOA
#define SPIx_MISO_AF                     GPIO_AF5_SPI1
#define SPIx_MOSI_PIN                    GPIO_PIN_7 // A7
#define SPIx_MOSI_GPIO_PORT              GPIOA
#define SPIx_MOSI_AF                     GPIO_AF5_SPI1
#define SPIx_NSS_PIN					 GPIO_PIN_11 // A11
#define SPIx_NSS_GPIO_PORT				 GPIOA
#define SPIx_NSS_AF						 GPIO_AF5_SPI1
#define SPIx_CS_PIN                      GPIO_PIN_1 // F1
#define SPIx_CS_GPIO_PORT                GPIOF

	SPI CLK, MISO, MOSI are defined automatically by CUBE software, CS pin needs
to be specified manually as GPIO_OUTPUT in software and then declared above.

In main.c:

 /* USER CODE BEGIN 1 */
	
	uint8_t CardID[4];
	
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
  
  /* USER CODE BEGIN 2 */
	
	RFID_RC522_Init();
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
		int status = TM_MFRC522_Check(CardID, &type);
		if (status == MI_OK) {
			//------------------------------------------------------------------------------------------------------------------//
			//Copy contents of CardId to another array because CardId will get "corrupted" upon calling TM_MFRC522_Check() again//
			//------------------------------------------------------------------------------------------------------------------//
		}
		else {							//------------------------//
        if (status == MI_TIMEOUT) {		//						  //
            str = "timeout";			// This part is optcional //
        }								//                        //
        if (status == MI_ERR) {			//------------------------//
            str = "error";
        }
    }
			
    /* USER CODE BEGIN 3 */
  }
  
//----------------------------------------------------------------------------------------------------------------------------------//  
  
  //----------------------------------------------------//
  // MX_SPI1_Init() - Configure SPI interface as below //
  //----------------------------------------------------//
  
void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}